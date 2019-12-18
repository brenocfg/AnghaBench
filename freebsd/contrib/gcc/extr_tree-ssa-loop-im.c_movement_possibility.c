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
typedef  int /*<<< orphan*/  tree ;
typedef  enum move_pos { ____Placeholder_move_pos } move_pos ;
struct TYPE_2__ {scalar_t__ has_volatile_ops; } ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 scalar_t__ MODIFY_EXPR ; 
 int MOVE_IMPOSSIBLE ; 
 int MOVE_POSSIBLE ; 
 int MOVE_PRESERVE_EXECUTION ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ SSA_NAME_OCCURS_IN_ABNORMAL_PHI (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_unswitch_loops ; 
 scalar_t__ get_call_expr_in (int /*<<< orphan*/ ) ; 
 TYPE_1__* stmt_ann (int /*<<< orphan*/ ) ; 
 scalar_t__ stmt_ends_bb_p (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_could_trap_p (int /*<<< orphan*/ ) ; 

enum move_pos
movement_possibility (tree stmt)
{
  tree lhs, rhs;

  if (flag_unswitch_loops
      && TREE_CODE (stmt) == COND_EXPR)
    {
      /* If we perform unswitching, force the operands of the invariant
	 condition to be moved out of the loop.  */
      return MOVE_POSSIBLE;
    }

  if (TREE_CODE (stmt) != MODIFY_EXPR)
    return MOVE_IMPOSSIBLE;

  if (stmt_ends_bb_p (stmt))
    return MOVE_IMPOSSIBLE;

  if (stmt_ann (stmt)->has_volatile_ops)
    return MOVE_IMPOSSIBLE;

  lhs = TREE_OPERAND (stmt, 0);
  if (TREE_CODE (lhs) == SSA_NAME
      && SSA_NAME_OCCURS_IN_ABNORMAL_PHI (lhs))
    return MOVE_IMPOSSIBLE;

  rhs = TREE_OPERAND (stmt, 1);

  if (TREE_SIDE_EFFECTS (rhs))
    return MOVE_IMPOSSIBLE;

  if (TREE_CODE (lhs) != SSA_NAME
      || tree_could_trap_p (rhs))
    return MOVE_PRESERVE_EXECUTION;

  if (get_call_expr_in (stmt))
    {
      /* While pure or const call is guaranteed to have no side effects, we
	 cannot move it arbitrarily.  Consider code like

	 char *s = something ();

	 while (1)
	   {
	     if (s)
	       t = strlen (s);
	     else
	       t = 0;
	   }

	 Here the strlen call cannot be moved out of the loop, even though
	 s is invariant.  In addition to possibly creating a call with
	 invalid arguments, moving out a function call that is not executed
	 may cause performance regressions in case the call is costly and
	 not executed at all.  */
      return MOVE_PRESERVE_EXECUTION;
    }
  return MOVE_POSSIBLE;
}