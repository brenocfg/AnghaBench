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
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 scalar_t__ CONST0_RTX (int) ; 
 scalar_t__ CONST_DOUBLE ; 
#define  EQ 134 
#define  GE 133 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
#define  GT 132 
 scalar_t__ HONOR_INFINITIES (int) ; 
 scalar_t__ HONOR_NANS (int) ; 
#define  LE 131 
 int LT ; 
 int LTGT ; 
 int NE ; 
#define  ORDERED 130 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 scalar_t__ TARGET_E500 ; 
 int /*<<< orphan*/  TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_ISEL ; 
#define  UNEQ 129 
#define  UNGE 128 
 int UNGT ; 
 int UNLE ; 
 int UNLT ; 
 int UNORDERED ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_trapping_math ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ gen_rtx_ABS (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_GE (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_IF_THEN_ELSE (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_MINUS (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_NEG (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ real_isinf (int /*<<< orphan*/ *) ; 
 int reverse_condition_maybe_unordered (int) ; 
 int /*<<< orphan*/  rs6000_compare_fp_p ; 
 scalar_t__ rs6000_compare_op0 ; 
 scalar_t__ rs6000_compare_op1 ; 
 int rs6000_emit_int_cmove (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  short_cint_operand (scalar_t__,int /*<<< orphan*/ ) ; 

int
rs6000_emit_cmove (rtx dest, rtx op, rtx true_cond, rtx false_cond)
{
  enum rtx_code code = GET_CODE (op);
  rtx op0 = rs6000_compare_op0;
  rtx op1 = rs6000_compare_op1;
  REAL_VALUE_TYPE c1;
  enum machine_mode compare_mode = GET_MODE (op0);
  enum machine_mode result_mode = GET_MODE (dest);
  rtx temp;
  bool is_against_zero;

  /* These modes should always match.  */
  if (GET_MODE (op1) != compare_mode
      /* In the isel case however, we can use a compare immediate, so
	 op1 may be a small constant.  */
      && (!TARGET_ISEL || !short_cint_operand (op1, VOIDmode)))
    return 0;
  if (GET_MODE (true_cond) != result_mode)
    return 0;
  if (GET_MODE (false_cond) != result_mode)
    return 0;

  /* First, work out if the hardware can do this at all, or
     if it's too slow....  */
  if (! rs6000_compare_fp_p)
    {
      if (TARGET_ISEL)
	return rs6000_emit_int_cmove (dest, op, true_cond, false_cond);
      return 0;
    }
  else if (TARGET_E500 && TARGET_HARD_FLOAT && !TARGET_FPRS
	   && SCALAR_FLOAT_MODE_P (compare_mode))
    return 0;

  is_against_zero = op1 == CONST0_RTX (compare_mode);

  /* A floating-point subtract might overflow, underflow, or produce
     an inexact result, thus changing the floating-point flags, so it
     can't be generated if we care about that.  It's safe if one side
     of the construct is zero, since then no subtract will be
     generated.  */
  if (SCALAR_FLOAT_MODE_P (compare_mode)
      && flag_trapping_math && ! is_against_zero)
    return 0;

  /* Eliminate half of the comparisons by switching operands, this
     makes the remaining code simpler.  */
  if (code == UNLT || code == UNGT || code == UNORDERED || code == NE
      || code == LTGT || code == LT || code == UNLE)
    {
      code = reverse_condition_maybe_unordered (code);
      temp = true_cond;
      true_cond = false_cond;
      false_cond = temp;
    }

  /* UNEQ and LTGT take four instructions for a comparison with zero,
     it'll probably be faster to use a branch here too.  */
  if (code == UNEQ && HONOR_NANS (compare_mode))
    return 0;

  if (GET_CODE (op1) == CONST_DOUBLE)
    REAL_VALUE_FROM_CONST_DOUBLE (c1, op1);

  /* We're going to try to implement comparisons by performing
     a subtract, then comparing against zero.  Unfortunately,
     Inf - Inf is NaN which is not zero, and so if we don't
     know that the operand is finite and the comparison
     would treat EQ different to UNORDERED, we can't do it.  */
  if (HONOR_INFINITIES (compare_mode)
      && code != GT && code != UNGE
      && (GET_CODE (op1) != CONST_DOUBLE || real_isinf (&c1))
      /* Constructs of the form (a OP b ? a : b) are safe.  */
      && ((! rtx_equal_p (op0, false_cond) && ! rtx_equal_p (op1, false_cond))
	  || (! rtx_equal_p (op0, true_cond)
	      && ! rtx_equal_p (op1, true_cond))))
    return 0;

  /* At this point we know we can use fsel.  */

  /* Reduce the comparison to a comparison against zero.  */
  if (! is_against_zero)
    {
      temp = gen_reg_rtx (compare_mode);
      emit_insn (gen_rtx_SET (VOIDmode, temp,
			      gen_rtx_MINUS (compare_mode, op0, op1)));
      op0 = temp;
      op1 = CONST0_RTX (compare_mode);
    }

  /* If we don't care about NaNs we can reduce some of the comparisons
     down to faster ones.  */
  if (! HONOR_NANS (compare_mode))
    switch (code)
      {
      case GT:
	code = LE;
	temp = true_cond;
	true_cond = false_cond;
	false_cond = temp;
	break;
      case UNGE:
	code = GE;
	break;
      case UNEQ:
	code = EQ;
	break;
      default:
	break;
      }

  /* Now, reduce everything down to a GE.  */
  switch (code)
    {
    case GE:
      break;

    case LE:
      temp = gen_reg_rtx (compare_mode);
      emit_insn (gen_rtx_SET (VOIDmode, temp, gen_rtx_NEG (compare_mode, op0)));
      op0 = temp;
      break;

    case ORDERED:
      temp = gen_reg_rtx (compare_mode);
      emit_insn (gen_rtx_SET (VOIDmode, temp, gen_rtx_ABS (compare_mode, op0)));
      op0 = temp;
      break;

    case EQ:
      temp = gen_reg_rtx (compare_mode);
      emit_insn (gen_rtx_SET (VOIDmode, temp,
			      gen_rtx_NEG (compare_mode,
					   gen_rtx_ABS (compare_mode, op0))));
      op0 = temp;
      break;

    case UNGE:
      /* a UNGE 0 <-> (a GE 0 || -a UNLT 0) */
      temp = gen_reg_rtx (result_mode);
      emit_insn (gen_rtx_SET (VOIDmode, temp,
			      gen_rtx_IF_THEN_ELSE (result_mode,
						    gen_rtx_GE (VOIDmode,
								op0, op1),
						    true_cond, false_cond)));
      false_cond = true_cond;
      true_cond = temp;

      temp = gen_reg_rtx (compare_mode);
      emit_insn (gen_rtx_SET (VOIDmode, temp, gen_rtx_NEG (compare_mode, op0)));
      op0 = temp;
      break;

    case GT:
      /* a GT 0 <-> (a GE 0 && -a UNLT 0) */
      temp = gen_reg_rtx (result_mode);
      emit_insn (gen_rtx_SET (VOIDmode, temp,
			      gen_rtx_IF_THEN_ELSE (result_mode,
						    gen_rtx_GE (VOIDmode,
								op0, op1),
						    true_cond, false_cond)));
      true_cond = false_cond;
      false_cond = temp;

      temp = gen_reg_rtx (compare_mode);
      emit_insn (gen_rtx_SET (VOIDmode, temp, gen_rtx_NEG (compare_mode, op0)));
      op0 = temp;
      break;

    default:
      gcc_unreachable ();
    }

  emit_insn (gen_rtx_SET (VOIDmode, dest,
			  gen_rtx_IF_THEN_ELSE (result_mode,
						gen_rtx_GE (VOIDmode,
							    op0, op1),
						true_cond, false_cond)));
  return 1;
}