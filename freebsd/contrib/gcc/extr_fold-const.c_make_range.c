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
struct TYPE_3__ {scalar_t__ (* type_for_mode ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_4__ {TYPE_1__ types; } ;

/* Variables and functions */
#define  BIT_NOT_EXPR 141 
#define  CONVERT_EXPR 140 
#define  EQ_EXPR 139 
#define  GE_EXPR 138 
#define  GT_EXPR 137 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (scalar_t__) ; 
 scalar_t__ IS_EXPR_CODE_CLASS (scalar_t__) ; 
#define  LE_EXPR 136 
#define  LT_EXPR 135 
#define  MINUS_EXPR 134 
#define  NEGATE_EXPR 133 
#define  NE_EXPR 132 
#define  NON_LVALUE_EXPR 131 
#define  NOP_EXPR 130 
 scalar_t__ NULL_TREE ; 
#define  PLUS_EXPR 129 
 int /*<<< orphan*/  RSHIFT_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CODE_CLASS (int) ; 
 int TREE_CODE_LENGTH (int) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_OVERFLOW (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TRUTH_NOT_EXPR 128 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_OVERFLOW_UNDEFINED (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_PRECISION (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ build2 (int,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_int_cst (scalar_t__,int) ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  int_fits_type_p (scalar_t__,scalar_t__) ; 
 scalar_t__ integer_one_node ; 
 scalar_t__ integer_onep (scalar_t__) ; 
 scalar_t__ integer_type_node ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 TYPE_2__ lang_hooks ; 
 int /*<<< orphan*/  merge_ranges (int*,scalar_t__*,scalar_t__*,int,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  negate_expr (scalar_t__) ; 
 scalar_t__ range_binop (int const,scalar_t__,scalar_t__,int,scalar_t__,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ tcc_binary ; 
 scalar_t__ tcc_comparison ; 
 scalar_t__ tcc_expression ; 
 scalar_t__ tcc_unary ; 
 int /*<<< orphan*/  tree_int_cst_equal (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tree_int_cst_lt (scalar_t__,scalar_t__) ; 

__attribute__((used)) static tree
make_range (tree exp, int *pin_p, tree *plow, tree *phigh,
	    bool *strict_overflow_p)
{
  enum tree_code code;
  tree arg0 = NULL_TREE, arg1 = NULL_TREE;
  tree exp_type = NULL_TREE, arg0_type = NULL_TREE;
  int in_p, n_in_p;
  tree low, high, n_low, n_high;

  /* Start with simply saying "EXP != 0" and then look at the code of EXP
     and see if we can refine the range.  Some of the cases below may not
     happen, but it doesn't seem worth worrying about this.  We "continue"
     the outer loop when we've changed something; otherwise we "break"
     the switch, which will "break" the while.  */

  in_p = 0;
  low = high = build_int_cst (TREE_TYPE (exp), 0);

  while (1)
    {
      code = TREE_CODE (exp);
      exp_type = TREE_TYPE (exp);

      if (IS_EXPR_CODE_CLASS (TREE_CODE_CLASS (code)))
	{
	  if (TREE_CODE_LENGTH (code) > 0)
	    arg0 = TREE_OPERAND (exp, 0);
	  if (TREE_CODE_CLASS (code) == tcc_comparison
	      || TREE_CODE_CLASS (code) == tcc_unary
	      || TREE_CODE_CLASS (code) == tcc_binary)
	    arg0_type = TREE_TYPE (arg0);
	  if (TREE_CODE_CLASS (code) == tcc_binary
	      || TREE_CODE_CLASS (code) == tcc_comparison
	      || (TREE_CODE_CLASS (code) == tcc_expression
		  && TREE_CODE_LENGTH (code) > 1))
	    arg1 = TREE_OPERAND (exp, 1);
	}

      switch (code)
	{
	case TRUTH_NOT_EXPR:
	  in_p = ! in_p, exp = arg0;
	  continue;

	case EQ_EXPR: case NE_EXPR:
	case LT_EXPR: case LE_EXPR: case GE_EXPR: case GT_EXPR:
	  /* We can only do something if the range is testing for zero
	     and if the second operand is an integer constant.  Note that
	     saying something is "in" the range we make is done by
	     complementing IN_P since it will set in the initial case of
	     being not equal to zero; "out" is leaving it alone.  */
	  if (low == 0 || high == 0
	      || ! integer_zerop (low) || ! integer_zerop (high)
	      || TREE_CODE (arg1) != INTEGER_CST)
	    break;

	  switch (code)
	    {
	    case NE_EXPR:  /* - [c, c]  */
	      low = high = arg1;
	      break;
	    case EQ_EXPR:  /* + [c, c]  */
	      in_p = ! in_p, low = high = arg1;
	      break;
	    case GT_EXPR:  /* - [-, c] */
	      low = 0, high = arg1;
	      break;
	    case GE_EXPR:  /* + [c, -] */
	      in_p = ! in_p, low = arg1, high = 0;
	      break;
	    case LT_EXPR:  /* - [c, -] */
	      low = arg1, high = 0;
	      break;
	    case LE_EXPR:  /* + [-, c] */
	      in_p = ! in_p, low = 0, high = arg1;
	      break;
	    default:
	      gcc_unreachable ();
	    }

	  /* If this is an unsigned comparison, we also know that EXP is
	     greater than or equal to zero.  We base the range tests we make
	     on that fact, so we record it here so we can parse existing
	     range tests.  We test arg0_type since often the return type
	     of, e.g. EQ_EXPR, is boolean.  */
	  if (TYPE_UNSIGNED (arg0_type) && (low == 0 || high == 0))
	    {
	      if (! merge_ranges (&n_in_p, &n_low, &n_high,
				  in_p, low, high, 1,
				  build_int_cst (arg0_type, 0),
				  NULL_TREE))
		break;

	      in_p = n_in_p, low = n_low, high = n_high;

	      /* If the high bound is missing, but we have a nonzero low
		 bound, reverse the range so it goes from zero to the low bound
		 minus 1.  */
	      if (high == 0 && low && ! integer_zerop (low))
		{
		  in_p = ! in_p;
		  high = range_binop (MINUS_EXPR, NULL_TREE, low, 0,
				      integer_one_node, 0);
		  low = build_int_cst (arg0_type, 0);
		}
	    }

	  exp = arg0;
	  continue;

	case NEGATE_EXPR:
	  /* (-x) IN [a,b] -> x in [-b, -a]  */
	  n_low = range_binop (MINUS_EXPR, exp_type,
			       build_int_cst (exp_type, 0),
			       0, high, 1);
	  n_high = range_binop (MINUS_EXPR, exp_type,
				build_int_cst (exp_type, 0),
				0, low, 0);
	  low = n_low, high = n_high;
	  exp = arg0;
	  continue;

	case BIT_NOT_EXPR:
	  /* ~ X -> -X - 1  */
	  exp = build2 (MINUS_EXPR, exp_type, negate_expr (arg0),
			build_int_cst (exp_type, 1));
	  continue;

	case PLUS_EXPR:  case MINUS_EXPR:
	  if (TREE_CODE (arg1) != INTEGER_CST)
	    break;

	  /* If flag_wrapv and ARG0_TYPE is signed, then we cannot
	     move a constant to the other side.  */
	  if (!TYPE_UNSIGNED (arg0_type)
	      && !TYPE_OVERFLOW_UNDEFINED (arg0_type))
	    break;

	  /* If EXP is signed, any overflow in the computation is undefined,
	     so we don't worry about it so long as our computations on
	     the bounds don't overflow.  For unsigned, overflow is defined
	     and this is exactly the right thing.  */
	  n_low = range_binop (code == MINUS_EXPR ? PLUS_EXPR : MINUS_EXPR,
			       arg0_type, low, 0, arg1, 0);
	  n_high = range_binop (code == MINUS_EXPR ? PLUS_EXPR : MINUS_EXPR,
				arg0_type, high, 1, arg1, 0);
	  if ((n_low != 0 && TREE_OVERFLOW (n_low))
	      || (n_high != 0 && TREE_OVERFLOW (n_high)))
	    break;

	  if (TYPE_OVERFLOW_UNDEFINED (arg0_type))
	    *strict_overflow_p = true;

	  /* Check for an unsigned range which has wrapped around the maximum
	     value thus making n_high < n_low, and normalize it.  */
	  if (n_low && n_high && tree_int_cst_lt (n_high, n_low))
	    {
	      low = range_binop (PLUS_EXPR, arg0_type, n_high, 0,
				 integer_one_node, 0);
	      high = range_binop (MINUS_EXPR, arg0_type, n_low, 0,
				  integer_one_node, 0);

	      /* If the range is of the form +/- [ x+1, x ], we won't
		 be able to normalize it.  But then, it represents the
		 whole range or the empty set, so make it
		 +/- [ -, - ].  */
	      if (tree_int_cst_equal (n_low, low)
		  && tree_int_cst_equal (n_high, high))
		low = high = 0;
	      else
		in_p = ! in_p;
	    }
	  else
	    low = n_low, high = n_high;

	  exp = arg0;
	  continue;

	case NOP_EXPR:  case NON_LVALUE_EXPR:  case CONVERT_EXPR:
	  if (TYPE_PRECISION (arg0_type) > TYPE_PRECISION (exp_type))
	    break;

	  if (! INTEGRAL_TYPE_P (arg0_type)
	      || (low != 0 && ! int_fits_type_p (low, arg0_type))
	      || (high != 0 && ! int_fits_type_p (high, arg0_type)))
	    break;

	  n_low = low, n_high = high;

	  if (n_low != 0)
	    n_low = fold_convert (arg0_type, n_low);

	  if (n_high != 0)
	    n_high = fold_convert (arg0_type, n_high);


	  /* If we're converting arg0 from an unsigned type, to exp,
	     a signed type,  we will be doing the comparison as unsigned.
	     The tests above have already verified that LOW and HIGH
	     are both positive.

	     So we have to ensure that we will handle large unsigned
	     values the same way that the current signed bounds treat
	     negative values.  */

	  if (!TYPE_UNSIGNED (exp_type) && TYPE_UNSIGNED (arg0_type))
	    {
	      tree high_positive;
	      tree equiv_type = lang_hooks.types.type_for_mode
		(TYPE_MODE (arg0_type), 1);

	      /* A range without an upper bound is, naturally, unbounded.
		 Since convert would have cropped a very large value, use
		 the max value for the destination type.  */
	      high_positive
		= TYPE_MAX_VALUE (equiv_type) ? TYPE_MAX_VALUE (equiv_type)
		: TYPE_MAX_VALUE (arg0_type);

	      if (TYPE_PRECISION (exp_type) == TYPE_PRECISION (arg0_type))
		high_positive = fold_build2 (RSHIFT_EXPR, arg0_type,
					     fold_convert (arg0_type,
							   high_positive),
					     fold_convert (arg0_type,
							   integer_one_node));

	      /* If the low bound is specified, "and" the range with the
		 range for which the original unsigned value will be
		 positive.  */
	      if (low != 0)
		{
		  if (! merge_ranges (&n_in_p, &n_low, &n_high,
				      1, n_low, n_high, 1,
				      fold_convert (arg0_type,
						    integer_zero_node),
				      high_positive))
		    break;

		  in_p = (n_in_p == in_p);
		}
	      else
		{
		  /* Otherwise, "or" the range with the range of the input
		     that will be interpreted as negative.  */
		  if (! merge_ranges (&n_in_p, &n_low, &n_high,
				      0, n_low, n_high, 1,
				      fold_convert (arg0_type,
						    integer_zero_node),
				      high_positive))
		    break;

		  in_p = (in_p != n_in_p);
		}
	    }

	  exp = arg0;
	  low = n_low, high = n_high;
	  continue;

	default:
	  break;
	}

      break;
    }

  /* If EXP is a constant, we can evaluate whether this is true or false.  */
  if (TREE_CODE (exp) == INTEGER_CST)
    {
      in_p = in_p == (integer_onep (range_binop (GE_EXPR, integer_type_node,
						 exp, 0, low, 0))
		      && integer_onep (range_binop (LE_EXPR, integer_type_node,
						    exp, 1, high, 1)));
      low = high = 0;
      exp = 0;
    }

  *pin_p = in_p, *plow = low, *phigh = high;
  return exp;
}