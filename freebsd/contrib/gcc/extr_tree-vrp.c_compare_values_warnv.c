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
 int /*<<< orphan*/  GT_EXPR ; 
 int /*<<< orphan*/  LT_EXPR ; 
 scalar_t__ MINUS_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 int /*<<< orphan*/  NE_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_NO_WARNING (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_OVERFLOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_UNDEFINED (int /*<<< orphan*/ ) ; 
 scalar_t__ boolean_true_node ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ fold_binary (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_unary_to_constant (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  is_gimple_min_invariant (scalar_t__) ; 
 scalar_t__ is_negative_overflow_infinity (scalar_t__) ; 
 scalar_t__ is_positive_overflow_infinity (scalar_t__) ; 
 scalar_t__ operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int tree_int_cst_compare (scalar_t__,scalar_t__) ; 
 int tree_int_cst_sgn (scalar_t__) ; 

__attribute__((used)) static int
compare_values_warnv (tree val1, tree val2, bool *strict_overflow_p)
{
  if (val1 == val2)
    return 0;

  /* Below we rely on the fact that VAL1 and VAL2 are both pointers or
     both integers.  */
  gcc_assert (POINTER_TYPE_P (TREE_TYPE (val1))
	      == POINTER_TYPE_P (TREE_TYPE (val2)));

  if ((TREE_CODE (val1) == SSA_NAME
       || TREE_CODE (val1) == PLUS_EXPR
       || TREE_CODE (val1) == MINUS_EXPR)
      && (TREE_CODE (val2) == SSA_NAME
	  || TREE_CODE (val2) == PLUS_EXPR
	  || TREE_CODE (val2) == MINUS_EXPR))
    {
      tree n1, c1, n2, c2;
      enum tree_code code1, code2;
  
      /* If VAL1 and VAL2 are of the form 'NAME [+-] CST' or 'NAME',
	 return -1 or +1 accordingly.  If VAL1 and VAL2 don't use the
	 same name, return -2.  */
      if (TREE_CODE (val1) == SSA_NAME)
	{
	  code1 = SSA_NAME;
	  n1 = val1;
	  c1 = NULL_TREE;
	}
      else
	{
	  code1 = TREE_CODE (val1);
	  n1 = TREE_OPERAND (val1, 0);
	  c1 = TREE_OPERAND (val1, 1);
	  if (tree_int_cst_sgn (c1) == -1)
	    {
	      if (is_negative_overflow_infinity (c1))
		return -2;
	      c1 = fold_unary_to_constant (NEGATE_EXPR, TREE_TYPE (c1), c1);
	      if (!c1)
		return -2;
	      code1 = code1 == MINUS_EXPR ? PLUS_EXPR : MINUS_EXPR;
	    }
	}

      if (TREE_CODE (val2) == SSA_NAME)
	{
	  code2 = SSA_NAME;
	  n2 = val2;
	  c2 = NULL_TREE;
	}
      else
	{
	  code2 = TREE_CODE (val2);
	  n2 = TREE_OPERAND (val2, 0);
	  c2 = TREE_OPERAND (val2, 1);
	  if (tree_int_cst_sgn (c2) == -1)
	    {
	      if (is_negative_overflow_infinity (c2))
		return -2;
	      c2 = fold_unary_to_constant (NEGATE_EXPR, TREE_TYPE (c2), c2);
	      if (!c2)
		return -2;
	      code2 = code2 == MINUS_EXPR ? PLUS_EXPR : MINUS_EXPR;
	    }
	}

      /* Both values must use the same name.  */
      if (n1 != n2)
	return -2;

      if (code1 == SSA_NAME
	  && code2 == SSA_NAME)
	/* NAME == NAME  */
	return 0;

      /* If overflow is defined we cannot simplify more.  */
      if (!TYPE_OVERFLOW_UNDEFINED (TREE_TYPE (val1)))
	return -2;

      if (strict_overflow_p != NULL
	  && (code1 == SSA_NAME || !TREE_NO_WARNING (val1))
	  && (code2 == SSA_NAME || !TREE_NO_WARNING (val2)))
	*strict_overflow_p = true;

      if (code1 == SSA_NAME)
	{
	  if (code2 == PLUS_EXPR)
	    /* NAME < NAME + CST  */
	    return -1;
	  else if (code2 == MINUS_EXPR)
	    /* NAME > NAME - CST  */
	    return 1;
	}
      else if (code1 == PLUS_EXPR)
	{
	  if (code2 == SSA_NAME)
	    /* NAME + CST > NAME  */
	    return 1;
	  else if (code2 == PLUS_EXPR)
	    /* NAME + CST1 > NAME + CST2, if CST1 > CST2  */
	    return compare_values_warnv (c1, c2, strict_overflow_p);
	  else if (code2 == MINUS_EXPR)
	    /* NAME + CST1 > NAME - CST2  */
	    return 1;
	}
      else if (code1 == MINUS_EXPR)
	{
	  if (code2 == SSA_NAME)
	    /* NAME - CST < NAME  */
	    return -1;
	  else if (code2 == PLUS_EXPR)
	    /* NAME - CST1 < NAME + CST2  */
	    return -1;
	  else if (code2 == MINUS_EXPR)
	    /* NAME - CST1 > NAME - CST2, if CST1 < CST2.  Notice that
	       C1 and C2 are swapped in the call to compare_values.  */
	    return compare_values_warnv (c2, c1, strict_overflow_p);
	}

      gcc_unreachable ();
    }

  /* We cannot compare non-constants.  */
  if (!is_gimple_min_invariant (val1) || !is_gimple_min_invariant (val2))
    return -2;

  if (!POINTER_TYPE_P (TREE_TYPE (val1)))
    {
      /* We cannot compare overflowed values, except for overflow
	 infinities.  */
      if (TREE_OVERFLOW (val1) || TREE_OVERFLOW (val2))
	{
	  if (strict_overflow_p != NULL)
	    *strict_overflow_p = true;
	  if (is_negative_overflow_infinity (val1))
	    return is_negative_overflow_infinity (val2) ? 0 : -1;
	  else if (is_negative_overflow_infinity (val2))
	    return 1;
	  else if (is_positive_overflow_infinity (val1))
	    return is_positive_overflow_infinity (val2) ? 0 : 1;
	  else if (is_positive_overflow_infinity (val2))
	    return -1;
	  return -2;
	}

      return tree_int_cst_compare (val1, val2);
    }
  else
    {
      tree t;

      /* First see if VAL1 and VAL2 are not the same.  */
      if (val1 == val2 || operand_equal_p (val1, val2, 0))
	return 0;
      
      /* If VAL1 is a lower address than VAL2, return -1.  */
      t = fold_binary (LT_EXPR, boolean_type_node, val1, val2);
      if (t == boolean_true_node)
	return -1;

      /* If VAL1 is a higher address than VAL2, return +1.  */
      t = fold_binary (GT_EXPR, boolean_type_node, val1, val2);
      if (t == boolean_true_node)
	return 1;

      /* If VAL1 is different than VAL2, return +2.  */
      t = fold_binary (NE_EXPR, boolean_type_node, val1, val2);
      if (t == boolean_true_node)
	return 2;

      return -2;
    }
}