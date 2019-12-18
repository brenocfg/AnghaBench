#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tftphdr {char* th_data; } ;
struct testcase {int ofile; int /*<<< orphan*/  testno; } ;
struct TYPE_2__ {struct tftphdr hdr; } ;
struct bf {int counter; TYPE_1__ buf; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  outfile ;

/* Variables and functions */
 int BF_FREE ; 
 int O_BINARY ; 
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 struct bf* bfs ; 
 int /*<<< orphan*/  logmsg (char*,char*) ; 
 int /*<<< orphan*/  lseek (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 size_t nextone ; 
 void* open (char*,int,int) ; 
 char prevchar ; 
 int write (int,...) ; 

__attribute__((used)) static ssize_t write_behind(struct testcase *test, int convert)
{
  char *writebuf;
  int count;
  int ct;
  char *p;
  int c;                          /* current character */
  struct bf *b;
  struct tftphdr *dp;

  b = &bfs[nextone];
  if(b->counter < -1)            /* anything to flush? */
    return 0;                     /* just nop if nothing to do */

  if(!test->ofile) {
    char outfile[256];
    msnprintf(outfile, sizeof(outfile), "log/upload.%ld", test->testno);
#ifdef WIN32
    test->ofile = open(outfile, O_CREAT|O_RDWR|O_BINARY, 0777);
#else
    test->ofile = open(outfile, O_CREAT|O_RDWR, 0777);
#endif
    if(test->ofile == -1) {
      logmsg("Couldn't create and/or open file %s for upload!", outfile);
      return -1; /* failure! */
    }
  }

  count = b->counter;             /* remember byte count */
  b->counter = BF_FREE;           /* reset flag */
  dp = &b->buf.hdr;
  nextone = !nextone;             /* incr for next time */
  writebuf = dp->th_data;

  if(count <= 0)
    return -1;                    /* nak logic? */

  if(convert == 0)
    return write(test->ofile, writebuf, count);

  p = writebuf;
  ct = count;
  while(ct--) {                   /* loop over the buffer */
    c = *p++;                     /* pick up a character */
    if(prevchar == '\r') {        /* if prev char was cr */
      if(c == '\n')               /* if have cr,lf then just */
        lseek(test->ofile, -1, SEEK_CUR); /* smash lf on top of the cr */
      else
        if(c == '\0')             /* if have cr,nul then */
          goto skipit;            /* just skip over the putc */
      /* else just fall through and allow it */
    }
    /* formerly
       putc(c, file); */
    if(1 != write(test->ofile, &c, 1))
      break;
    skipit:
    prevchar = c;
  }
  return count;
}