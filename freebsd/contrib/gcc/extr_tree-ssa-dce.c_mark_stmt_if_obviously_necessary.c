#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* stmt_ann_t ;
struct TYPE_5__ {int /*<<< orphan*/  succs; } ;
struct TYPE_4__ {scalar_t__ has_volatile_ops; } ;

/* Variables and functions */
#define  ASM_EXPR 138 
#define  BIND_EXPR 137 
#define  CALL_EXPR 136 
#define  CASE_LABEL_EXPR 135 
#define  COND_EXPR 134 
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int EXC_PTR_EXPR ; 
 int FILTER_EXPR ; 
#define  GOTO_EXPR 133 
#define  LABEL_EXPR 132 
#define  MODIFY_EXPR 131 
#define  RESX_EXPR 130 
#define  RETURN_EXPR 129 
#define  SWITCH_EXPR 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 TYPE_3__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_non_call_exceptions ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_call_expr_in (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ctrl_altering_stmt (int /*<<< orphan*/ ) ; 
 scalar_t__ is_hidden_global_store (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_stmt_necessary (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  simple_goto_p (int /*<<< orphan*/ ) ; 
 TYPE_1__* stmt_ann (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_could_throw_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mark_stmt_if_obviously_necessary (tree stmt, bool aggressive)
{
  stmt_ann_t ann;
  tree op;

  /* With non-call exceptions, we have to assume that all statements could
     throw.  If a statement may throw, it is inherently necessary.  */
  if (flag_non_call_exceptions
      && tree_could_throw_p (stmt))
    {
      mark_stmt_necessary (stmt, true);
      return;
    }

  /* Statements that are implicitly live.  Most function calls, asm and return
     statements are required.  Labels and BIND_EXPR nodes are kept because
     they are control flow, and we have no way of knowing whether they can be
     removed.  DCE can eliminate all the other statements in a block, and CFG
     can then remove the block and labels.  */
  switch (TREE_CODE (stmt))
    {
    case BIND_EXPR:
    case LABEL_EXPR:
    case CASE_LABEL_EXPR:
      mark_stmt_necessary (stmt, false);
      return;

    case ASM_EXPR:
    case RESX_EXPR:
    case RETURN_EXPR:
      mark_stmt_necessary (stmt, true);
      return;

    case CALL_EXPR:
      /* Most, but not all function calls are required.  Function calls that
	 produce no result and have no side effects (i.e. const pure
	 functions) are unnecessary.  */
      if (TREE_SIDE_EFFECTS (stmt))
	mark_stmt_necessary (stmt, true);
      return;

    case MODIFY_EXPR:
      op = get_call_expr_in (stmt);
      if (op && TREE_SIDE_EFFECTS (op))
	{
	  mark_stmt_necessary (stmt, true);
	  return;
	}

      /* These values are mildly magic bits of the EH runtime.  We can't
	 see the entire lifetime of these values until landing pads are
	 generated.  */
      if (TREE_CODE (TREE_OPERAND (stmt, 0)) == EXC_PTR_EXPR
	  || TREE_CODE (TREE_OPERAND (stmt, 0)) == FILTER_EXPR)
	{
	  mark_stmt_necessary (stmt, true);
	  return;
	}
      break;

    case GOTO_EXPR:
      gcc_assert (!simple_goto_p (stmt));
      mark_stmt_necessary (stmt, true);
      return;

    case COND_EXPR:
      gcc_assert (EDGE_COUNT (bb_for_stmt (stmt)->succs) == 2);
      /* Fall through.  */

    case SWITCH_EXPR:
      if (! aggressive)
	mark_stmt_necessary (stmt, true);
      break;

    default:
      break;
    }

  ann = stmt_ann (stmt);

  /* If the statement has volatile operands, it needs to be preserved.
     Same for statements that can alter control flow in unpredictable
     ways.  */
  if (ann->has_volatile_ops || is_ctrl_altering_stmt (stmt))
    {
      mark_stmt_necessary (stmt, true);
      return;
    }

  if (is_hidden_global_store (stmt))
    {
      mark_stmt_necessary (stmt, true);
      return;
    }

  return;
}