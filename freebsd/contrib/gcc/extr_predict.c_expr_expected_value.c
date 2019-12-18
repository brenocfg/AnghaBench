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
typedef  int /*<<< orphan*/ * tree ;
typedef  int /*<<< orphan*/  bitmap ;

/* Variables and functions */
 scalar_t__ BINARY_CLASS_P (int /*<<< orphan*/ *) ; 
 scalar_t__ BUILT_IN_EXPECT ; 
 scalar_t__ BUILT_IN_NORMAL ; 
 scalar_t__ CALL_EXPR ; 
 scalar_t__ COMPARISON_CLASS_P (int /*<<< orphan*/ *) ; 
 scalar_t__ DECL_BUILT_IN_CLASS (int /*<<< orphan*/ *) ; 
 scalar_t__ DECL_FUNCTION_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ MODIFY_EXPR ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 int /*<<< orphan*/ * PHI_ARG_DEF (int /*<<< orphan*/ *,int) ; 
 scalar_t__ PHI_NODE ; 
 int PHI_NUM_ARGS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PHI_RESULT (int /*<<< orphan*/ *) ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/ * SSA_NAME_DEF_STMT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSA_NAME_VERSION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 scalar_t__ TREE_CONSTANT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_VALUE (int /*<<< orphan*/ *) ; 
 scalar_t__ UNARY_CLASS_P (int /*<<< orphan*/ *) ; 
 scalar_t__ bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fold_build1 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fold_build2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_callee_fndecl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  operand_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static tree
expr_expected_value (tree expr, bitmap visited)
{
  if (TREE_CONSTANT (expr))
    return expr;
  else if (TREE_CODE (expr) == SSA_NAME)
    {
      tree def = SSA_NAME_DEF_STMT (expr);

      /* If we were already here, break the infinite cycle.  */
      if (bitmap_bit_p (visited, SSA_NAME_VERSION (expr)))
	return NULL;
      bitmap_set_bit (visited, SSA_NAME_VERSION (expr));

      if (TREE_CODE (def) == PHI_NODE)
	{
	  /* All the arguments of the PHI node must have the same constant
	     length.  */
	  int i;
	  tree val = NULL, new_val;

	  for (i = 0; i < PHI_NUM_ARGS (def); i++)
	    {
	      tree arg = PHI_ARG_DEF (def, i);

	      /* If this PHI has itself as an argument, we cannot
		 determine the string length of this argument.  However,
		 if we can find an expected constant value for the other
		 PHI args then we can still be sure that this is
		 likely a constant.  So be optimistic and just
		 continue with the next argument.  */
	      if (arg == PHI_RESULT (def))
		continue;

	      new_val = expr_expected_value (arg, visited);
	      if (!new_val)
		return NULL;
	      if (!val)
		val = new_val;
	      else if (!operand_equal_p (val, new_val, false))
		return NULL;
	    }
	  return val;
	}
      if (TREE_CODE (def) != MODIFY_EXPR || TREE_OPERAND (def, 0) != expr)
	return NULL;
      return expr_expected_value (TREE_OPERAND (def, 1), visited);
    }
  else if (TREE_CODE (expr) == CALL_EXPR)
    {
      tree decl = get_callee_fndecl (expr);
      if (!decl)
	return NULL;
      if (DECL_BUILT_IN_CLASS (decl) == BUILT_IN_NORMAL
	  && DECL_FUNCTION_CODE (decl) == BUILT_IN_EXPECT)
	{
	  tree arglist = TREE_OPERAND (expr, 1);
	  tree val;

	  if (arglist == NULL_TREE
	      || TREE_CHAIN (arglist) == NULL_TREE)
	    return NULL; 
	  val = TREE_VALUE (TREE_CHAIN (TREE_OPERAND (expr, 1)));
	  if (TREE_CONSTANT (val))
	    return val;
	  return TREE_VALUE (TREE_CHAIN (TREE_OPERAND (expr, 1)));
	}
    }
  if (BINARY_CLASS_P (expr) || COMPARISON_CLASS_P (expr))
    {
      tree op0, op1, res;
      op0 = expr_expected_value (TREE_OPERAND (expr, 0), visited);
      if (!op0)
	return NULL;
      op1 = expr_expected_value (TREE_OPERAND (expr, 1), visited);
      if (!op1)
	return NULL;
      res = fold_build2 (TREE_CODE (expr), TREE_TYPE (expr), op0, op1);
      if (TREE_CONSTANT (res))
	return res;
      return NULL;
    }
  if (UNARY_CLASS_P (expr))
    {
      tree op0, res;
      op0 = expr_expected_value (TREE_OPERAND (expr, 0), visited);
      if (!op0)
	return NULL;
      res = fold_build1 (TREE_CODE (expr), TREE_TYPE (expr), op0);
      if (TREE_CONSTANT (res))
	return res;
      return NULL;
    }
  return NULL;
}