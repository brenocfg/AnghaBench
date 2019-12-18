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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_INT ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ LEGITIMATE_CONSTANT_P (int /*<<< orphan*/ ) ; 
 scalar_t__ LEGITIMATE_PIC_OPERAND_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ MODE_PARTIAL_INT ; 
 scalar_t__ NO_REGS ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO_REG_CLASS (scalar_t__) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  flag_pic ; 
 int general_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reload_completed ; 
 scalar_t__ trunc_int_for_mode (scalar_t__,int) ; 

int
nonmemory_operand (rtx op, enum machine_mode mode)
{
  if (CONSTANT_P (op))
    {
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

      return ((GET_MODE (op) == VOIDmode || GET_MODE (op) == mode
	       || mode == VOIDmode)
	      && (! flag_pic || LEGITIMATE_PIC_OPERAND_P (op))
	      && LEGITIMATE_CONSTANT_P (op));
    }

  if (GET_MODE (op) != mode && mode != VOIDmode)
    return 0;

  if (GET_CODE (op) == SUBREG)
    {
      /* Before reload, we can allow (SUBREG (MEM...)) as a register operand
	 because it is guaranteed to be reloaded into one.
	 Just make sure the MEM is valid in itself.
	 (Ideally, (SUBREG (MEM)...) should not exist after reload,
	 but currently it does result from (SUBREG (REG)...) where the
	 reg went on the stack.)  */
      if (! reload_completed && MEM_P (SUBREG_REG (op)))
	return general_operand (op, mode);
      op = SUBREG_REG (op);
    }

  /* We don't consider registers whose class is NO_REGS
     to be a register operand.  */
  return (REG_P (op)
	  && (REGNO (op) >= FIRST_PSEUDO_REGISTER
	      || REGNO_REG_CLASS (REGNO (op)) != NO_REGS));
}