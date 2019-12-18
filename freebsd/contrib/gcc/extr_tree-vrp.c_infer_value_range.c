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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {int /*<<< orphan*/  succs; } ;

/* Variables and functions */
 scalar_t__ EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int ERROR_MARK ; 
 int NE_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME_OCCURS_IN_ABNORMAL_PHI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 TYPE_1__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  count_uses_and_derefs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*,unsigned int*,int*) ; 
 scalar_t__ flag_delete_null_pointer_checks ; 
 scalar_t__ stmt_ends_bb_p (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_could_throw_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
infer_value_range (tree stmt, tree op, enum tree_code *comp_code_p, tree *val_p)
{
  *val_p = NULL_TREE;
  *comp_code_p = ERROR_MARK;

  /* Do not attempt to infer anything in names that flow through
     abnormal edges.  */
  if (SSA_NAME_OCCURS_IN_ABNORMAL_PHI (op))
    return false;

  /* Similarly, don't infer anything from statements that may throw
     exceptions.  */
  if (tree_could_throw_p (stmt))
    return false;

  /* If STMT is the last statement of a basic block with no
     successors, there is no point inferring anything about any of its
     operands.  We would not be able to find a proper insertion point
     for the assertion, anyway.  */
  if (stmt_ends_bb_p (stmt) && EDGE_COUNT (bb_for_stmt (stmt)->succs) == 0)
    return false;

  /* We can only assume that a pointer dereference will yield
     non-NULL if -fdelete-null-pointer-checks is enabled.  */
  if (flag_delete_null_pointer_checks && POINTER_TYPE_P (TREE_TYPE (op)))
    {
      bool is_store;
      unsigned num_uses, num_derefs;

      count_uses_and_derefs (op, stmt, &num_uses, &num_derefs, &is_store);
      if (num_derefs > 0)
	{
	  *val_p = build_int_cst (TREE_TYPE (op), 0);
	  *comp_code_p = NE_EXPR;
	  return true;
	}
    }

  return false;
}