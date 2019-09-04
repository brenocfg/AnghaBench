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
struct tftphdr {int dummy; } ;
struct testcase {int dummy; } ;
struct TYPE_2__ {struct tftphdr hdr; } ;
struct bf {scalar_t__ counter; TYPE_1__ buf; } ;

/* Variables and functions */
 scalar_t__ BF_FREE ; 
 struct bf* bfs ; 
 size_t current ; 
 int /*<<< orphan*/  read_ahead (struct testcase*,int) ; 

__attribute__((used)) static int readit(struct testcase *test, struct tftphdr **dpp,
                  int convert /* if true, convert to ascii */)
{
  struct bf *b;

  bfs[current].counter = BF_FREE; /* free old one */
  current = !current;             /* "incr" current */

  b = &bfs[current];              /* look at new buffer */
  if(b->counter == BF_FREE)      /* if it's empty */
    read_ahead(test, convert);    /* fill it */

  *dpp = &b->buf.hdr;             /* set caller's ptr */
  return b->counter;
}