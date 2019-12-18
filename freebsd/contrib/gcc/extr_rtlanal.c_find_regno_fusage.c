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

/* Variables and functions */
 scalar_t__ CALL_INSN_FUNCTION_USAGE (scalar_t__) ; 
 int /*<<< orphan*/  CALL_P (scalar_t__) ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (scalar_t__) ; 
 size_t GET_MODE (scalar_t__) ; 
 unsigned int REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 unsigned int** hard_regno_nregs ; 

int
find_regno_fusage (rtx insn, enum rtx_code code, unsigned int regno)
{
  rtx link;

  /* CALL_INSN_FUNCTION_USAGE information cannot contain references
     to pseudo registers, so don't bother checking.  */

  if (regno >= FIRST_PSEUDO_REGISTER
      || !CALL_P (insn) )
    return 0;

  for (link = CALL_INSN_FUNCTION_USAGE (insn); link; link = XEXP (link, 1))
    {
      unsigned int regnote;
      rtx op, reg;

      if (GET_CODE (op = XEXP (link, 0)) == code
	  && REG_P (reg = XEXP (op, 0))
	  && (regnote = REGNO (reg)) <= regno
	  && regnote + hard_regno_nregs[regnote][GET_MODE (reg)] > regno)
	return 1;
    }

  return 0;
}