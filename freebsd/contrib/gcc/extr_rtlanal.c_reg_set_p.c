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

/* Variables and functions */
 scalar_t__ CALL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLOBBER ; 
 scalar_t__ FIND_REG_INC_NOTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FIRST_PSEUDO_REGISTER ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (int /*<<< orphan*/ ) ; 
 scalar_t__ MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 scalar_t__ find_reg_fusage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ overlaps_hard_reg_set_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  regs_invalidated_by_call ; 
 scalar_t__ set_of (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
reg_set_p (rtx reg, rtx insn)
{
  /* We can be passed an insn or part of one.  If we are passed an insn,
     check if a side-effect of the insn clobbers REG.  */
  if (INSN_P (insn)
      && (FIND_REG_INC_NOTE (insn, reg)
	  || (CALL_P (insn)
	      && ((REG_P (reg)
		   && REGNO (reg) < FIRST_PSEUDO_REGISTER
		   && overlaps_hard_reg_set_p (regs_invalidated_by_call,
					       GET_MODE (reg), REGNO (reg)))
		  || MEM_P (reg)
		  || find_reg_fusage (insn, CLOBBER, reg)))))
    return 1;

  return set_of (reg, insn) != NULL_RTX;
}