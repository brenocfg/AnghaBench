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
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int ABS ; 
 scalar_t__ COMMUTATIVE_ARITH_P (scalar_t__) ; 
 scalar_t__ COMPARISON_P (scalar_t__) ; 
#define  EQ 136 
 int /*<<< orphan*/  FLOAT_MODE_P (int) ; 
#define  GE 135 
 int GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  GEU 134 
#define  GT 133 
#define  GTU 132 
#define  LE 131 
#define  LEU 130 
#define  LT 129 
#define  LTU 128 
 int NE ; 
 int /*<<< orphan*/  NEG ; 
 int SMAX ; 
 int SMIN ; 
 int SUBREG ; 
 int /*<<< orphan*/  SUBREG_BYTE (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 int /*<<< orphan*/  SUBST (scalar_t__,scalar_t__) ; 
 int UMAX ; 
 int UMIN ; 
 int UNEQ ; 
 int UNKNOWN ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int ZERO_EXTEND ; 
 scalar_t__ comparison_dominates_p (int,int) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const_true_rtx ; 
 int reverse_condition (int) ; 
 int reversed_comparison_code (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ side_effects_p (scalar_t__) ; 
 scalar_t__ simplify_gen_unary (int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 scalar_t__ simplify_subreg (int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ simplify_unary_operation (int,int,scalar_t__,int) ; 
 int swap_condition (int) ; 

__attribute__((used)) static rtx
known_cond (rtx x, enum rtx_code cond, rtx reg, rtx val)
{
  enum rtx_code code = GET_CODE (x);
  rtx temp;
  const char *fmt;
  int i, j;

  if (side_effects_p (x))
    return x;

  /* If either operand of the condition is a floating point value,
     then we have to avoid collapsing an EQ comparison.  */
  if (cond == EQ
      && rtx_equal_p (x, reg)
      && ! FLOAT_MODE_P (GET_MODE (x))
      && ! FLOAT_MODE_P (GET_MODE (val)))
    return val;

  if (cond == UNEQ && rtx_equal_p (x, reg))
    return val;

  /* If X is (abs REG) and we know something about REG's relationship
     with zero, we may be able to simplify this.  */

  if (code == ABS && rtx_equal_p (XEXP (x, 0), reg) && val == const0_rtx)
    switch (cond)
      {
      case GE:  case GT:  case EQ:
	return XEXP (x, 0);
      case LT:  case LE:
	return simplify_gen_unary (NEG, GET_MODE (XEXP (x, 0)),
				   XEXP (x, 0),
				   GET_MODE (XEXP (x, 0)));
      default:
	break;
      }

  /* The only other cases we handle are MIN, MAX, and comparisons if the
     operands are the same as REG and VAL.  */

  else if (COMPARISON_P (x) || COMMUTATIVE_ARITH_P (x))
    {
      if (rtx_equal_p (XEXP (x, 0), val))
	cond = swap_condition (cond), temp = val, val = reg, reg = temp;

      if (rtx_equal_p (XEXP (x, 0), reg) && rtx_equal_p (XEXP (x, 1), val))
	{
	  if (COMPARISON_P (x))
	    {
	      if (comparison_dominates_p (cond, code))
		return const_true_rtx;

	      code = reversed_comparison_code (x, NULL);
	      if (code != UNKNOWN
		  && comparison_dominates_p (cond, code))
		return const0_rtx;
	      else
		return x;
	    }
	  else if (code == SMAX || code == SMIN
		   || code == UMIN || code == UMAX)
	    {
	      int unsignedp = (code == UMIN || code == UMAX);

	      /* Do not reverse the condition when it is NE or EQ.
		 This is because we cannot conclude anything about
		 the value of 'SMAX (x, y)' when x is not equal to y,
		 but we can when x equals y.  */
	      if ((code == SMAX || code == UMAX)
		  && ! (cond == EQ || cond == NE))
		cond = reverse_condition (cond);

	      switch (cond)
		{
		case GE:   case GT:
		  return unsignedp ? x : XEXP (x, 1);
		case LE:   case LT:
		  return unsignedp ? x : XEXP (x, 0);
		case GEU:  case GTU:
		  return unsignedp ? XEXP (x, 1) : x;
		case LEU:  case LTU:
		  return unsignedp ? XEXP (x, 0) : x;
		default:
		  break;
		}
	    }
	}
    }
  else if (code == SUBREG)
    {
      enum machine_mode inner_mode = GET_MODE (SUBREG_REG (x));
      rtx new, r = known_cond (SUBREG_REG (x), cond, reg, val);

      if (SUBREG_REG (x) != r)
	{
	  /* We must simplify subreg here, before we lose track of the
	     original inner_mode.  */
	  new = simplify_subreg (GET_MODE (x), r,
				 inner_mode, SUBREG_BYTE (x));
	  if (new)
	    return new;
	  else
	    SUBST (SUBREG_REG (x), r);
	}

      return x;
    }
  /* We don't have to handle SIGN_EXTEND here, because even in the
     case of replacing something with a modeless CONST_INT, a
     CONST_INT is already (supposed to be) a valid sign extension for
     its narrower mode, which implies it's already properly
     sign-extended for the wider mode.  Now, for ZERO_EXTEND, the
     story is different.  */
  else if (code == ZERO_EXTEND)
    {
      enum machine_mode inner_mode = GET_MODE (XEXP (x, 0));
      rtx new, r = known_cond (XEXP (x, 0), cond, reg, val);

      if (XEXP (x, 0) != r)
	{
	  /* We must simplify the zero_extend here, before we lose
	     track of the original inner_mode.  */
	  new = simplify_unary_operation (ZERO_EXTEND, GET_MODE (x),
					  r, inner_mode);
	  if (new)
	    return new;
	  else
	    SUBST (XEXP (x, 0), r);
	}

      return x;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	SUBST (XEXP (x, i), known_cond (XEXP (x, i), cond, reg, val));
      else if (fmt[i] == 'E')
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  SUBST (XVECEXP (x, i, j), known_cond (XVECEXP (x, i, j),
						cond, reg, val));
    }

  return x;
}