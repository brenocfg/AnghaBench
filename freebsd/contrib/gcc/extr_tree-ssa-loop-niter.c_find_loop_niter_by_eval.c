#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
struct loop {int dummy; } ;
typedef  TYPE_1__* edge ;
struct TYPE_6__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ NULL_TREE ; 
 scalar_t__ chrec_contains_undetermined (scalar_t__) ; 
 scalar_t__ chrec_dont_know ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** get_loop_exit_edges (struct loop*,unsigned int*) ; 
 int /*<<< orphan*/  just_once_each_iteration_p (struct loop*,int /*<<< orphan*/ ) ; 
 scalar_t__ loop_niter_by_eval (struct loop*,TYPE_1__*) ; 
 int /*<<< orphan*/  tree_int_cst_lt (scalar_t__,scalar_t__) ; 

tree
find_loop_niter_by_eval (struct loop *loop, edge *exit)
{
  unsigned n_exits, i;
  edge *exits = get_loop_exit_edges (loop, &n_exits);
  edge ex;
  tree niter = NULL_TREE, aniter;

  *exit = NULL;
  for (i = 0; i < n_exits; i++)
    {
      ex = exits[i];
      if (!just_once_each_iteration_p (loop, ex->src))
	continue;

      aniter = loop_niter_by_eval (loop, ex);
      if (chrec_contains_undetermined (aniter))
	continue;

      if (niter
	  && !tree_int_cst_lt (aniter, niter))
	continue;

      niter = aniter;
      *exit = ex;
    }
  free (exits);

  return niter ? niter : chrec_dont_know;
}