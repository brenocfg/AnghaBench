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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ LEGITIMATE_CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LEGITIMATE_PIC_OPERAND_P (int /*<<< orphan*/ ) ; 
 int MEM ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ MODE_PARTIAL_INT ; 
 scalar_t__ NO_REGS ; 
 int REG ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO_REG_CLASS (scalar_t__) ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 int SUBREG ; 
 scalar_t__ SUBREG_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_pic ; 
 scalar_t__ memory_address_p (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_completed ; 
 scalar_t__ trunc_int_for_mode (scalar_t__,int) ; 
 int /*<<< orphan*/  volatile_ok ; 

int
general_operand (rtx op, enum machine_mode mode)
{
  enum rtx_code code = GET_CODE (op);

  if (mode == VOIDmode)
    mode = GET_MODE (op);

  /* Don't accept CONST_INT or anything similar
     if the caller wants something floating.  */
  if (GET_MODE (op) == VOIDmode && mode != VOIDmode
      && GET_MODE_CLASS (mode) != MODE_INT
      && GET_MODE_CLASS (mode) != MODE_PARTIAL_INT)
    return 0;

  if (GET_CODE (op) == CONST_INT
      && mode != VOIDmode
      && trunc_int_for_mode (INTVAL (op), mode) != INTVAL (op))
    return 0;

  if (CONSTANT_P (op))
    return ((GET_MODE (op) == VOIDmode || GET_MODE (op) == mode
	     || mode == VOIDmode)
	    && (! flag_pic || LEGITIMATE_PIC_OPERAND_P (op))
	    && LEGITIMATE_CONSTANT_P (op));

  /* Except for certain constants with VOIDmode, already checked for,
     OP's mode must match MODE if MODE specifies a mode.  */

  if (GET_MODE (op) != mode)
    return 0;

  if (code == SUBREG)
    {
      rtx sub = SUBREG_REG (op);

#ifdef INSN_SCHEDULING
      /* On machines that have insn scheduling, we want all memory
	 reference to be explicit, so outlaw paradoxical SUBREGs.
	 However, we must allow them after reload so that they can
	 get cleaned up by cleanup_subreg_operands.  */
      if (!reload_completed && MEM_P (sub)
	  && GET_MODE_SIZE (mode) > GET_MODE_SIZE (GET_MODE (sub)))
	return 0;
#endif
      /* Avoid memories with nonzero SUBREG_BYTE, as offsetting the memory
         may result in incorrect reference.  We should simplify all valid
         subregs of MEM anyway.  But allow this after reload because we
	 might be called from cleanup_subreg_operands.

	 ??? This is a kludge.  */
      if (!reload_completed && SUBREG_BYTE (op) != 0
	  && MEM_P (sub))
	return 0;

      /* FLOAT_MODE subregs can't be paradoxical.  Combine will occasionally
	 create such rtl, and we must reject it.  */
      if (SCALAR_FLOAT_MODE_P (GET_MODE (op))
	  && GET_MODE_SIZE (GET_MODE (op)) > GET_MODE_SIZE (GET_MODE (sub)))
	return 0;

      op = sub;
      code = GET_CODE (op);
    }

  if (code == REG)
    /* A register whose class is NO_REGS is not a general operand.  */
    return (REGNO (op) >= FIRST_PSEUDO_REGISTER
	    || REGNO_REG_CLASS (REGNO (op)) != NO_REGS);

  if (code == MEM)
    {
      rtx y = XEXP (op, 0);

      if (! volatile_ok && MEM_VOLATILE_P (op))
	return 0;

      /* Use the mem's mode, since it will be reloaded thus.  */
      if (memory_address_p (GET_MODE (op), y))
	return 1;
    }

  return 0;
}