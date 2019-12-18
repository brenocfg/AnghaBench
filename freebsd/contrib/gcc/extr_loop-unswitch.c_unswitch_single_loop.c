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
struct loops {int dummy; } ;
struct loop {unsigned int num_nodes; int /*<<< orphan*/  header; scalar_t__ inner; } ;
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  edge ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  BRANCH_EDGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALLTHRU_EDGE (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PARAM_MAX_UNSWITCH_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNSWITCH_LEVEL ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ alloc_EXPR_LIST (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  can_duplicate_loop_p (struct loop*) ; 
 scalar_t__ canon_condition (scalar_t__) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const_true_rtx ; 
 scalar_t__ dump_file ; 
 int expected_loop_iterations (struct loop*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_EXPR_LIST_node (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (struct loop*) ; 
 int /*<<< orphan*/ * get_loop_body (struct loop*) ; 
 int /*<<< orphan*/  iv_analysis_loop_init (struct loop*) ; 
 scalar_t__ may_unswitch_on (int /*<<< orphan*/ ,struct loop*,scalar_t__*) ; 
 int /*<<< orphan*/  maybe_hot_bb_p (int /*<<< orphan*/ ) ; 
 int num_loop_insns (struct loop*) ; 
 int /*<<< orphan*/  remove_path (struct loops*,int /*<<< orphan*/ ) ; 
 scalar_t__ reversed_condition (scalar_t__) ; 
 int /*<<< orphan*/  simplify_using_condition (scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 struct loop* unswitch_loop (struct loops*,struct loop*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
unswitch_single_loop (struct loops *loops, struct loop *loop,
		      rtx cond_checked, int num)
{
  basic_block *bbs;
  struct loop *nloop;
  unsigned i;
  rtx cond, rcond = NULL_RTX, conds, rconds, acond, cinsn;
  int repeat;
  edge e;

  /* Do not unswitch too much.  */
  if (num > PARAM_VALUE (PARAM_MAX_UNSWITCH_LEVEL))
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unswitching anymore, hit max level\n");
      return;
    }

  /* Only unswitch innermost loops.  */
  if (loop->inner)
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unswitching, not innermost loop\n");
      return;
    }

  /* We must be able to duplicate loop body.  */
  if (!can_duplicate_loop_p (loop))
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unswitching, can't duplicate loop\n");
      return;
    }

  /* The loop should not be too large, to limit code growth.  */
  if (num_loop_insns (loop) > PARAM_VALUE (PARAM_MAX_UNSWITCH_INSNS))
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unswitching, loop too big\n");
      return;
    }

  /* Do not unswitch in cold areas.  */
  if (!maybe_hot_bb_p (loop->header))
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unswitching, not hot area\n");
      return;
    }

  /* Nor if the loop usually does not roll.  */
  if (expected_loop_iterations (loop) < 1)
    {
      if (dump_file)
	fprintf (dump_file, ";; Not unswitching, loop iterations < 1\n");
      return;
    }

  do
    {
      repeat = 0;
      cinsn = NULL_RTX;

      /* Find a bb to unswitch on.  */
      bbs = get_loop_body (loop);
      iv_analysis_loop_init (loop);
      for (i = 0; i < loop->num_nodes; i++)
	if ((cond = may_unswitch_on (bbs[i], loop, &cinsn)))
	  break;

      if (i == loop->num_nodes)
	{
	  free (bbs);
	  return;
	}

      if (cond != const0_rtx
	  && cond != const_true_rtx)
	{
	  rcond = reversed_condition (cond);
	  if (rcond)
	    rcond = canon_condition (rcond);

	  /* Check whether the result can be predicted.  */
	  for (acond = cond_checked; acond; acond = XEXP (acond, 1))
	    simplify_using_condition (XEXP (acond, 0), &cond, NULL);
	}

      if (cond == const_true_rtx)
	{
	  /* Remove false path.  */
	  e = FALLTHRU_EDGE (bbs[i]);
	  remove_path (loops, e);
	  free (bbs);
	  repeat = 1;
	}
      else if (cond == const0_rtx)
	{
	  /* Remove true path.  */
	  e = BRANCH_EDGE (bbs[i]);
	  remove_path (loops, e);
	  free (bbs);
	  repeat = 1;
	}
    } while (repeat);

  /* We found the condition we can unswitch on.  */
  conds = alloc_EXPR_LIST (0, cond, cond_checked);
  if (rcond)
    rconds = alloc_EXPR_LIST (0, rcond, cond_checked);
  else
    rconds = cond_checked;

  if (dump_file)
    fprintf (dump_file, ";; Unswitching loop\n");

  /* Unswitch the loop on this condition.  */
  nloop = unswitch_loop (loops, loop, bbs[i], cond, cinsn);
  gcc_assert (nloop);

  /* Invoke itself on modified loops.  */
  unswitch_single_loop (loops, nloop, rconds, num + 1);
  unswitch_single_loop (loops, loop, conds, num + 1);

  free_EXPR_LIST_node (conds);
  if (rcond)
    free_EXPR_LIST_node (rconds);

  free (bbs);
}