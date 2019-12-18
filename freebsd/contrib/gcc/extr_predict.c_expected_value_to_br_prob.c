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

/* Variables and functions */
#define  CODE_LABEL 130 
 int CONST_INT ; 
 int GET_CODE (scalar_t__) ; 
#define  JUMP_INSN 129 
 int /*<<< orphan*/  JUMP_P (scalar_t__) ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
#define  NOTE 128 
 scalar_t__ NOTE_EXPECTED_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  NOTE_INSN_EXPECTED_VALUE ; 
 int /*<<< orphan*/  NOTE_LINE_NUMBER (scalar_t__) ; 
 int /*<<< orphan*/  NOT_TAKEN ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  PRED_BUILTIN_EXPECT ; 
 scalar_t__ SET_SRC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAKEN ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  any_condjump_p (scalar_t__) ; 
 scalar_t__ canonicalize_condition (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int,int) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const_true_rtx ; 
 int /*<<< orphan*/  delete_insn (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_rtx_fmt_ee (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ get_insns () ; 
 int /*<<< orphan*/  pc_set (scalar_t__) ; 
 int /*<<< orphan*/  predict_insn_def (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_set_p (scalar_t__,scalar_t__) ; 
 scalar_t__ simplify_rtx (scalar_t__) ; 

void
expected_value_to_br_prob (void)
{
  rtx insn, cond, ev = NULL_RTX, ev_reg = NULL_RTX;

  for (insn = get_insns (); insn ; insn = NEXT_INSN (insn))
    {
      switch (GET_CODE (insn))
	{
	case NOTE:
	  /* Look for expected value notes.  */
	  if (NOTE_LINE_NUMBER (insn) == NOTE_INSN_EXPECTED_VALUE)
	    {
	      ev = NOTE_EXPECTED_VALUE (insn);
	      ev_reg = XEXP (ev, 0);
	      delete_insn (insn);
	    }
	  continue;

	case CODE_LABEL:
	  /* Never propagate across labels.  */
	  ev = NULL_RTX;
	  continue;

	case JUMP_INSN:
	  /* Look for simple conditional branches.  If we haven't got an
	     expected value yet, no point going further.  */
	  if (!JUMP_P (insn) || ev == NULL_RTX
	      || ! any_condjump_p (insn))
	    continue;
	  break;

	default:
	  /* Look for insns that clobber the EV register.  */
	  if (ev && reg_set_p (ev_reg, insn))
	    ev = NULL_RTX;
	  continue;
	}

      /* Collect the branch condition, hopefully relative to EV_REG.  */
      /* ???  At present we'll miss things like
		(expected_value (eq r70 0))
		(set r71 -1)
		(set r80 (lt r70 r71))
		(set pc (if_then_else (ne r80 0) ...))
	 as canonicalize_condition will render this to us as
		(lt r70, r71)
	 Could use cselib to try and reduce this further.  */
      cond = XEXP (SET_SRC (pc_set (insn)), 0);
      cond = canonicalize_condition (insn, cond, 0, NULL, ev_reg,
				     false, false);
      if (! cond || XEXP (cond, 0) != ev_reg
	  || GET_CODE (XEXP (cond, 1)) != CONST_INT)
	continue;

      /* Substitute and simplify.  Given that the expression we're
	 building involves two constants, we should wind up with either
	 true or false.  */
      cond = gen_rtx_fmt_ee (GET_CODE (cond), VOIDmode,
			     XEXP (ev, 1), XEXP (cond, 1));
      cond = simplify_rtx (cond);

      /* Turn the condition into a scaled branch probability.  */
      gcc_assert (cond == const_true_rtx || cond == const0_rtx);
      predict_insn_def (insn, PRED_BUILTIN_EXPECT,
		        cond == const_true_rtx ? TAKEN : NOT_TAKEN);
    }
}