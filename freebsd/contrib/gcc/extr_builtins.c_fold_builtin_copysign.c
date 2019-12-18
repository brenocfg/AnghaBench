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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ REAL_CST ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_REAL_CST (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 scalar_t__ build_function_call_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_real (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_strip_sign_ops (scalar_t__) ; 
 scalar_t__ omit_one_operand (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  real_copysign (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ tree_expr_nonnegative_p (scalar_t__) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_copysign (tree fndecl, tree arglist, tree type)
{
  tree arg1, arg2, tem;

  if (!validate_arglist (arglist, REAL_TYPE, REAL_TYPE, VOID_TYPE))
    return NULL_TREE;

  arg1 = TREE_VALUE (arglist);
  arg2 = TREE_VALUE (TREE_CHAIN (arglist));

  /* copysign(X,X) is X.  */
  if (operand_equal_p (arg1, arg2, 0))
    return fold_convert (type, arg1);

  /* If ARG1 and ARG2 are compile-time constants, determine the result.  */
  if (TREE_CODE (arg1) == REAL_CST
      && TREE_CODE (arg2) == REAL_CST
      && !TREE_CONSTANT_OVERFLOW (arg1)
      && !TREE_CONSTANT_OVERFLOW (arg2))
    {
      REAL_VALUE_TYPE c1, c2;

      c1 = TREE_REAL_CST (arg1);
      c2 = TREE_REAL_CST (arg2);
      /* c1.sign := c2.sign.  */
      real_copysign (&c1, &c2);
      return build_real (type, c1);
    }

  /* copysign(X, Y) is fabs(X) when Y is always non-negative.
     Remember to evaluate Y for side-effects.  */
  if (tree_expr_nonnegative_p (arg2))
    return omit_one_operand (type,
			     fold_build1 (ABS_EXPR, type, arg1),
			     arg2);

  /* Strip sign changing operations for the first argument.  */
  tem = fold_strip_sign_ops (arg1);
  if (tem)
    {
      arglist = tree_cons (NULL_TREE, tem, TREE_CHAIN (arglist));
      return build_function_call_expr (fndecl, arglist);
    }

  return NULL_TREE;
}