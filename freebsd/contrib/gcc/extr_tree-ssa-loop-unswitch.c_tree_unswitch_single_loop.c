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
typedef  int /*<<< orphan*/  tree ;
struct loops {int dummy; } ;
struct loop {unsigned int num_nodes; scalar_t__ inner; } ;
typedef  int /*<<< orphan*/  basic_block ;
typedef  int /*<<< orphan*/  COND_EXPR_COND ;

/* Variables and functions */
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  PARAM_MAX_UNSWITCH_INSNS ; 
 int /*<<< orphan*/  PARAM_MAX_UNSWITCH_LEVEL ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
 int TDF_DETAILS ; 
 int /*<<< orphan*/  TODO_update_ssa ; 
 int /*<<< orphan*/  boolean_false_node ; 
 int /*<<< orphan*/  boolean_true_node ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_original_copy_tables () ; 
 int /*<<< orphan*/ * get_loop_body (struct loop*) ; 
 int /*<<< orphan*/  initialize_original_copy_tables () ; 
 scalar_t__ integer_nonzerop (int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simplify_using_entry_checks (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_may_unswitch_on (int /*<<< orphan*/ ,struct loop*) ; 
 unsigned int tree_num_loop_insns (struct loop*) ; 
 struct loop* tree_unswitch_loop (struct loops*,struct loop*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_ssa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
tree_unswitch_single_loop (struct loops *loops, struct loop *loop, int num)
{
  basic_block *bbs;
  struct loop *nloop;
  unsigned i;
  tree cond = NULL_TREE, stmt;
  bool changed = false;

  /* Do not unswitch too much.  */
  if (num > PARAM_VALUE (PARAM_MAX_UNSWITCH_LEVEL))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, ";; Not unswitching anymore, hit max level\n");
      return false;
    }

  /* Only unswitch innermost loops.  */
  if (loop->inner)
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, ";; Not unswitching, not innermost loop\n");
      return false;
    }

  /* The loop should not be too large, to limit code growth.  */
  if (tree_num_loop_insns (loop)
      > (unsigned) PARAM_VALUE (PARAM_MAX_UNSWITCH_INSNS))
    {
      if (dump_file && (dump_flags & TDF_DETAILS))
	fprintf (dump_file, ";; Not unswitching, loop too big\n");
      return false;
    }

  i = 0;
  bbs = get_loop_body (loop);
  
  while (1)
    {
      /* Find a bb to unswitch on.  */
      for (; i < loop->num_nodes; i++)
	if ((cond = tree_may_unswitch_on (bbs[i], loop)))
	  break;

      if (i == loop->num_nodes)
	{
	  free (bbs);
	  return changed;
	}

      cond = simplify_using_entry_checks (loop, cond);
      stmt = last_stmt (bbs[i]);
      if (integer_nonzerop (cond))
	{
	  /* Remove false path.  */
	  COND_EXPR_COND (stmt) = boolean_true_node;
	  changed = true;
	}
      else if (integer_zerop (cond))
	{
	  /* Remove true path.  */
	  COND_EXPR_COND (stmt) = boolean_false_node;
	  changed = true;
	}
      else
	break;

      update_stmt (stmt);
      i++;
    }

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file, ";; Unswitching loop\n");

  initialize_original_copy_tables ();
  /* Unswitch the loop on this condition.  */
  nloop = tree_unswitch_loop (loops, loop, bbs[i], cond);
  if (!nloop)
    {
      free_original_copy_tables ();
      free (bbs);
      return changed;
    }

  /* Update the SSA form after unswitching.  */
  update_ssa (TODO_update_ssa);
  free_original_copy_tables ();

  /* Invoke itself on modified loops.  */
  tree_unswitch_single_loop (loops, nloop, num + 1);
  tree_unswitch_single_loop (loops, loop, num + 1);
  free (bbs);
  return true;
}