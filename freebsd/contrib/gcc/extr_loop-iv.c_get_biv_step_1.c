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
struct df_ref {int dummy; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum iv_grd_result { ____Placeholder_iv_grd_result } iv_grd_result ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTANT_P (scalar_t__) ; 
 scalar_t__ DF_REF_INSN (struct df_ref*) ; 
 int const GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 int GRD_INVALID ; 
 int GRD_INVARIANT ; 
 int GRD_MAYBE_BIV ; 
#define  MINUS 133 
 scalar_t__ NULL_RTX ; 
#define  PLUS 132 
#define  REG 131 
 scalar_t__ SET_SRC (scalar_t__) ; 
#define  SIGN_EXTEND 130 
#define  SUBREG 129 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
 int UNKNOWN ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
#define  ZERO_EXTEND 128 
 scalar_t__ const0_rtx ; 
 scalar_t__ find_reg_equal_equiv_note (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int iv_get_reaching_def (scalar_t__,scalar_t__,struct df_ref**) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  simple_reg_p (scalar_t__) ; 
 scalar_t__ simplify_gen_binary (int const,int,scalar_t__,scalar_t__) ; 
 scalar_t__ single_set (scalar_t__) ; 
 int /*<<< orphan*/  subreg_lowpart_p (scalar_t__) ; 

__attribute__((used)) static bool
get_biv_step_1 (struct df_ref *def, rtx reg,
		rtx *inner_step, enum machine_mode *inner_mode,
		enum rtx_code *extend, enum machine_mode outer_mode,
		rtx *outer_step)
{
  rtx set, rhs, op0 = NULL_RTX, op1 = NULL_RTX;
  rtx next, nextr, tmp;
  enum rtx_code code;
  rtx insn = DF_REF_INSN (def);
  struct df_ref *next_def;
  enum iv_grd_result res;

  set = single_set (insn);
  if (!set)
    return false;

  rhs = find_reg_equal_equiv_note (insn);
  if (rhs)
    rhs = XEXP (rhs, 0);
  else
    rhs = SET_SRC (set);

  code = GET_CODE (rhs);
  switch (code)
    {
    case SUBREG:
    case REG:
      next = rhs;
      break;

    case PLUS:
    case MINUS:
      op0 = XEXP (rhs, 0);
      op1 = XEXP (rhs, 1);

      if (code == PLUS && CONSTANT_P (op0))
	{
	  tmp = op0; op0 = op1; op1 = tmp;
	}

      if (!simple_reg_p (op0)
	  || !CONSTANT_P (op1))
	return false;

      if (GET_MODE (rhs) != outer_mode)
	{
	  /* ppc64 uses expressions like

	     (set x:SI (plus:SI (subreg:SI y:DI) 1)).

	     this is equivalent to

	     (set x':DI (plus:DI y:DI 1))
	     (set x:SI (subreg:SI (x':DI)).  */
	  if (GET_CODE (op0) != SUBREG)
	    return false;
	  if (GET_MODE (SUBREG_REG (op0)) != outer_mode)
	    return false;
	}

      next = op0;
      break;

    case SIGN_EXTEND:
    case ZERO_EXTEND:
      if (GET_MODE (rhs) != outer_mode)
	return false;

      op0 = XEXP (rhs, 0);
      if (!simple_reg_p (op0))
	return false;

      next = op0;
      break;

    default:
      return false;
    }

  if (GET_CODE (next) == SUBREG)
    {
      if (!subreg_lowpart_p (next))
	return false;

      nextr = SUBREG_REG (next);
      if (GET_MODE (nextr) != outer_mode)
	return false;
    }
  else
    nextr = next;

  res = iv_get_reaching_def (insn, nextr, &next_def);

  if (res == GRD_INVALID || res == GRD_INVARIANT)
    return false;

  if (res == GRD_MAYBE_BIV)
    {
      if (!rtx_equal_p (nextr, reg))
	return false;

      *inner_step = const0_rtx;
      *extend = UNKNOWN;
      *inner_mode = outer_mode;
      *outer_step = const0_rtx;
    }
  else if (!get_biv_step_1 (next_def, reg,
			    inner_step, inner_mode, extend, outer_mode,
			    outer_step))
    return false;

  if (GET_CODE (next) == SUBREG)
    {
      enum machine_mode amode = GET_MODE (next);

      if (GET_MODE_SIZE (amode) > GET_MODE_SIZE (*inner_mode))
	return false;

      *inner_mode = amode;
      *inner_step = simplify_gen_binary (PLUS, outer_mode,
					 *inner_step, *outer_step);
      *outer_step = const0_rtx;
      *extend = UNKNOWN;
    }

  switch (code)
    {
    case REG:
    case SUBREG:
      break;

    case PLUS:
    case MINUS:
      if (*inner_mode == outer_mode
	  /* See comment in previous switch.  */
	  || GET_MODE (rhs) != outer_mode)
	*inner_step = simplify_gen_binary (code, outer_mode,
					   *inner_step, op1);
      else
	*outer_step = simplify_gen_binary (code, outer_mode,
					   *outer_step, op1);
      break;

    case SIGN_EXTEND:
    case ZERO_EXTEND:
      gcc_assert (GET_MODE (op0) == *inner_mode
		  && *extend == UNKNOWN
		  && *outer_step == const0_rtx);

      *extend = code;
      break;

    default:
      return false;
    }

  return true;
}