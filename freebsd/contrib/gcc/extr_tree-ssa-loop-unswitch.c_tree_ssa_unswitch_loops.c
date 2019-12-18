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
struct loops {int num; struct loop** parray; } ;
struct loop {scalar_t__ inner; } ;

/* Variables and functions */
 unsigned int TODO_cleanup_cfg ; 
 int tree_unswitch_single_loop (struct loops*,struct loop*,int /*<<< orphan*/ ) ; 

unsigned int
tree_ssa_unswitch_loops (struct loops *loops)
{
  int i, num;
  struct loop *loop;
  bool changed = false;

  /* Go through inner loops (only original ones).  */
  num = loops->num;

  for (i = 1; i < num; i++)
    {
      /* Removed loop?  */
      loop = loops->parray[i];
      if (!loop)
	continue;

      if (loop->inner)
	continue;

      changed |= tree_unswitch_single_loop (loops, loop, 0);
    }

  if (changed)
    return TODO_cleanup_cfg;
  return 0;
}