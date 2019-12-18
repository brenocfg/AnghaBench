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
typedef  int /*<<< orphan*/ * edge ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ COND_EXPR ; 
 scalar_t__ LABEL_DECL ; 
 scalar_t__ LABEL_EXPR ; 
 scalar_t__ SWITCH_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ computed_goto_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_taken_edge_computed_goto (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_taken_edge_cond_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * find_taken_edge_switch_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  is_ctrl_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  last_stmt (int /*<<< orphan*/ ) ; 

edge
find_taken_edge (basic_block bb, tree val)
{
  tree stmt;

  stmt = last_stmt (bb);

  gcc_assert (stmt);
  gcc_assert (is_ctrl_stmt (stmt));
  gcc_assert (val);

  if (! is_gimple_min_invariant (val))
    return NULL;

  if (TREE_CODE (stmt) == COND_EXPR)
    return find_taken_edge_cond_expr (bb, val);

  if (TREE_CODE (stmt) == SWITCH_EXPR)
    return find_taken_edge_switch_expr (bb, val);

  if (computed_goto_p (stmt))
    {
      /* Only optimize if the argument is a label, if the argument is
	 not a label then we can not construct a proper CFG.

         It may be the case that we only need to allow the LABEL_REF to
         appear inside an ADDR_EXPR, but we also allow the LABEL_REF to
         appear inside a LABEL_EXPR just to be safe.  */
      if ((TREE_CODE (val) == ADDR_EXPR || TREE_CODE (val) == LABEL_EXPR)
	  && TREE_CODE (TREE_OPERAND (val, 0)) == LABEL_DECL)
	return find_taken_edge_computed_goto (bb, TREE_OPERAND (val, 0));
      return NULL;
    }

  gcc_unreachable ();
}