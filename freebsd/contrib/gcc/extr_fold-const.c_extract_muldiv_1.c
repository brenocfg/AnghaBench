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
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_3__ {scalar_t__ (* signed_type ) (scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
#define  ABS_EXPR 145 
 int /*<<< orphan*/  BINARY_CLASS_P (scalar_t__) ; 
#define  CEIL_DIV_EXPR 144 
 int CEIL_MOD_EXPR ; 
 int /*<<< orphan*/  COMPARISON_CLASS_P (scalar_t__) ; 
#define  CONVERT_EXPR 143 
#define  EXACT_DIV_EXPR 142 
 int /*<<< orphan*/  EXPRESSION_CLASS_P (scalar_t__) ; 
#define  FLOOR_DIV_EXPR 141 
 int FLOOR_MOD_EXPR ; 
 scalar_t__ GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
#define  INTEGER_CST 140 
 int const INTEGER_TYPE ; 
#define  LSHIFT_EXPR 139 
#define  MAX_EXPR 138 
#define  MINUS_EXPR 137 
#define  MIN_EXPR 136 
#define  MULT_EXPR 135 
#define  NEGATE_EXPR 134 
#define  NON_LVALUE_EXPR 133 
#define  NOP_EXPR 132 
 scalar_t__ NULL_TREE ; 
#define  PLUS_EXPR 131 
#define  ROUND_DIV_EXPR 130 
 int ROUND_MOD_EXPR ; 
#define  RSHIFT_EXPR 129 
 int const TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_HIGH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_OVERFLOW (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TRUNC_DIV_EXPR 128 
 int TRUNC_MOD_EXPR ; 
 int /*<<< orphan*/  TYPE_IS_SIZETYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_UNDEFINED (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_WRAPS (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PRECISION (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (scalar_t__) ; 
 int /*<<< orphan*/  UNARY_CLASS_P (scalar_t__) ; 
 scalar_t__ build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ const_binop (int const,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ extract_muldiv (scalar_t__,scalar_t__,int,scalar_t__,int*) ; 
 scalar_t__ fold_build1 (int,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  multiple_of_p (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ negate_expr (scalar_t__) ; 
 scalar_t__ omit_one_operand (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ size_one_node ; 
 scalar_t__ stub1 (scalar_t__) ; 
 scalar_t__ tcc_binary ; 
 scalar_t__ tcc_unary ; 
 int tree_int_cst_sgn (scalar_t__) ; 

__attribute__((used)) static tree
extract_muldiv_1 (tree t, tree c, enum tree_code code, tree wide_type,
		  bool *strict_overflow_p)
{
  tree type = TREE_TYPE (t);
  enum tree_code tcode = TREE_CODE (t);
  tree ctype = (wide_type != 0 && (GET_MODE_SIZE (TYPE_MODE (wide_type))
				   > GET_MODE_SIZE (TYPE_MODE (type)))
		? wide_type : type);
  tree t1, t2;
  int same_p = tcode == code;
  tree op0 = NULL_TREE, op1 = NULL_TREE;
  bool sub_strict_overflow_p;

  /* Don't deal with constants of zero here; they confuse the code below.  */
  if (integer_zerop (c))
    return NULL_TREE;

  if (TREE_CODE_CLASS (tcode) == tcc_unary)
    op0 = TREE_OPERAND (t, 0);

  if (TREE_CODE_CLASS (tcode) == tcc_binary)
    op0 = TREE_OPERAND (t, 0), op1 = TREE_OPERAND (t, 1);

  /* Note that we need not handle conditional operations here since fold
     already handles those cases.  So just do arithmetic here.  */
  switch (tcode)
    {
    case INTEGER_CST:
      /* For a constant, we can always simplify if we are a multiply
	 or (for divide and modulus) if it is a multiple of our constant.  */
      if (code == MULT_EXPR
	  || integer_zerop (const_binop (TRUNC_MOD_EXPR, t, c, 0)))
	return const_binop (code, fold_convert (ctype, t),
			    fold_convert (ctype, c), 0);
      break;

    case CONVERT_EXPR:  case NON_LVALUE_EXPR:  case NOP_EXPR:
      /* If op0 is an expression ...  */
      if ((COMPARISON_CLASS_P (op0)
	   || UNARY_CLASS_P (op0)
	   || BINARY_CLASS_P (op0)
	   || EXPRESSION_CLASS_P (op0))
	  /* ... and is unsigned, and its type is smaller than ctype,
	     then we cannot pass through as widening.  */
	  && ((TYPE_UNSIGNED (TREE_TYPE (op0))
	       && ! (TREE_CODE (TREE_TYPE (op0)) == INTEGER_TYPE
		     && TYPE_IS_SIZETYPE (TREE_TYPE (op0)))
	       && (GET_MODE_SIZE (TYPE_MODE (ctype))
	           > GET_MODE_SIZE (TYPE_MODE (TREE_TYPE (op0)))))
	      /* ... or this is a truncation (t is narrower than op0),
		 then we cannot pass through this narrowing.  */
	      || (GET_MODE_SIZE (TYPE_MODE (type))
		  < GET_MODE_SIZE (TYPE_MODE (TREE_TYPE (op0))))
	      /* ... or signedness changes for division or modulus,
		 then we cannot pass through this conversion.  */
	      || (code != MULT_EXPR
		  && (TYPE_UNSIGNED (ctype)
		      != TYPE_UNSIGNED (TREE_TYPE (op0))))))
	break;

      /* Pass the constant down and see if we can make a simplification.  If
	 we can, replace this expression with the inner simplification for
	 possible later conversion to our or some other type.  */
      if ((t2 = fold_convert (TREE_TYPE (op0), c)) != 0
	  && TREE_CODE (t2) == INTEGER_CST
	  && ! TREE_CONSTANT_OVERFLOW (t2)
	  && (0 != (t1 = extract_muldiv (op0, t2, code,
					 code == MULT_EXPR
					 ? ctype : NULL_TREE,
					 strict_overflow_p))))
	return t1;
      break;

    case ABS_EXPR:
      /* If widening the type changes it from signed to unsigned, then we
         must avoid building ABS_EXPR itself as unsigned.  */
      if (TYPE_UNSIGNED (ctype) && !TYPE_UNSIGNED (type))
        {
          tree cstype = (*lang_hooks.types.signed_type) (ctype);
          if ((t1 = extract_muldiv (op0, c, code, cstype, strict_overflow_p))
	      != 0)
            {
              t1 = fold_build1 (tcode, cstype, fold_convert (cstype, t1));
              return fold_convert (ctype, t1);
            }
          break;
        }
      /* If the constant is negative, we cannot simplify this.  */
      if (tree_int_cst_sgn (c) == -1)
	break;
      /* FALLTHROUGH */
    case NEGATE_EXPR:
      if ((t1 = extract_muldiv (op0, c, code, wide_type, strict_overflow_p))
	  != 0)
	return fold_build1 (tcode, ctype, fold_convert (ctype, t1));
      break;

    case MIN_EXPR:  case MAX_EXPR:
      /* If widening the type changes the signedness, then we can't perform
	 this optimization as that changes the result.  */
      if (TYPE_UNSIGNED (ctype) != TYPE_UNSIGNED (type))
	break;

      /* MIN (a, b) / 5 -> MIN (a / 5, b / 5)  */
      sub_strict_overflow_p = false;
      if ((t1 = extract_muldiv (op0, c, code, wide_type,
				&sub_strict_overflow_p)) != 0
	  && (t2 = extract_muldiv (op1, c, code, wide_type,
				   &sub_strict_overflow_p)) != 0)
	{
	  if (tree_int_cst_sgn (c) < 0)
	    tcode = (tcode == MIN_EXPR ? MAX_EXPR : MIN_EXPR);
	  if (sub_strict_overflow_p)
	    *strict_overflow_p = true;
	  return fold_build2 (tcode, ctype, fold_convert (ctype, t1),
			      fold_convert (ctype, t2));
	}
      break;

    case LSHIFT_EXPR:  case RSHIFT_EXPR:
      /* If the second operand is constant, this is a multiplication
	 or floor division, by a power of two, so we can treat it that
	 way unless the multiplier or divisor overflows.  Signed
	 left-shift overflow is implementation-defined rather than
	 undefined in C90, so do not convert signed left shift into
	 multiplication.  */
      if (TREE_CODE (op1) == INTEGER_CST
	  && (tcode == RSHIFT_EXPR || TYPE_UNSIGNED (TREE_TYPE (op0)))
	  /* const_binop may not detect overflow correctly,
	     so check for it explicitly here.  */
	  && TYPE_PRECISION (TREE_TYPE (size_one_node)) > TREE_INT_CST_LOW (op1)
	  && TREE_INT_CST_HIGH (op1) == 0
	  && 0 != (t1 = fold_convert (ctype,
				      const_binop (LSHIFT_EXPR,
						   size_one_node,
						   op1, 0)))
	  && ! TREE_OVERFLOW (t1))
	return extract_muldiv (build2 (tcode == LSHIFT_EXPR
				       ? MULT_EXPR : FLOOR_DIV_EXPR,
				       ctype, fold_convert (ctype, op0), t1),
			       c, code, wide_type, strict_overflow_p);
      break;

    case PLUS_EXPR:  case MINUS_EXPR:
      /* See if we can eliminate the operation on both sides.  If we can, we
	 can return a new PLUS or MINUS.  If we can't, the only remaining
	 cases where we can do anything are if the second operand is a
	 constant.  */
      sub_strict_overflow_p = false;
      t1 = extract_muldiv (op0, c, code, wide_type, &sub_strict_overflow_p);
      t2 = extract_muldiv (op1, c, code, wide_type, &sub_strict_overflow_p);
      if (t1 != 0 && t2 != 0
	  && (code == MULT_EXPR
	      /* If not multiplication, we can only do this if both operands
		 are divisible by c.  */
	      || (multiple_of_p (ctype, op0, c)
	          && multiple_of_p (ctype, op1, c))))
	{
	  if (sub_strict_overflow_p)
	    *strict_overflow_p = true;
	  return fold_build2 (tcode, ctype, fold_convert (ctype, t1),
			      fold_convert (ctype, t2));
	}

      /* If this was a subtraction, negate OP1 and set it to be an addition.
	 This simplifies the logic below.  */
      if (tcode == MINUS_EXPR)
	tcode = PLUS_EXPR, op1 = negate_expr (op1);

      if (TREE_CODE (op1) != INTEGER_CST)
	break;

      /* If either OP1 or C are negative, this optimization is not safe for
	 some of the division and remainder types while for others we need
	 to change the code.  */
      if (tree_int_cst_sgn (op1) < 0 || tree_int_cst_sgn (c) < 0)
	{
	  if (code == CEIL_DIV_EXPR)
	    code = FLOOR_DIV_EXPR;
	  else if (code == FLOOR_DIV_EXPR)
	    code = CEIL_DIV_EXPR;
	  else if (code != MULT_EXPR
		   && code != CEIL_MOD_EXPR && code != FLOOR_MOD_EXPR)
	    break;
	}

      /* If it's a multiply or a division/modulus operation of a multiple
         of our constant, do the operation and verify it doesn't overflow.  */
      if (code == MULT_EXPR
	  || integer_zerop (const_binop (TRUNC_MOD_EXPR, op1, c, 0)))
	{
	  op1 = const_binop (code, fold_convert (ctype, op1),
			     fold_convert (ctype, c), 0);
	  /* We allow the constant to overflow with wrapping semantics.  */
	  if (op1 == 0
	      || (TREE_OVERFLOW (op1) && !TYPE_OVERFLOW_WRAPS (ctype)))
	    break;
	}
      else
	break;

      /* If we have an unsigned type is not a sizetype, we cannot widen
	 the operation since it will change the result if the original
	 computation overflowed.  */
      if (TYPE_UNSIGNED (ctype)
	  && ! (TREE_CODE (ctype) == INTEGER_TYPE && TYPE_IS_SIZETYPE (ctype))
	  && ctype != type)
	break;

      /* If we were able to eliminate our operation from the first side,
	 apply our operation to the second side and reform the PLUS.  */
      if (t1 != 0 && (TREE_CODE (t1) != code || code == MULT_EXPR))
	return fold_build2 (tcode, ctype, fold_convert (ctype, t1), op1);

      /* The last case is if we are a multiply.  In that case, we can
	 apply the distributive law to commute the multiply and addition
	 if the multiplication of the constants doesn't overflow.  */
      if (code == MULT_EXPR)
	return fold_build2 (tcode, ctype,
			    fold_build2 (code, ctype,
					 fold_convert (ctype, op0),
					 fold_convert (ctype, c)),
			    op1);

      break;

    case MULT_EXPR:
      /* We have a special case here if we are doing something like
	 (C * 8) % 4 since we know that's zero.  */
      if ((code == TRUNC_MOD_EXPR || code == CEIL_MOD_EXPR
	   || code == FLOOR_MOD_EXPR || code == ROUND_MOD_EXPR)
	  && TREE_CODE (TREE_OPERAND (t, 1)) == INTEGER_CST
	  && integer_zerop (const_binop (TRUNC_MOD_EXPR, op1, c, 0)))
	return omit_one_operand (type, integer_zero_node, op0);

      /* ... fall through ...  */

    case TRUNC_DIV_EXPR:  case CEIL_DIV_EXPR:  case FLOOR_DIV_EXPR:
    case ROUND_DIV_EXPR:  case EXACT_DIV_EXPR:
      /* If we can extract our operation from the LHS, do so and return a
	 new operation.  Likewise for the RHS from a MULT_EXPR.  Otherwise,
	 do something only if the second operand is a constant.  */
      if (same_p
	  && (t1 = extract_muldiv (op0, c, code, wide_type,
				   strict_overflow_p)) != 0)
	return fold_build2 (tcode, ctype, fold_convert (ctype, t1),
			    fold_convert (ctype, op1));
      else if (tcode == MULT_EXPR && code == MULT_EXPR
	       && (t1 = extract_muldiv (op1, c, code, wide_type,
					strict_overflow_p)) != 0)
	return fold_build2 (tcode, ctype, fold_convert (ctype, op0),
			    fold_convert (ctype, t1));
      else if (TREE_CODE (op1) != INTEGER_CST)
	return 0;

      /* If these are the same operation types, we can associate them
	 assuming no overflow.  */
      if (tcode == code
	  && 0 != (t1 = const_binop (MULT_EXPR, fold_convert (ctype, op1),
				     fold_convert (ctype, c), 0))
	  && ! TREE_OVERFLOW (t1))
	return fold_build2 (tcode, ctype, fold_convert (ctype, op0), t1);

      /* If these operations "cancel" each other, we have the main
	 optimizations of this pass, which occur when either constant is a
	 multiple of the other, in which case we replace this with either an
	 operation or CODE or TCODE.

	 If we have an unsigned type that is not a sizetype, we cannot do
	 this since it will change the result if the original computation
	 overflowed.  */
      if ((TYPE_OVERFLOW_UNDEFINED (ctype)
	   || (TREE_CODE (ctype) == INTEGER_TYPE && TYPE_IS_SIZETYPE (ctype)))
	  && ((code == MULT_EXPR && tcode == EXACT_DIV_EXPR)
	      || (tcode == MULT_EXPR
		  && code != TRUNC_MOD_EXPR && code != CEIL_MOD_EXPR
		  && code != FLOOR_MOD_EXPR && code != ROUND_MOD_EXPR)))
	{
	  if (integer_zerop (const_binop (TRUNC_MOD_EXPR, op1, c, 0)))
	    {
	      if (TYPE_OVERFLOW_UNDEFINED (ctype))
		*strict_overflow_p = true;
	      return fold_build2 (tcode, ctype, fold_convert (ctype, op0),
				  fold_convert (ctype,
						const_binop (TRUNC_DIV_EXPR,
							     op1, c, 0)));
	    }
	  else if (integer_zerop (const_binop (TRUNC_MOD_EXPR, c, op1, 0)))
	    {
	      if (TYPE_OVERFLOW_UNDEFINED (ctype))
		*strict_overflow_p = true;
	      return fold_build2 (code, ctype, fold_convert (ctype, op0),
				  fold_convert (ctype,
						const_binop (TRUNC_DIV_EXPR,
							     c, op1, 0)));
	    }
	}
      break;

    default:
      break;
    }

  return 0;
}