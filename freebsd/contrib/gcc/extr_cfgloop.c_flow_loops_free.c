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
struct TYPE_2__ {struct loop** rc_order; struct loop** dfs_order; } ;
struct loops {unsigned int num; TYPE_1__ cfg; struct loop** parray; } ;
struct loop {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  flow_loop_free (struct loop*) ; 
 int /*<<< orphan*/  free (struct loop**) ; 
 int /*<<< orphan*/  gcc_assert (unsigned int) ; 

void
flow_loops_free (struct loops *loops)
{
  if (loops->parray)
    {
      unsigned i;

      gcc_assert (loops->num);

      /* Free the loop descriptors.  */
      for (i = 0; i < loops->num; i++)
	{
	  struct loop *loop = loops->parray[i];

	  if (!loop)
	    continue;

	  flow_loop_free (loop);
	}

      free (loops->parray);
      loops->parray = NULL;

      if (loops->cfg.dfs_order)
	free (loops->cfg.dfs_order);
      if (loops->cfg.rc_order)
	free (loops->cfg.rc_order);

    }
}