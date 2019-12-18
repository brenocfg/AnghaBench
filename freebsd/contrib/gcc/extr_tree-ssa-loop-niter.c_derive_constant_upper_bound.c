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
typedef  int /*<<< orphan*/  double_int ;

/* Variables and functions */
#define  CONVERT_EXPR 134 
#define  EXACT_DIV_EXPR 133 
#define  FLOOR_DIV_EXPR 132 
#define  INTEGER_CST 131 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
#define  MINUS_EXPR 130 
#define  NOP_EXPR 129 
#define  PLUS_EXPR 128 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_neg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_negative_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_sext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_to_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_ucmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_int_udiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  implies_ge_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  implies_nonnegative_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_int_cst_sign_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_to_double_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_bound_in_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static double_int
derive_constant_upper_bound (tree val, tree additional)
{
  tree type = TREE_TYPE (val);
  tree op0, op1, subtype, maxt;
  double_int bnd, max, mmax, cst;

  if (INTEGRAL_TYPE_P (type))
    maxt = TYPE_MAX_VALUE (type);
  else
    maxt = upper_bound_in_type (type, type);

  max = tree_to_double_int (maxt);

  switch (TREE_CODE (val))
    {
    case INTEGER_CST:
      return tree_to_double_int (val);

    case NOP_EXPR:
    case CONVERT_EXPR:
      op0 = TREE_OPERAND (val, 0);
      subtype = TREE_TYPE (op0);
      if (!TYPE_UNSIGNED (subtype)
	  /* If TYPE is also signed, the fact that VAL is nonnegative implies
	     that OP0 is nonnegative.  */
	  && TYPE_UNSIGNED (type)
	  && !implies_nonnegative_p (additional, op0))
	{
	  /* If we cannot prove that the casted expression is nonnegative,
	     we cannot establish more useful upper bound than the precision
	     of the type gives us.  */
	  return max;
	}

      /* We now know that op0 is an nonnegative value.  Try deriving an upper
	 bound for it.  */
      bnd = derive_constant_upper_bound (op0, additional);

      /* If the bound does not fit in TYPE, max. value of TYPE could be
	 attained.  */
      if (double_int_ucmp (max, bnd) < 0)
	return max;

      return bnd;

    case PLUS_EXPR:
    case MINUS_EXPR:
      op0 = TREE_OPERAND (val, 0);
      op1 = TREE_OPERAND (val, 1);

      if (TREE_CODE (op1) != INTEGER_CST
	  || !implies_nonnegative_p (additional, op0))
	return max;

      /* Canonicalize to OP0 - CST.  Consider CST to be signed, in order to
	 choose the most logical way how to treat this constant regardless
	 of the signedness of the type.  */
      cst = tree_to_double_int (op1);
      cst = double_int_sext (cst, TYPE_PRECISION (type));
      if (TREE_CODE (val) == PLUS_EXPR)
	cst = double_int_neg (cst);

      bnd = derive_constant_upper_bound (op0, additional);

      if (double_int_negative_p (cst))
	{
	  cst = double_int_neg (cst);
	  /* Avoid CST == 0x80000...  */
	  if (double_int_negative_p (cst))
	    return max;;

	  /* OP0 + CST.  We need to check that
	     BND <= MAX (type) - CST.  */

	  mmax = double_int_add (max, double_int_neg (cst));
	  if (double_int_ucmp (bnd, mmax) > 0)
	    return max;

	  return double_int_add (bnd, cst);
	}
      else
	{
	  /* OP0 - CST, where CST >= 0.

	     If TYPE is signed, we have already verified that OP0 >= 0, and we
	     know that the result is nonnegative.  This implies that
	     VAL <= BND - CST.

	     If TYPE is unsigned, we must additionally know that OP0 >= CST,
	     otherwise the operation underflows.
	   */

	  /* This should only happen if the type is unsigned; however, for
	     programs that use overflowing signed arithmetics even with
	     -fno-wrapv, this condition may also be true for signed values.  */
	  if (double_int_ucmp (bnd, cst) < 0)
	    return max;

	  if (TYPE_UNSIGNED (type)
	      && !implies_ge_p (additional,
				op0, double_int_to_tree (type, cst)))
	    return max;

	  bnd = double_int_add (bnd, double_int_neg (cst));
	}

      return bnd;

    case FLOOR_DIV_EXPR:
    case EXACT_DIV_EXPR:
      op0 = TREE_OPERAND (val, 0);
      op1 = TREE_OPERAND (val, 1);
      if (TREE_CODE (op1) != INTEGER_CST
	  || tree_int_cst_sign_bit (op1))
	return max;

      bnd = derive_constant_upper_bound (op0, additional);
      return double_int_udiv (bnd, tree_to_double_int (op1), FLOOR_DIV_EXPR);

    default: 
      return max;
    }
}