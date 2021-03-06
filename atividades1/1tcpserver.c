#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>



#define MAX_MSG 100
#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 3787


 main ( ) {

  int sd, newSd, cliLen, n,num1,num2,sum, nome, cargo, salario,novosalario;

  struct sockaddr_in cliAddr, servAddr;
  char line[MAX_MSG],line1[MAX_MSG],line2[MAX_MSG];


  /**********************************/ 
  /* build server address structure */
  /**********************************/ 

  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
  servAddr.sin_port = htons(SERVER_PORT);

/*
  bzero((char *)&servAddr, sizeof(servAddr));
  servAddr.sin_family = AF_INET;
  inet_aton(SERVER_ADDR, &servAddr.sin_addr);
  servAddr.sin_port = htons(SERVER_PORT);
*/


  /************************/ 
  /* create stream socket */
  /************************/ 

  sd = socket(AF_INET, SOCK_STREAM, 0);
  printf("Socket criado com sucesso. \n");

  /**************************/ 
  /* bind local port number */
  /**************************/ 

  bind(sd, (struct sockaddr *) &servAddr, sizeof(servAddr));
  printf("Porta ok. \n");


  /********************************/ 
  /* specify number of concurrent */
  /* clients to listen for        */
  /********************************/ 

  listen(sd,5);


  while(1) {

    printf("Esperando o cliente conectar na porta TCP %u\n",SERVER_PORT);

    /*****************************/
    /* wait for client connection*/
    /*****************************/   

    cliLen = sizeof(cliAddr);
    newSd = accept(sd, (struct sockaddr *) &cliAddr, &cliLen);

    printf("Conectado! Detalhes: [IP %s ,TCP port %d]\n",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

    /*****************************/
    /* wait for data from client */
    /*****************************/     

    do{
      memset(line,0x0,MAX_MSG);

      n=recv(newSd, line, MAX_MSG, 0);
      nome=atoi(line);

      n=recv(newSd, line, MAX_MSG, 0);
      cargo=atoi(line);

      n=recv(newSd, line, MAX_MSG, 0);
      salario=atoi(line);

//	if(strcmp(salario, "operador") == 0){
//	   novosalario=salario*1.2;
//	}

//	if(strcmp(salario, "programador") == 0){
//	   novosalario=salario*1.18;
//	}


//	if (cargo == "operador") {
//		novosalario=salario*1.2;
//		}
//	if (cargo == "programador") {
//		novosalario=salario*1.18;
//		}

//      sprintf(line1,"%d",nome);
      sprintf(line1,"%d",salario);


      printf("received from host [IP %s ,TCP port %d] : %s\n",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line1);
  send(newSd, line1, strlen(line1) + 1, 0);

//      printf("received from host [IP %s ,TCP port %d] : %s\n",
  //               inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port), line2);
//  send(newSd, line2, strlen(line2) + 1, 0);

    } while(abs(strcmp(line, "quit")));


    /**************************/
    /* close client connection*/
    /**************************/   

    printf("closing connection with host [IP %s ,TCP port %d]\n",
                 inet_ntoa(cliAddr.sin_addr), ntohs(cliAddr.sin_port));

    close(newSd);
  }
}
