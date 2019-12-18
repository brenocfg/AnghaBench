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

/* Variables and functions */
 int /*<<< orphan*/  ADDR_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TARGET_EXPR_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_NEEDS_CONSTRUCTING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_indirect_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_unary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  get_target_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_lvalue_p (int /*<<< orphan*/ ) ; 

tree
stabilize_expr (tree exp, tree* initp)
{
  tree init_expr;

  if (!TREE_SIDE_EFFECTS (exp))
    init_expr = NULL_TREE;
  else if (!real_lvalue_p (exp)
	   || !TYPE_NEEDS_CONSTRUCTING (TREE_TYPE (exp)))
    {
      init_expr = get_target_expr (exp);
      exp = TARGET_EXPR_SLOT (init_expr);
    }
  else
    {
      exp = build_unary_op (ADDR_EXPR, exp, 1);
      init_expr = get_target_expr (exp);
      exp = TARGET_EXPR_SLOT (init_expr);
      exp = build_indirect_ref (exp, 0);
    }
  *initp = init_expr;

  gcc_assert (!TREE_SIDE_EFFECTS (exp));
  return exp;
}