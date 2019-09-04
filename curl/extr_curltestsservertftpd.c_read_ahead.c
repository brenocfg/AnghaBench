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
struct testcase {int* rptr; scalar_t__ rcount; } ;
struct TYPE_2__ {struct tftphdr hdr; } ;
struct bf {int counter; TYPE_1__ buf; } ;

/* Variables and functions */
 int BF_FREE ; 
 size_t MIN (int,scalar_t__) ; 
 int SEGSIZE ; 
 struct bf* bfs ; 
 int /*<<< orphan*/  memcpy (char*,int*,size_t) ; 
 int newline ; 
 size_t nextone ; 
 char prevchar ; 

__attribute__((used)) static void read_ahead(struct testcase *test,
                       int convert /* if true, convert to ascii */)
{
  int i;
  char *p;
  int c;
  struct bf *b;
  struct tftphdr *dp;

  b = &bfs[nextone];              /* look at "next" buffer */
  if(b->counter != BF_FREE)      /* nop if not free */
    return;
  nextone = !nextone;             /* "incr" next buffer ptr */

  dp = &b->buf.hdr;

  if(convert == 0) {
    /* The former file reading code did this:
       b->counter = read(fileno(file), dp->th_data, SEGSIZE); */
    size_t copy_n = MIN(SEGSIZE, test->rcount);
    memcpy(dp->th_data, test->rptr, copy_n);

    /* decrease amount, advance pointer */
    test->rcount -= copy_n;
    test->rptr += copy_n;
    b->counter = (int)copy_n;
    return;
  }

  p = dp->th_data;
  for(i = 0 ; i < SEGSIZE; i++) {
    if(newline) {
      if(prevchar == '\n')
        c = '\n';       /* lf to cr,lf */
      else
        c = '\0';       /* cr to cr,nul */
      newline = 0;
    }
    else {
      if(test->rcount) {
        c = test->rptr[0];
        test->rptr++;
        test->rcount--;
      }
      else
        break;
      if(c == '\n' || c == '\r') {
        prevchar = c;
        c = '\r';
        newline = 1;
      }
    }
    *p++ = (char)c;
  }
  b->counter = (int)(p - dp->th_data);
}