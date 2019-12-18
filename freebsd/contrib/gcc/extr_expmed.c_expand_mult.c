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
struct algorithm {int dummy; } ;
typedef  scalar_t__ rtx ;
typedef  enum mult_variant { ____Placeholder_mult_variant } mult_variant ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_DOUBLE ; 
 scalar_t__ CONST_DOUBLE_HIGH (scalar_t__) ; 
 scalar_t__ CONST_DOUBLE_LOW (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ EXACT_POWER_OF_2_OR_ZERO_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int GET_MODE_BITSIZE (int) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int HOST_BITS_PER_WIDE_INT ; 
 scalar_t__ INTVAL (scalar_t__) ; 
 scalar_t__ LAST_VIRTUAL_REGISTER ; 
 int /*<<< orphan*/  LSHIFT_EXPR ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 scalar_t__ REAL_VALUES_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 scalar_t__ SCALAR_INT_MODE_P (int) ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  add_optab ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 scalar_t__ choose_mult_variant (int,scalar_t__,struct algorithm*,int*,int) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const1_rtx ; 
 scalar_t__ constm1_rtx ; 
 int /*<<< orphan*/  dconst2 ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_mult_const (int,scalar_t__,scalar_t__,scalar_t__,struct algorithm*,int) ; 
 scalar_t__ expand_shift (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ expand_unop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_trapv ; 
 int floor_log2 (scalar_t__) ; 
 scalar_t__ force_reg (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ gen_raw_REG (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_MULT (int,scalar_t__,scalar_t__) ; 
 int* neg_cost ; 
 int /*<<< orphan*/  neg_optab ; 
 int /*<<< orphan*/  negv_optab ; 
 int rtx_cost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smul_optab ; 
 int /*<<< orphan*/  smulv_optab ; 

rtx
expand_mult (enum machine_mode mode, rtx op0, rtx op1, rtx target,
	     int unsignedp)
{
  enum mult_variant variant;
  struct algorithm algorithm;
  int max_cost;

  /* Handling const0_rtx here allows us to use zero as a rogue value for
     coeff below.  */
  if (op1 == const0_rtx)
    return const0_rtx;
  if (op1 == const1_rtx)
    return op0;
  if (op1 == constm1_rtx)
    return expand_unop (mode,
			GET_MODE_CLASS (mode) == MODE_INT
			&& !unsignedp && flag_trapv
			? negv_optab : neg_optab,
			op0, target, 0);

  /* These are the operations that are potentially turned into a sequence
     of shifts and additions.  */
  if (SCALAR_INT_MODE_P (mode)
      && (unsignedp || !flag_trapv))
    {
      HOST_WIDE_INT coeff = 0;
      rtx fake_reg = gen_raw_REG (mode, LAST_VIRTUAL_REGISTER + 1);

      /* synth_mult does an `unsigned int' multiply.  As long as the mode is
	 less than or equal in size to `unsigned int' this doesn't matter.
	 If the mode is larger than `unsigned int', then synth_mult works
	 only if the constant value exactly fits in an `unsigned int' without
	 any truncation.  This means that multiplying by negative values does
	 not work; results are off by 2^32 on a 32 bit machine.  */

      if (GET_CODE (op1) == CONST_INT)
	{
	  /* Attempt to handle multiplication of DImode values by negative
	     coefficients, by performing the multiplication by a positive
	     multiplier and then inverting the result.  */
	  if (INTVAL (op1) < 0
	      && GET_MODE_BITSIZE (mode) > HOST_BITS_PER_WIDE_INT)
	    {
	      /* Its safe to use -INTVAL (op1) even for INT_MIN, as the
		 result is interpreted as an unsigned coefficient.
		 Exclude cost of op0 from max_cost to match the cost
		 calculation of the synth_mult.  */
	      max_cost = rtx_cost (gen_rtx_MULT (mode, fake_reg, op1), SET)
			 - neg_cost[mode];
	      if (max_cost > 0
		  && choose_mult_variant (mode, -INTVAL (op1), &algorithm,
					  &variant, max_cost))
		{
		  rtx temp = expand_mult_const (mode, op0, -INTVAL (op1),
						NULL_RTX, &algorithm,
						variant);
		  return expand_unop (mode, neg_optab, temp, target, 0);
		}
	    }
	  else coeff = INTVAL (op1);
	}
      else if (GET_CODE (op1) == CONST_DOUBLE)
	{
	  /* If we are multiplying in DImode, it may still be a win
	     to try to work with shifts and adds.  */
	  if (CONST_DOUBLE_HIGH (op1) == 0)
	    coeff = CONST_DOUBLE_LOW (op1);
	  else if (CONST_DOUBLE_LOW (op1) == 0
		   && EXACT_POWER_OF_2_OR_ZERO_P (CONST_DOUBLE_HIGH (op1)))
	    {
	      int shift = floor_log2 (CONST_DOUBLE_HIGH (op1))
			  + HOST_BITS_PER_WIDE_INT;
	      return expand_shift (LSHIFT_EXPR, mode, op0,
				   build_int_cst (NULL_TREE, shift),
				   target, unsignedp);
	    }
	}
        
      /* We used to test optimize here, on the grounds that it's better to
	 produce a smaller program when -O is not used.  But this causes
	 such a terrible slowdown sometimes that it seems better to always
	 use synth_mult.  */
      if (coeff != 0)
	{
	  /* Special case powers of two.  */
	  if (EXACT_POWER_OF_2_OR_ZERO_P (coeff))
	    return expand_shift (LSHIFT_EXPR, mode, op0,
				 build_int_cst (NULL_TREE, floor_log2 (coeff)),
				 target, unsignedp);

	  /* Exclude cost of op0 from max_cost to match the cost
	     calculation of the synth_mult.  */
	  max_cost = rtx_cost (gen_rtx_MULT (mode, fake_reg, op1), SET);
	  if (choose_mult_variant (mode, coeff, &algorithm, &variant,
				   max_cost))
	    return expand_mult_const (mode, op0, coeff, target,
				      &algorithm, variant);
	}
    }

  if (GET_CODE (op0) == CONST_DOUBLE)
    {
      rtx temp = op0;
      op0 = op1;
      op1 = temp;
    }

  /* Expand x*2.0 as x+x.  */
  if (GET_CODE (op1) == CONST_DOUBLE
      && SCALAR_FLOAT_MODE_P (mode))
    {
      REAL_VALUE_TYPE d;
      REAL_VALUE_FROM_CONST_DOUBLE (d, op1);

      if (REAL_VALUES_EQUAL (d, dconst2))
	{
	  op0 = force_reg (GET_MODE (op0), op0);
	  return expand_binop (mode, add_optab, op0, op0,
			       target, unsignedp, OPTAB_LIB_WIDEN);
	}
    }

  /* This used to use umul_optab if unsigned, but for non-widening multiply
     there is no difference between signed and unsigned.  */
  op0 = expand_binop (mode,
		      ! unsignedp
		      && flag_trapv && (GET_MODE_CLASS(mode) == MODE_INT)
		      ? smulv_optab : smul_optab,
		      op0, op1, target, unsignedp, OPTAB_LIB_WIDEN);
  gcc_assert (op0);
  return op0;
}