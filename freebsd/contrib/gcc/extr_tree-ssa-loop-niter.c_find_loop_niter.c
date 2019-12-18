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
struct tree_niter_desc {scalar_t__ niter; int /*<<< orphan*/  may_be_zero; } ;
struct loop {int dummy; } ;
typedef  TYPE_1__* edge ;
struct TYPE_6__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ chrec_dont_know ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** get_loop_exit_edges (struct loop*,unsigned int*) ; 
 int /*<<< orphan*/  just_once_each_iteration_p (struct loop*,int /*<<< orphan*/ ) ; 
 scalar_t__ nonzero_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number_of_iterations_exit (struct loop*,TYPE_1__*,struct tree_niter_desc*,int) ; 
 scalar_t__ tree_int_cst_lt (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  unsigned_type_node ; 
 int /*<<< orphan*/  zero_p (int /*<<< orphan*/ ) ; 

tree
find_loop_niter (struct loop *loop, edge *exit)
{
  unsigned n_exits, i;
  edge *exits = get_loop_exit_edges (loop, &n_exits);
  edge ex;
  tree niter = NULL_TREE, aniter;
  struct tree_niter_desc desc;

  *exit = NULL;
  for (i = 0; i < n_exits; i++)
    {
      ex = exits[i];
      if (!just_once_each_iteration_p (loop, ex->src))
	continue;

      if (!number_of_iterations_exit (loop, ex, &desc, false))
	continue;

      if (nonzero_p (desc.may_be_zero))
	{
	  /* We exit in the first iteration through this exit.
	     We won't find anything better.  */
	  niter = build_int_cst (unsigned_type_node, 0);
	  *exit = ex;
	  break;
	}

      if (!zero_p (desc.may_be_zero))
	continue;

      aniter = desc.niter;

      if (!niter)
	{
	  /* Nothing recorded yet.  */
	  niter = aniter;
	  *exit = ex;
	  continue;
	}

      /* Prefer constants, the lower the better.  */
      if (TREE_CODE (aniter) != INTEGER_CST)
	continue;

      if (TREE_CODE (niter) != INTEGER_CST)
	{
	  niter = aniter;
	  *exit = ex;
	  continue;
	}

      if (tree_int_cst_lt (aniter, niter))
	{
	  niter = aniter;
	  *exit = ex;
	  continue;
	}
    }
  free (exits);

  return niter ? niter : chrec_dont_know;
}