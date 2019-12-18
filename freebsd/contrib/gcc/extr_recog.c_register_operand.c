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
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ GET_MODE_SIZE (int) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MODE_COMPLEX_FLOAT ; 
 scalar_t__ MODE_COMPLEX_INT ; 
 scalar_t__ NO_REGS ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REGNO_REG_CLASS (scalar_t__) ; 
 scalar_t__ REG_CANNOT_CHANGE_MODE_P (scalar_t__,int,int) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SCALAR_FLOAT_MODE_P (int) ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 int VOIDmode ; 
 int general_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reload_completed ; 

int
register_operand (rtx op, enum machine_mode mode)
{
  if (GET_MODE (op) != mode && mode != VOIDmode)
    return 0;

  if (GET_CODE (op) == SUBREG)
    {
      rtx sub = SUBREG_REG (op);

      /* Before reload, we can allow (SUBREG (MEM...)) as a register operand
	 because it is guaranteed to be reloaded into one.
	 Just make sure the MEM is valid in itself.
	 (Ideally, (SUBREG (MEM)...) should not exist after reload,
	 but currently it does result from (SUBREG (REG)...) where the
	 reg went on the stack.)  */
      if (! reload_completed && MEM_P (sub))
	return general_operand (op, mode);

#ifdef CANNOT_CHANGE_MODE_CLASS
      if (REG_P (sub)
	  && REGNO (sub) < FIRST_PSEUDO_REGISTER
	  && REG_CANNOT_CHANGE_MODE_P (REGNO (sub), GET_MODE (sub), mode)
	  && GET_MODE_CLASS (GET_MODE (sub)) != MODE_COMPLEX_INT
	  && GET_MODE_CLASS (GET_MODE (sub)) != MODE_COMPLEX_FLOAT)
	return 0;
#endif

      /* FLOAT_MODE subregs can't be paradoxical.  Combine will occasionally
	 create such rtl, and we must reject it.  */
      if (SCALAR_FLOAT_MODE_P (GET_MODE (op))
	  && GET_MODE_SIZE (GET_MODE (op)) > GET_MODE_SIZE (GET_MODE (sub)))
	return 0;

      op = sub;
    }

  /* We don't consider registers whose class is NO_REGS
     to be a register operand.  */
  return (REG_P (op)
	  && (REGNO (op) >= FIRST_PSEUDO_REGISTER
	      || REGNO_REG_CLASS (REGNO (op)) != NO_REGS));
}