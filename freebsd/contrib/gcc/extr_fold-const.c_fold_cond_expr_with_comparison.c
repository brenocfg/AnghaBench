#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_3__ {int /*<<< orphan*/  (* signed_type ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  name; TYPE_1__ types; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_EXPR ; 
 int /*<<< orphan*/  COND_EXPR ; 
#define  EQ_EXPR 139 
 scalar_t__ FLOAT_TYPE_P (int /*<<< orphan*/ ) ; 
#define  GE_EXPR 138 
#define  GT_EXPR 137 
 int /*<<< orphan*/  HONOR_NANS (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGRAL_TYPE_P (int /*<<< orphan*/ ) ; 
#define  LE_EXPR 136 
#define  LTGT_EXPR 135 
#define  LT_EXPR 134 
 int /*<<< orphan*/  MAX_EXPR ; 
 scalar_t__ MINUS_EXPR ; 
 int /*<<< orphan*/  MIN_EXPR ; 
 scalar_t__ NEGATE_EXPR ; 
#define  NE_EXPR 133 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OEP_ONLY_CONST ; 
 scalar_t__ PLUS_EXPR ; 
 int /*<<< orphan*/  STRIP_NOPS (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
#define  UNEQ_EXPR 132 
#define  UNGE_EXPR 131 
#define  UNGT_EXPR 130 
#define  UNLE_EXPR 129 
#define  UNLT_EXPR 128 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_binop (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_trapping_math ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ in_gimple_form ; 
 int /*<<< orphan*/  integer_one_node ; 
 scalar_t__ integer_zerop (int /*<<< orphan*/ ) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  maybe_lvalue_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  negate_expr (int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_for_comparison_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pedantic_non_lvalue (int /*<<< orphan*/ ) ; 
 scalar_t__ real_zerop (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcc_comparison ; 

__attribute__((used)) static tree
fold_cond_expr_with_comparison (tree type, tree arg0, tree arg1, tree arg2)
{
  enum tree_code comp_code = TREE_CODE (arg0);
  tree arg00 = TREE_OPERAND (arg0, 0);
  tree arg01 = TREE_OPERAND (arg0, 1);
  tree arg1_type = TREE_TYPE (arg1);
  tree tem;

  STRIP_NOPS (arg1);
  STRIP_NOPS (arg2);

  /* If we have A op 0 ? A : -A, consider applying the following
     transformations:

     A == 0? A : -A    same as -A
     A != 0? A : -A    same as A
     A >= 0? A : -A    same as abs (A)
     A > 0?  A : -A    same as abs (A)
     A <= 0? A : -A    same as -abs (A)
     A < 0?  A : -A    same as -abs (A)

     None of these transformations work for modes with signed
     zeros.  If A is +/-0, the first two transformations will
     change the sign of the result (from +0 to -0, or vice
     versa).  The last four will fix the sign of the result,
     even though the original expressions could be positive or
     negative, depending on the sign of A.

     Note that all these transformations are correct if A is
     NaN, since the two alternatives (A and -A) are also NaNs.  */
  if ((FLOAT_TYPE_P (TREE_TYPE (arg01))
       ? real_zerop (arg01)
       : integer_zerop (arg01))
      && ((TREE_CODE (arg2) == NEGATE_EXPR
	   && operand_equal_p (TREE_OPERAND (arg2, 0), arg1, 0))
	     /* In the case that A is of the form X-Y, '-A' (arg2) may
	        have already been folded to Y-X, check for that. */
	  || (TREE_CODE (arg1) == MINUS_EXPR
	      && TREE_CODE (arg2) == MINUS_EXPR
	      && operand_equal_p (TREE_OPERAND (arg1, 0),
				  TREE_OPERAND (arg2, 1), 0)
	      && operand_equal_p (TREE_OPERAND (arg1, 1),
				  TREE_OPERAND (arg2, 0), 0))))
    switch (comp_code)
      {
      case EQ_EXPR:
      case UNEQ_EXPR:
	tem = fold_convert (arg1_type, arg1);
	return pedantic_non_lvalue (fold_convert (type, negate_expr (tem)));
      case NE_EXPR:
      case LTGT_EXPR:
	return pedantic_non_lvalue (fold_convert (type, arg1));
      case UNGE_EXPR:
      case UNGT_EXPR:
	if (flag_trapping_math)
	  break;
	/* Fall through.  */
      case GE_EXPR:
      case GT_EXPR:
	if (TYPE_UNSIGNED (TREE_TYPE (arg1)))
	  arg1 = fold_convert (lang_hooks.types.signed_type
			       (TREE_TYPE (arg1)), arg1);
	tem = fold_build1 (ABS_EXPR, TREE_TYPE (arg1), arg1);
	return pedantic_non_lvalue (fold_convert (type, tem));
      case UNLE_EXPR:
      case UNLT_EXPR:
	if (flag_trapping_math)
	  break;
      case LE_EXPR:
      case LT_EXPR:
	if (TYPE_UNSIGNED (TREE_TYPE (arg1)))
	  arg1 = fold_convert (lang_hooks.types.signed_type
			       (TREE_TYPE (arg1)), arg1);
	tem = fold_build1 (ABS_EXPR, TREE_TYPE (arg1), arg1);
	return negate_expr (fold_convert (type, tem));
      default:
	gcc_assert (TREE_CODE_CLASS (comp_code) == tcc_comparison);
	break;
      }

  /* A != 0 ? A : 0 is simply A, unless A is -0.  Likewise
     A == 0 ? A : 0 is always 0 unless A is -0.  Note that
     both transformations are correct when A is NaN: A != 0
     is then true, and A == 0 is false.  */

  if (integer_zerop (arg01) && integer_zerop (arg2))
    {
      if (comp_code == NE_EXPR)
	return pedantic_non_lvalue (fold_convert (type, arg1));
      else if (comp_code == EQ_EXPR)
	return build_int_cst (type, 0);
    }

  /* Try some transformations of A op B ? A : B.

     A == B? A : B    same as B
     A != B? A : B    same as A
     A >= B? A : B    same as max (A, B)
     A > B?  A : B    same as max (B, A)
     A <= B? A : B    same as min (A, B)
     A < B?  A : B    same as min (B, A)

     As above, these transformations don't work in the presence
     of signed zeros.  For example, if A and B are zeros of
     opposite sign, the first two transformations will change
     the sign of the result.  In the last four, the original
     expressions give different results for (A=+0, B=-0) and
     (A=-0, B=+0), but the transformed expressions do not.

     The first two transformations are correct if either A or B
     is a NaN.  In the first transformation, the condition will
     be false, and B will indeed be chosen.  In the case of the
     second transformation, the condition A != B will be true,
     and A will be chosen.

     The conversions to max() and min() are not correct if B is
     a number and A is not.  The conditions in the original
     expressions will be false, so all four give B.  The min()
     and max() versions would give a NaN instead.  */
  if (operand_equal_for_comparison_p (arg01, arg2, arg00)
      /* Avoid these transformations if the COND_EXPR may be used
	 as an lvalue in the C++ front-end.  PR c++/19199.  */
      && (in_gimple_form
	  || (strcmp (lang_hooks.name, "GNU C++") != 0
	      && strcmp (lang_hooks.name, "GNU Objective-C++") != 0)
	  || ! maybe_lvalue_p (arg1)
	  || ! maybe_lvalue_p (arg2)))
    {
      tree comp_op0 = arg00;
      tree comp_op1 = arg01;
      tree comp_type = TREE_TYPE (comp_op0);

      /* Avoid adding NOP_EXPRs in case this is an lvalue.  */
      if (TYPE_MAIN_VARIANT (comp_type) == TYPE_MAIN_VARIANT (type))
	{
	  comp_type = type;
	  comp_op0 = arg1;
	  comp_op1 = arg2;
	}

      switch (comp_code)
	{
	case EQ_EXPR:
	  return pedantic_non_lvalue (fold_convert (type, arg2));
	case NE_EXPR:
	  return pedantic_non_lvalue (fold_convert (type, arg1));
	case LE_EXPR:
	case LT_EXPR:
	case UNLE_EXPR:
	case UNLT_EXPR:
	  /* In C++ a ?: expression can be an lvalue, so put the
	     operand which will be used if they are equal first
	     so that we can convert this back to the
	     corresponding COND_EXPR.  */
	  if (!HONOR_NANS (TYPE_MODE (TREE_TYPE (arg1))))
	    {
	      comp_op0 = fold_convert (comp_type, comp_op0);
	      comp_op1 = fold_convert (comp_type, comp_op1);
	      tem = (comp_code == LE_EXPR || comp_code == UNLE_EXPR)
		    ? fold_build2 (MIN_EXPR, comp_type, comp_op0, comp_op1)
		    : fold_build2 (MIN_EXPR, comp_type, comp_op1, comp_op0);
	      return pedantic_non_lvalue (fold_convert (type, tem));
	    }
	  break;
	case GE_EXPR:
	case GT_EXPR:
	case UNGE_EXPR:
	case UNGT_EXPR:
	  if (!HONOR_NANS (TYPE_MODE (TREE_TYPE (arg1))))
	    {
	      comp_op0 = fold_convert (comp_type, comp_op0);
	      comp_op1 = fold_convert (comp_type, comp_op1);
	      tem = (comp_code == GE_EXPR || comp_code == UNGE_EXPR)
		    ? fold_build2 (MAX_EXPR, comp_type, comp_op0, comp_op1)
		    : fold_build2 (MAX_EXPR, comp_type, comp_op1, comp_op0);
	      return pedantic_non_lvalue (fold_convert (type, tem));
	    }
	  break;
	case UNEQ_EXPR:
	  if (!HONOR_NANS (TYPE_MODE (TREE_TYPE (arg1))))
	    return pedantic_non_lvalue (fold_convert (type, arg2));
	  break;
	case LTGT_EXPR:
	  if (!HONOR_NANS (TYPE_MODE (TREE_TYPE (arg1))))
	    return pedantic_non_lvalue (fold_convert (type, arg1));
	  break;
	default:
	  gcc_assert (TREE_CODE_CLASS (comp_code) == tcc_comparison);
	  break;
	}
    }

  /* If this is A op C1 ? A : C2 with C1 and C2 constant integers,
     we might still be able to simplify this.  For example,
     if C1 is one less or one more than C2, this might have started
     out as a MIN or MAX and been transformed by this function.
     Only good for INTEGER_TYPEs, because we need TYPE_MAX_VALUE.  */

  if (INTEGRAL_TYPE_P (type)
      && TREE_CODE (arg01) == INTEGER_CST
      && TREE_CODE (arg2) == INTEGER_CST)
    switch (comp_code)
      {
      case EQ_EXPR:
	/* We can replace A with C1 in this case.  */
	arg1 = fold_convert (type, arg01);
	return fold_build3 (COND_EXPR, type, arg0, arg1, arg2);

      case LT_EXPR:
	/* If C1 is C2 + 1, this is min(A, C2).  */
	if (! operand_equal_p (arg2, TYPE_MAX_VALUE (type),
			       OEP_ONLY_CONST)
	    && operand_equal_p (arg01,
				const_binop (PLUS_EXPR, arg2,
					     integer_one_node, 0),
				OEP_ONLY_CONST))
	  return pedantic_non_lvalue (fold_build2 (MIN_EXPR,
						   type, arg1, arg2));
	break;

      case LE_EXPR:
	/* If C1 is C2 - 1, this is min(A, C2).  */
	if (! operand_equal_p (arg2, TYPE_MIN_VALUE (type),
			       OEP_ONLY_CONST)
	    && operand_equal_p (arg01,
				const_binop (MINUS_EXPR, arg2,
					     integer_one_node, 0),
				OEP_ONLY_CONST))
	  return pedantic_non_lvalue (fold_build2 (MIN_EXPR,
						   type, arg1, arg2));
	break;

      case GT_EXPR:
	/* If C1 is C2 - 1, this is max(A, C2).  */
	if (! operand_equal_p (arg2, TYPE_MIN_VALUE (type),
			       OEP_ONLY_CONST)
	    && operand_equal_p (arg01,
				const_binop (MINUS_EXPR, arg2,
					     integer_one_node, 0),
				OEP_ONLY_CONST))
	  return pedantic_non_lvalue (fold_build2 (MAX_EXPR,
						   type, arg1, arg2));
	break;

      case GE_EXPR:
	/* If C1 is C2 + 1, this is max(A, C2).  */
	if (! operand_equal_p (arg2, TYPE_MAX_VALUE (type),
			       OEP_ONLY_CONST)
	    && operand_equal_p (arg01,
				const_binop (PLUS_EXPR, arg2,
					     integer_one_node, 0),
				OEP_ONLY_CONST))
	  return pedantic_non_lvalue (fold_build2 (MAX_EXPR,
						   type, arg1, arg2));
	break;
      case NE_EXPR:
	break;
      default:
	gcc_unreachable ();
      }

  return NULL_TREE;
}