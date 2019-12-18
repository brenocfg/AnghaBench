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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  GE_EXPR ; 
 int /*<<< orphan*/  LE_EXPR ; 
 scalar_t__ MAX_EXPR ; 
 scalar_t__ MIN_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_conditional_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_unary_op (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_x_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static tree
rationalize_conditional_expr (enum tree_code code, tree t)
{
  /* For MIN_EXPR or MAX_EXPR, fold-const.c has arranged things so that
     the first operand is always the one to be used if both operands
     are equal, so we know what conditional expression this used to be.  */
  if (TREE_CODE (t) == MIN_EXPR || TREE_CODE (t) == MAX_EXPR)
    {
      tree op0 = TREE_OPERAND (t, 0);
      tree op1 = TREE_OPERAND (t, 1);

      /* The following code is incorrect if either operand side-effects.  */
      gcc_assert (!TREE_SIDE_EFFECTS (op0)
		  && !TREE_SIDE_EFFECTS (op1));
      return
	build_conditional_expr (build_x_binary_op ((TREE_CODE (t) == MIN_EXPR
						    ? LE_EXPR : GE_EXPR),
						   op0, TREE_CODE (op0),
						   op1, TREE_CODE (op1),
						   /*overloaded_p=*/NULL),
			    build_unary_op (code, op0, 0),
			    build_unary_op (code, op1, 0));
    }

  return
    build_conditional_expr (TREE_OPERAND (t, 0),
			    build_unary_op (code, TREE_OPERAND (t, 1), 0),
			    build_unary_op (code, TREE_OPERAND (t, 2), 0));
}