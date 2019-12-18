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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  HONOR_SIGNED_ZEROS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LT_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ REAL_CST ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 scalar_t__ REAL_VALUE_NEGATIVE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REAL_CST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst0 ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tree_expr_nonnegative_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_signbit (tree fndecl, tree arglist)
{
  tree type = TREE_TYPE (TREE_TYPE (fndecl));
  tree arg, temp;

  if (!validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return NULL_TREE;

  arg = TREE_VALUE (arglist);

  /* If ARG is a compile-time constant, determine the result.  */
  if (TREE_CODE (arg) == REAL_CST
      && !TREE_CONSTANT_OVERFLOW (arg))
    {
      REAL_VALUE_TYPE c;

      c = TREE_REAL_CST (arg);
      temp = REAL_VALUE_NEGATIVE (c) ? integer_one_node : integer_zero_node;
      return fold_convert (type, temp);
    }

  /* If ARG is non-negative, the result is always zero.  */
  if (tree_expr_nonnegative_p (arg))
    return omit_one_operand (type, integer_zero_node, arg);

  /* If ARG's format doesn't have signed zeros, return "arg < 0.0".  */
  if (!HONOR_SIGNED_ZEROS (TYPE_MODE (TREE_TYPE (arg))))
    return fold_build2 (LT_EXPR, type, arg,
			build_real (TREE_TYPE (arg), dconst0));

  return NULL_TREE;
}