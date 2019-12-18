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
struct loops {unsigned int num; int /*<<< orphan*/  state; struct loop** parray; } ;
struct loop {scalar_t__ latch; scalar_t__ header; } ;
typedef  int /*<<< orphan*/  edge ;

/* Variables and functions */
 int /*<<< orphan*/  LOOPS_HAVE_SIMPLE_LATCHES ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  find_edge (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  loop_split_edge_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ single_succ_p (scalar_t__) ; 

void
force_single_succ_latches (struct loops *loops)
{
  unsigned i;
  struct loop *loop;
  edge e;

  for (i = 1; i < loops->num; i++)
    {
      loop = loops->parray[i];
      if (loop->latch != loop->header && single_succ_p (loop->latch))
	continue;

      e = find_edge (loop->latch, loop->header);

      loop_split_edge_with (e, NULL_RTX);
    }
  loops->state |= LOOPS_HAVE_SIMPLE_LATCHES;
}