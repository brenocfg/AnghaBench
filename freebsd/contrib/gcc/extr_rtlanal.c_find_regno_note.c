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
typedef  enum reg_note { ____Placeholder_reg_note } reg_note ;

/* Variables and functions */
 size_t FIRST_PSEUDO_REGISTER ; 
 size_t GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  INSN_P (scalar_t__) ; 
 size_t REGNO (scalar_t__) ; 
 scalar_t__ REG_NOTES (scalar_t__) ; 
 int REG_NOTE_KIND (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int** hard_regno_nregs ; 

rtx
find_regno_note (rtx insn, enum reg_note kind, unsigned int regno)
{
  rtx link;

  /* Ignore anything that is not an INSN, JUMP_INSN or CALL_INSN.  */
  if (! INSN_P (insn))
    return 0;

  for (link = REG_NOTES (insn); link; link = XEXP (link, 1))
    if (REG_NOTE_KIND (link) == kind
	/* Verify that it is a register, so that scratch and MEM won't cause a
	   problem here.  */
	&& REG_P (XEXP (link, 0))
	&& REGNO (XEXP (link, 0)) <= regno
	&& ((REGNO (XEXP (link, 0))
	     + (REGNO (XEXP (link, 0)) >= FIRST_PSEUDO_REGISTER ? 1
		: hard_regno_nregs[REGNO (XEXP (link, 0))]
				  [GET_MODE (XEXP (link, 0))]))
	    > regno))
      return link;
  return 0;
}