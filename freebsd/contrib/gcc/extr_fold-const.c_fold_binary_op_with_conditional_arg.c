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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CONSTANT (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ VOID_TYPE_P (scalar_t__) ; 
 scalar_t__ constant_boolean_node (int,scalar_t__) ; 
 scalar_t__ fold_build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build3 (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
fold_binary_op_with_conditional_arg (enum tree_code code,
				     tree type, tree op0, tree op1,
				     tree cond, tree arg, int cond_first_p)
{
  tree cond_type = cond_first_p ? TREE_TYPE (op0) : TREE_TYPE (op1);
  tree arg_type = cond_first_p ? TREE_TYPE (op1) : TREE_TYPE (op0);
  tree test, true_value, false_value;
  tree lhs = NULL_TREE;
  tree rhs = NULL_TREE;

  /* This transformation is only worthwhile if we don't have to wrap
     arg in a SAVE_EXPR, and the operation can be simplified on at least
     one of the branches once its pushed inside the COND_EXPR.  */
  if (!TREE_CONSTANT (arg))
    return NULL_TREE;

  if (TREE_CODE (cond) == COND_EXPR)
    {
      test = TREE_OPERAND (cond, 0);
      true_value = TREE_OPERAND (cond, 1);
      false_value = TREE_OPERAND (cond, 2);
      /* If this operand throws an expression, then it does not make
	 sense to try to perform a logical or arithmetic operation
	 involving it.  */
      if (VOID_TYPE_P (TREE_TYPE (true_value)))
	lhs = true_value;
      if (VOID_TYPE_P (TREE_TYPE (false_value)))
	rhs = false_value;
    }
  else
    {
      tree testtype = TREE_TYPE (cond);
      test = cond;
      true_value = constant_boolean_node (true, testtype);
      false_value = constant_boolean_node (false, testtype);
    }

  arg = fold_convert (arg_type, arg);
  if (lhs == 0)
    {
      true_value = fold_convert (cond_type, true_value);
      if (cond_first_p)
	lhs = fold_build2 (code, type, true_value, arg);
      else
	lhs = fold_build2 (code, type, arg, true_value);
    }
  if (rhs == 0)
    {
      false_value = fold_convert (cond_type, false_value);
      if (cond_first_p)
	rhs = fold_build2 (code, type, false_value, arg);
      else
	rhs = fold_build2 (code, type, arg, false_value);
    }

  test = fold_build3 (COND_EXPR, type, test, lhs, rhs);
  return fold_convert (type, test);
}