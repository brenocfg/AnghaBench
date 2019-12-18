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
typedef  enum cdi_direction { ____Placeholder_cdi_direction } cdi_direction ;
typedef  int /*<<< orphan*/ * basic_block ;

/* Variables and functions */
 int /*<<< orphan*/ ** dom_computed ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_immediate_dominator (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * recount_dominator (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_immediate_dominator (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
iterate_fix_dominators (enum cdi_direction dir, basic_block *bbs, int n)
{
  int i, changed = 1;
  basic_block old_dom, new_dom;

  gcc_assert (dom_computed[dir]);

  for (i = 0; i < n; i++)
    set_immediate_dominator (dir, bbs[i], NULL);

  while (changed)
    {
      changed = 0;
      for (i = 0; i < n; i++)
	{
	  old_dom = get_immediate_dominator (dir, bbs[i]);
	  new_dom = recount_dominator (dir, bbs[i]);
	  if (old_dom != new_dom)
	    {
	      changed = 1;
	      set_immediate_dominator (dir, bbs[i], new_dom);
	    }
	}
    }

  for (i = 0; i < n; i++)
    gcc_assert (get_immediate_dominator (dir, bbs[i]));
}