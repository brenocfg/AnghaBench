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
typedef  int /*<<< orphan*/  tree ;
struct loops {int dummy; } ;
struct loop {int num; TYPE_1__* single_exit; } ;
typedef  enum unroll_level { ____Placeholder_unroll_level } unroll_level ;
typedef  TYPE_1__* edge ;
struct TYPE_6__ {int /*<<< orphan*/  src; } ;

/* Variables and functions */
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TDF_SLIM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 scalar_t__ chrec_contains_undetermined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_canonical_iv (struct loop*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  find_loop_niter (struct loop*,TYPE_1__**) ; 
 int /*<<< orphan*/  find_loop_niter_by_eval (struct loop*,TYPE_1__**) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,...) ; 
 int /*<<< orphan*/  just_once_each_iteration_p (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  number_of_iterations_in_loop (struct loop*) ; 
 int /*<<< orphan*/  print_generic_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ try_unroll_loop_completely (struct loops*,struct loop*,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
canonicalize_loop_induction_variables (struct loops *loops, struct loop *loop,
				       bool create_iv, enum unroll_level ul,
				       bool try_eval)
{
  edge exit = NULL;
  tree niter;

  niter = number_of_iterations_in_loop (loop);
  if (TREE_CODE (niter) == INTEGER_CST)
    {
      exit = loop->single_exit;
      if (!just_once_each_iteration_p (loop, exit->src))
	return false;

      /* The result of number_of_iterations_in_loop is by one higher than
	 we expect (i.e. it returns number of executions of the exit
	 condition, not of the loop latch edge).  */
      niter = fold_build2 (MINUS_EXPR, TREE_TYPE (niter), niter,
			   build_int_cst (TREE_TYPE (niter), 1));
    }
  else
    {
      /* If the loop has more than one exit, try checking all of them
	 for # of iterations determinable through scev.  */
      if (!loop->single_exit)
	niter = find_loop_niter (loop, &exit);

      /* Finally if everything else fails, try brute force evaluation.  */
      if (try_eval
	  && (chrec_contains_undetermined (niter)
	      || TREE_CODE (niter) != INTEGER_CST))
	niter = find_loop_niter_by_eval (loop, &exit);

      if (chrec_contains_undetermined (niter)
	  || TREE_CODE (niter) != INTEGER_CST)
	return false;
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    {
      fprintf (dump_file, "Loop %d iterates ", loop->num);
      print_generic_expr (dump_file, niter, TDF_SLIM);
      fprintf (dump_file, " times.\n");
    }

  if (try_unroll_loop_completely (loops, loop, exit, niter, ul))
    return true;

  if (create_iv)
    create_canonical_iv (loop, exit, niter);

  return false;
}