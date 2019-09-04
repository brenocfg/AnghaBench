#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tftphdr {int dummy; } ;
struct testcase {int dummy; } ;
struct TYPE_3__ {struct tftphdr hdr; } ;
struct TYPE_4__ {int counter; TYPE_1__ buf; } ;

/* Variables and functions */
 int BF_ALLOC ; 
 int BF_FREE ; 
 TYPE_2__* bfs ; 
 size_t current ; 
 int /*<<< orphan*/  write_behind (struct testcase*,int) ; 

__attribute__((used)) static int writeit(struct testcase *test, struct tftphdr * volatile *dpp,
                   int ct, int convert)
{
  bfs[current].counter = ct;      /* set size of data to write */
  current = !current;             /* switch to other buffer */
  if(bfs[current].counter != BF_FREE)     /* if not free */
    write_behind(test, convert);     /* flush it */
  bfs[current].counter = BF_ALLOC;        /* mark as alloc'd */
  *dpp =  &bfs[current].buf.hdr;
  return ct;                      /* this is a lie of course */
}