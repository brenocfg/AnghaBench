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
struct loop {int /*<<< orphan*/  latch; } ;
typedef  int /*<<< orphan*/ * basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_DOMINATORS ; 
 scalar_t__ dominated_by_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * first_dom_son (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flow_bb_inside_loop_p (struct loop const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * next_dom_son (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fill_sons_in_loop (const struct loop *loop, basic_block bb,
		   basic_block *tovisit, int *tv)
{
  basic_block son, postpone = NULL;

  tovisit[(*tv)++] = bb;
  for (son = first_dom_son (CDI_DOMINATORS, bb);
       son;
       son = next_dom_son (CDI_DOMINATORS, son))
    {
      if (!flow_bb_inside_loop_p (loop, son))
	continue;

      if (dominated_by_p (CDI_DOMINATORS, loop->latch, son))
	{
	  postpone = son;
	  continue;
	}
      fill_sons_in_loop (loop, son, tovisit, tv);
    }

  if (postpone)
    fill_sons_in_loop (loop, postpone, tovisit, tv);
}