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
typedef  enum built_in_function { ____Placeholder_built_in_function } built_in_function ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ ADDR_EXPR ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ CONVERT_EXPR ; 
 scalar_t__ DECL_BIT_FIELD (scalar_t__) ; 
 int /*<<< orphan*/  DECL_SIZE (scalar_t__) ; 
 int END_BUILTINS ; 
#define  EQ_EXPR 133 
 scalar_t__ EXACT_DIV_EXPR ; 
 scalar_t__ FLOAT_TYPE_P (scalar_t__) ; 
#define  GE_EXPR 132 
#define  GT_EXPR 131 
 int /*<<< orphan*/  HONOR_NANS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HONOR_SNANS (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INTEGER_TYPE ; 
 scalar_t__ INTEGRAL_TYPE_P (scalar_t__) ; 
#define  LE_EXPR 130 
 int LSHIFT_EXPR ; 
#define  LT_EXPR 129 
 scalar_t__ MAX_EXPR ; 
 scalar_t__ MINUS_EXPR ; 
 scalar_t__ MIN_EXPR ; 
 scalar_t__ NEGATE_EXPR ; 
#define  NE_EXPR 128 
 scalar_t__ NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ PLUS_EXPR ; 
 scalar_t__ POINTER_TYPE_P (scalar_t__) ; 
 scalar_t__ POSTDECREMENT_EXPR ; 
 scalar_t__ POSTINCREMENT_EXPR ; 
 int PREDECREMENT_EXPR ; 
 int PREINCREMENT_EXPR ; 
 scalar_t__ REAL_CST ; 
 scalar_t__ REAL_VALUE_ISINF (int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_VALUE_ISNAN (int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_VALUE_MINUS_ZERO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_NEGATE (int /*<<< orphan*/ ) ; 
 int RSHIFT_EXPR ; 
 int /*<<< orphan*/  STRIP_SIGN_NOPS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_OVERFLOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_REAL_CST (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TRUNC_DIV_EXPR ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_TRAPS (scalar_t__) ; 
 scalar_t__ TYPE_OVERFLOW_UNDEFINED (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 int /*<<< orphan*/  WARN_STRICT_OVERFLOW_COMPARISON ; 
 scalar_t__ build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_fold_addr_expr (scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,scalar_t__) ; 
 scalar_t__ build_real (scalar_t__,int /*<<< orphan*/ ) ; 
 int builtin_mathfn_code (scalar_t__) ; 
 scalar_t__ const_binop (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ constant_boolean_node (int,scalar_t__) ; 
 int /*<<< orphan*/  dconst0 ; 
 scalar_t__ eval_subst (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ extract_array_ref (scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  flag_errno_math ; 
 scalar_t__ flag_unsafe_math_optimizations ; 
 int /*<<< orphan*/  flag_wrapv ; 
 scalar_t__ fold_build2 (int const,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 scalar_t__ fold_div_compare (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_inf_compare (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_mathfn_compare (int,int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fold_overflow_warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ fold_relational_const (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_sign_changed_comparison (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_widened_comparison (int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ host_integerp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ integer_one_node ; 
 int integer_onep (scalar_t__) ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 scalar_t__ omit_one_operand (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ operand_equal_p (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ optimize_minmax_comparison (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ save_expr (scalar_t__) ; 
 scalar_t__ signed_type_for (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_type_node ; 
 scalar_t__ strip_float_extensions (scalar_t__) ; 
 int swap_tree_comparison (int) ; 
 scalar_t__ tree_low_cst (int /*<<< orphan*/ ,int) ; 
 scalar_t__ tree_swap_operands_p (scalar_t__,scalar_t__,int) ; 
 scalar_t__ twoval_comparison_p (scalar_t__,scalar_t__*,scalar_t__*,int*) ; 

__attribute__((used)) static tree
fold_comparison (enum tree_code code, tree type, tree op0, tree op1)
{
  tree arg0, arg1, tem;

  arg0 = op0;
  arg1 = op1;

  STRIP_SIGN_NOPS (arg0);
  STRIP_SIGN_NOPS (arg1);

  tem = fold_relational_const (code, type, arg0, arg1);
  if (tem != NULL_TREE)
    return tem;

  /* If one arg is a real or integer constant, put it last.  */
  if (tree_swap_operands_p (arg0, arg1, true))
    return fold_build2 (swap_tree_comparison (code), type, op1, op0);

  /* Transform comparisons of the form X +- C1 CMP C2 to X CMP C2 +- C1.  */
  if ((TREE_CODE (arg0) == PLUS_EXPR || TREE_CODE (arg0) == MINUS_EXPR)
      && (TREE_CODE (TREE_OPERAND (arg0, 1)) == INTEGER_CST
	  && !TREE_OVERFLOW (TREE_OPERAND (arg0, 1))
	  && TYPE_OVERFLOW_UNDEFINED (TREE_TYPE (arg1)))
      && (TREE_CODE (arg1) == INTEGER_CST
	  && !TREE_OVERFLOW (arg1)))
    {
      tree const1 = TREE_OPERAND (arg0, 1);
      tree const2 = arg1;
      tree variable = TREE_OPERAND (arg0, 0);
      tree lhs;
      int lhs_add;
      lhs_add = TREE_CODE (arg0) != PLUS_EXPR;

      lhs = fold_build2 (lhs_add ? PLUS_EXPR : MINUS_EXPR,
			 TREE_TYPE (arg1), const2, const1);
      if (TREE_CODE (lhs) == TREE_CODE (arg1)
	  && (TREE_CODE (lhs) != INTEGER_CST
	      || !TREE_OVERFLOW (lhs)))
	{
	  fold_overflow_warning (("assuming signed overflow does not occur "
				  "when changing X +- C1 cmp C2 to "
				  "X cmp C1 +- C2"),
				 WARN_STRICT_OVERFLOW_COMPARISON);
	  return fold_build2 (code, type, variable, lhs);
	}
    }

  /* If this is a comparison of two exprs that look like an ARRAY_REF of the
     same object, then we can fold this to a comparison of the two offsets in
     signed size type.  This is possible because pointer arithmetic is
     restricted to retain within an object and overflow on pointer differences
     is undefined as of 6.5.6/8 and /9 with respect to the signed ptrdiff_t.

     We check flag_wrapv directly because pointers types are unsigned,
     and therefore TYPE_OVERFLOW_WRAPS returns true for them.  That is
     normally what we want to avoid certain odd overflow cases, but
     not here.  */
  if (POINTER_TYPE_P (TREE_TYPE (arg0))
      && !flag_wrapv
      && !TYPE_OVERFLOW_TRAPS (TREE_TYPE (arg0)))
    {
      tree base0, offset0, base1, offset1;

      if (extract_array_ref (arg0, &base0, &offset0)
	  && extract_array_ref (arg1, &base1, &offset1)
	  && operand_equal_p (base0, base1, 0))
        {
	  tree signed_size_type_node;
	  signed_size_type_node = signed_type_for (size_type_node);

	  /* By converting to signed size type we cover middle-end pointer
	     arithmetic which operates on unsigned pointer types of size
	     type size and ARRAY_REF offsets which are properly sign or
	     zero extended from their type in case it is narrower than
	     size type.  */
	  if (offset0 == NULL_TREE)
	    offset0 = build_int_cst (signed_size_type_node, 0);
	  else
	    offset0 = fold_convert (signed_size_type_node, offset0);
	  if (offset1 == NULL_TREE)
	    offset1 = build_int_cst (signed_size_type_node, 0);
	  else
	    offset1 = fold_convert (signed_size_type_node, offset1);

	  return fold_build2 (code, type, offset0, offset1);
	}
    }

  if (FLOAT_TYPE_P (TREE_TYPE (arg0)))
    {
      tree targ0 = strip_float_extensions (arg0);
      tree targ1 = strip_float_extensions (arg1);
      tree newtype = TREE_TYPE (targ0);

      if (TYPE_PRECISION (TREE_TYPE (targ1)) > TYPE_PRECISION (newtype))
	newtype = TREE_TYPE (targ1);

      /* Fold (double)float1 CMP (double)float2 into float1 CMP float2.  */
      if (TYPE_PRECISION (newtype) < TYPE_PRECISION (TREE_TYPE (arg0)))
	return fold_build2 (code, type, fold_convert (newtype, targ0),
			    fold_convert (newtype, targ1));

      /* (-a) CMP (-b) -> b CMP a  */
      if (TREE_CODE (arg0) == NEGATE_EXPR
	  && TREE_CODE (arg1) == NEGATE_EXPR)
	return fold_build2 (code, type, TREE_OPERAND (arg1, 0),
			    TREE_OPERAND (arg0, 0));

      if (TREE_CODE (arg1) == REAL_CST)
	{
	  REAL_VALUE_TYPE cst;
	  cst = TREE_REAL_CST (arg1);

	  /* (-a) CMP CST -> a swap(CMP) (-CST)  */
	  if (TREE_CODE (arg0) == NEGATE_EXPR)
	    return fold_build2 (swap_tree_comparison (code), type,
				TREE_OPERAND (arg0, 0),
				build_real (TREE_TYPE (arg1),
					    REAL_VALUE_NEGATE (cst)));

	  /* IEEE doesn't distinguish +0 and -0 in comparisons.  */
	  /* a CMP (-0) -> a CMP 0  */
	  if (REAL_VALUE_MINUS_ZERO (cst))
	    return fold_build2 (code, type, arg0,
				build_real (TREE_TYPE (arg1), dconst0));

	  /* x != NaN is always true, other ops are always false.  */
	  if (REAL_VALUE_ISNAN (cst)
	      && ! HONOR_SNANS (TYPE_MODE (TREE_TYPE (arg1))))
	    {
	      tem = (code == NE_EXPR) ? integer_one_node : integer_zero_node;
	      return omit_one_operand (type, tem, arg0);
	    }

	  /* Fold comparisons against infinity.  */
	  if (REAL_VALUE_ISINF (cst))
	    {
	      tem = fold_inf_compare (code, type, arg0, arg1);
	      if (tem != NULL_TREE)
		return tem;
	    }
	}

      /* If this is a comparison of a real constant with a PLUS_EXPR
	 or a MINUS_EXPR of a real constant, we can convert it into a
	 comparison with a revised real constant as long as no overflow
	 occurs when unsafe_math_optimizations are enabled.  */
      if (flag_unsafe_math_optimizations
	  && TREE_CODE (arg1) == REAL_CST
	  && (TREE_CODE (arg0) == PLUS_EXPR
	      || TREE_CODE (arg0) == MINUS_EXPR)
	  && TREE_CODE (TREE_OPERAND (arg0, 1)) == REAL_CST
	  && 0 != (tem = const_binop (TREE_CODE (arg0) == PLUS_EXPR
				      ? MINUS_EXPR : PLUS_EXPR,
				      arg1, TREE_OPERAND (arg0, 1), 0))
	  && ! TREE_CONSTANT_OVERFLOW (tem))
	return fold_build2 (code, type, TREE_OPERAND (arg0, 0), tem);

      /* Likewise, we can simplify a comparison of a real constant with
         a MINUS_EXPR whose first operand is also a real constant, i.e.
         (c1 - x) < c2 becomes x > c1-c2.  */
      if (flag_unsafe_math_optimizations
	  && TREE_CODE (arg1) == REAL_CST
	  && TREE_CODE (arg0) == MINUS_EXPR
	  && TREE_CODE (TREE_OPERAND (arg0, 0)) == REAL_CST
	  && 0 != (tem = const_binop (MINUS_EXPR, TREE_OPERAND (arg0, 0),
				      arg1, 0))
	  && ! TREE_CONSTANT_OVERFLOW (tem))
	return fold_build2 (swap_tree_comparison (code), type,
			    TREE_OPERAND (arg0, 1), tem);

      /* Fold comparisons against built-in math functions.  */
      if (TREE_CODE (arg1) == REAL_CST
	  && flag_unsafe_math_optimizations
	  && ! flag_errno_math)
	{
	  enum built_in_function fcode = builtin_mathfn_code (arg0);

	  if (fcode != END_BUILTINS)
	    {
	      tem = fold_mathfn_compare (fcode, code, type, arg0, arg1);
	      if (tem != NULL_TREE)
		return tem;
	    }
	}
    }

  /* Convert foo++ == CONST into ++foo == CONST + INCR.  */
  if (TREE_CONSTANT (arg1)
      && (TREE_CODE (arg0) == POSTINCREMENT_EXPR
	  || TREE_CODE (arg0) == POSTDECREMENT_EXPR)
      /* This optimization is invalid for ordered comparisons
         if CONST+INCR overflows or if foo+incr might overflow.
	 This optimization is invalid for floating point due to rounding.
	 For pointer types we assume overflow doesn't happen.  */
      && (POINTER_TYPE_P (TREE_TYPE (arg0))
	  || (INTEGRAL_TYPE_P (TREE_TYPE (arg0))
	      && (code == EQ_EXPR || code == NE_EXPR))))
    {
      tree varop, newconst;

      if (TREE_CODE (arg0) == POSTINCREMENT_EXPR)
	{
	  newconst = fold_build2 (PLUS_EXPR, TREE_TYPE (arg0),
				  arg1, TREE_OPERAND (arg0, 1));
	  varop = build2 (PREINCREMENT_EXPR, TREE_TYPE (arg0),
			  TREE_OPERAND (arg0, 0),
			  TREE_OPERAND (arg0, 1));
	}
      else
	{
	  newconst = fold_build2 (MINUS_EXPR, TREE_TYPE (arg0),
				  arg1, TREE_OPERAND (arg0, 1));
	  varop = build2 (PREDECREMENT_EXPR, TREE_TYPE (arg0),
			  TREE_OPERAND (arg0, 0),
			  TREE_OPERAND (arg0, 1));
	}


      /* If VAROP is a reference to a bitfield, we must mask
	 the constant by the width of the field.  */
      if (TREE_CODE (TREE_OPERAND (varop, 0)) == COMPONENT_REF
	  && DECL_BIT_FIELD (TREE_OPERAND (TREE_OPERAND (varop, 0), 1))
	  && host_integerp (DECL_SIZE (TREE_OPERAND
					 (TREE_OPERAND (varop, 0), 1)), 1))
	{
	  tree fielddecl = TREE_OPERAND (TREE_OPERAND (varop, 0), 1);
	  HOST_WIDE_INT size = tree_low_cst (DECL_SIZE (fielddecl), 1);
	  tree folded_compare, shift;

	  /* First check whether the comparison would come out
	     always the same.  If we don't do that we would
	     change the meaning with the masking.  */
	  folded_compare = fold_build2 (code, type,
					TREE_OPERAND (varop, 0), arg1);
	  if (TREE_CODE (folded_compare) == INTEGER_CST)
	    return omit_one_operand (type, folded_compare, varop);

	  shift = build_int_cst (NULL_TREE,
				 TYPE_PRECISION (TREE_TYPE (varop)) - size);
	  shift = fold_convert (TREE_TYPE (varop), shift);
	  newconst = fold_build2 (LSHIFT_EXPR, TREE_TYPE (varop),
				  newconst, shift);
	  newconst = fold_build2 (RSHIFT_EXPR, TREE_TYPE (varop),
				  newconst, shift);
	}

      return fold_build2 (code, type, varop, newconst);
    }

  if (TREE_CODE (TREE_TYPE (arg0)) == INTEGER_TYPE
      && (TREE_CODE (arg0) == NOP_EXPR
	  || TREE_CODE (arg0) == CONVERT_EXPR))
    {
      /* If we are widening one operand of an integer comparison,
	 see if the other operand is similarly being widened.  Perhaps we
	 can do the comparison in the narrower type.  */
      tem = fold_widened_comparison (code, type, arg0, arg1);
      if (tem)
	return tem;

      /* Or if we are changing signedness.  */
      tem = fold_sign_changed_comparison (code, type, arg0, arg1);
      if (tem)
	return tem;
    }

  /* If this is comparing a constant with a MIN_EXPR or a MAX_EXPR of a
     constant, we can simplify it.  */
  if (TREE_CODE (arg1) == INTEGER_CST
      && (TREE_CODE (arg0) == MIN_EXPR
	  || TREE_CODE (arg0) == MAX_EXPR)
      && TREE_CODE (TREE_OPERAND (arg0, 1)) == INTEGER_CST)
    {
      tem = optimize_minmax_comparison (code, type, op0, op1);
      if (tem)
	return tem;
    }

  /* Simplify comparison of something with itself.  (For IEEE
     floating-point, we can only do some of these simplifications.)  */
  if (operand_equal_p (arg0, arg1, 0))
    {
      switch (code)
	{
	case EQ_EXPR:
	  if (! FLOAT_TYPE_P (TREE_TYPE (arg0))
	      || ! HONOR_NANS (TYPE_MODE (TREE_TYPE (arg0))))
	    return constant_boolean_node (1, type);
	  break;

	case GE_EXPR:
	case LE_EXPR:
	  if (! FLOAT_TYPE_P (TREE_TYPE (arg0))
	      || ! HONOR_NANS (TYPE_MODE (TREE_TYPE (arg0))))
	    return constant_boolean_node (1, type);
	  return fold_build2 (EQ_EXPR, type, arg0, arg1);

	case NE_EXPR:
	  /* For NE, we can only do this simplification if integer
	     or we don't honor IEEE floating point NaNs.  */
	  if (FLOAT_TYPE_P (TREE_TYPE (arg0))
	      && HONOR_NANS (TYPE_MODE (TREE_TYPE (arg0))))
	    break;
	  /* ... fall through ...  */
	case GT_EXPR:
	case LT_EXPR:
	  return constant_boolean_node (0, type);
	default:
	  gcc_unreachable ();
	}
    }

  /* If we are comparing an expression that just has comparisons
     of two integer values, arithmetic expressions of those comparisons,
     and constants, we can simplify it.  There are only three cases
     to check: the two values can either be equal, the first can be
     greater, or the second can be greater.  Fold the expression for
     those three values.  Since each value must be 0 or 1, we have
     eight possibilities, each of which corresponds to the constant 0
     or 1 or one of the six possible comparisons.

     This handles common cases like (a > b) == 0 but also handles
     expressions like  ((x > y) - (y > x)) > 0, which supposedly
     occur in macroized code.  */

  if (TREE_CODE (arg1) == INTEGER_CST && TREE_CODE (arg0) != INTEGER_CST)
    {
      tree cval1 = 0, cval2 = 0;
      int save_p = 0;

      if (twoval_comparison_p (arg0, &cval1, &cval2, &save_p)
	  /* Don't handle degenerate cases here; they should already
	     have been handled anyway.  */
	  && cval1 != 0 && cval2 != 0
	  && ! (TREE_CONSTANT (cval1) && TREE_CONSTANT (cval2))
	  && TREE_TYPE (cval1) == TREE_TYPE (cval2)
	  && INTEGRAL_TYPE_P (TREE_TYPE (cval1))
	  && TYPE_MAX_VALUE (TREE_TYPE (cval1))
	  && TYPE_MAX_VALUE (TREE_TYPE (cval2))
	  && ! operand_equal_p (TYPE_MIN_VALUE (TREE_TYPE (cval1)),
				TYPE_MAX_VALUE (TREE_TYPE (cval2)), 0))
	{
	  tree maxval = TYPE_MAX_VALUE (TREE_TYPE (cval1));
	  tree minval = TYPE_MIN_VALUE (TREE_TYPE (cval1));

	  /* We can't just pass T to eval_subst in case cval1 or cval2
	     was the same as ARG1.  */

	  tree high_result
		= fold_build2 (code, type,
			       eval_subst (arg0, cval1, maxval,
					   cval2, minval),
			       arg1);
	  tree equal_result
		= fold_build2 (code, type,
			       eval_subst (arg0, cval1, maxval,
					   cval2, maxval),
			       arg1);
	  tree low_result
		= fold_build2 (code, type,
			       eval_subst (arg0, cval1, minval,
					   cval2, maxval),
			       arg1);

	  /* All three of these results should be 0 or 1.  Confirm they are.
	     Then use those values to select the proper code to use.  */

	  if (TREE_CODE (high_result) == INTEGER_CST
	      && TREE_CODE (equal_result) == INTEGER_CST
	      && TREE_CODE (low_result) == INTEGER_CST)
	    {
	      /* Make a 3-bit mask with the high-order bit being the
		 value for `>', the next for '=', and the low for '<'.  */
	      switch ((integer_onep (high_result) * 4)
		      + (integer_onep (equal_result) * 2)
		      + integer_onep (low_result))
		{
		case 0:
		  /* Always false.  */
		  return omit_one_operand (type, integer_zero_node, arg0);
		case 1:
		  code = LT_EXPR;
		  break;
		case 2:
		  code = EQ_EXPR;
		  break;
		case 3:
		  code = LE_EXPR;
		  break;
		case 4:
		  code = GT_EXPR;
		  break;
		case 5:
		  code = NE_EXPR;
		  break;
		case 6:
		  code = GE_EXPR;
		  break;
		case 7:
		  /* Always true.  */
		  return omit_one_operand (type, integer_one_node, arg0);
		}

	      if (save_p)
		return save_expr (build2 (code, type, cval1, cval2));
	      return fold_build2 (code, type, cval1, cval2);
	    }
	}
    }

  /* Fold a comparison of the address of COMPONENT_REFs with the same
     type and component to a comparison of the address of the base
     object.  In short, &x->a OP &y->a to x OP y and
     &x->a OP &y.a to x OP &y  */
  if (TREE_CODE (arg0) == ADDR_EXPR
      && TREE_CODE (TREE_OPERAND (arg0, 0)) == COMPONENT_REF
      && TREE_CODE (arg1) == ADDR_EXPR
      && TREE_CODE (TREE_OPERAND (arg1, 0)) == COMPONENT_REF)
    {
      tree cref0 = TREE_OPERAND (arg0, 0);
      tree cref1 = TREE_OPERAND (arg1, 0);
      if (TREE_OPERAND (cref0, 1) == TREE_OPERAND (cref1, 1))
	{
	  tree op0 = TREE_OPERAND (cref0, 0);
	  tree op1 = TREE_OPERAND (cref1, 0);
	  return fold_build2 (code, type,
			      build_fold_addr_expr (op0),
			      build_fold_addr_expr (op1));
	}
    }

  /* We can fold X/C1 op C2 where C1 and C2 are integer constants
     into a single range test.  */
  if ((TREE_CODE (arg0) == TRUNC_DIV_EXPR
       || TREE_CODE (arg0) == EXACT_DIV_EXPR)
      && TREE_CODE (arg1) == INTEGER_CST
      && TREE_CODE (TREE_OPERAND (arg0, 1)) == INTEGER_CST
      && !integer_zerop (TREE_OPERAND (arg0, 1))
      && !TREE_OVERFLOW (TREE_OPERAND (arg0, 1))
      && !TREE_OVERFLOW (arg1))
    {
      tem = fold_div_compare (code, type, arg0, arg1);
      if (tem != NULL_TREE)
	return tem;
    }

  return NULL_TREE;
}