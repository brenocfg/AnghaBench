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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
#define  FIX_CEIL_EXPR 131 
#define  FIX_FLOOR_EXPR 130 
#define  FIX_ROUND_EXPR 129 
#define  FIX_TRUNC_EXPR 128 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ REAL_VALUES_LESS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ REAL_VALUE_ISNAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_TO_INT (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (scalar_t__) ; 
 scalar_t__ TREE_INT_CST_HIGH (scalar_t__) ; 
 scalar_t__ TREE_INT_CST_LOW (scalar_t__) ; 
 int TREE_OVERFLOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_REAL_CST (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ build_int_cst_wide (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ force_fit_type (scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  real_ceil (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_floor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_round (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_trunc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  real_value_from_int_cst (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static tree
fold_convert_const_int_from_real (enum tree_code code, tree type, tree arg1)
{
  int overflow = 0;
  tree t;

  /* The following code implements the floating point to integer
     conversion rules required by the Java Language Specification,
     that IEEE NaNs are mapped to zero and values that overflow
     the target precision saturate, i.e. values greater than
     INT_MAX are mapped to INT_MAX, and values less than INT_MIN
     are mapped to INT_MIN.  These semantics are allowed by the
     C and C++ standards that simply state that the behavior of
     FP-to-integer conversion is unspecified upon overflow.  */

  HOST_WIDE_INT high, low;
  REAL_VALUE_TYPE r;
  REAL_VALUE_TYPE x = TREE_REAL_CST (arg1);

  switch (code)
    {
    case FIX_TRUNC_EXPR:
      real_trunc (&r, VOIDmode, &x);
      break;

    case FIX_CEIL_EXPR:
      real_ceil (&r, VOIDmode, &x);
      break;

    case FIX_FLOOR_EXPR:
      real_floor (&r, VOIDmode, &x);
      break;

    case FIX_ROUND_EXPR:
      real_round (&r, VOIDmode, &x);
      break;

    default:
      gcc_unreachable ();
    }

  /* If R is NaN, return zero and show we have an overflow.  */
  if (REAL_VALUE_ISNAN (r))
    {
      overflow = 1;
      high = 0;
      low = 0;
    }

  /* See if R is less than the lower bound or greater than the
     upper bound.  */

  if (! overflow)
    {
      tree lt = TYPE_MIN_VALUE (type);
      REAL_VALUE_TYPE l = real_value_from_int_cst (NULL_TREE, lt);
      if (REAL_VALUES_LESS (r, l))
	{
	  overflow = 1;
	  high = TREE_INT_CST_HIGH (lt);
	  low = TREE_INT_CST_LOW (lt);
	}
    }

  if (! overflow)
    {
      tree ut = TYPE_MAX_VALUE (type);
      if (ut)
	{
	  REAL_VALUE_TYPE u = real_value_from_int_cst (NULL_TREE, ut);
	  if (REAL_VALUES_LESS (u, r))
	    {
	      overflow = 1;
	      high = TREE_INT_CST_HIGH (ut);
	      low = TREE_INT_CST_LOW (ut);
	    }
	}
    }

  if (! overflow)
    REAL_VALUE_TO_INT (&low, &high, r);

  t = build_int_cst_wide (type, low, high);

  t = force_fit_type (t, -1, overflow | TREE_OVERFLOW (arg1),
		      TREE_CONSTANT_OVERFLOW (arg1));
  return t;
}