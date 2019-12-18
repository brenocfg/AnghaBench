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
 scalar_t__ GENERAL_REGS ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ INSN ; 
 scalar_t__ MEM ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ PATTERN (scalar_t__) ; 
 scalar_t__ REG ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 scalar_t__ REGNO_REG_CLASS (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_OR_SUBREG_RTX (scalar_t__) ; 
 scalar_t__ SET ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ note_invalid_constants (scalar_t__,int,int) ; 

__attribute__((used)) static bool
arm_memory_load_p (rtx insn)
{
  rtx body, lhs, rhs;;

  if (insn == NULL_RTX || GET_CODE (insn) != INSN)
    return false;

  body = PATTERN (insn);

  if (GET_CODE (body) != SET)
    return false;

  lhs = XEXP (body, 0);
  rhs = XEXP (body, 1);

  lhs = REG_OR_SUBREG_RTX (lhs);

  /* If the destination is not a general purpose
     register we do not have to worry.  */
  if (GET_CODE (lhs) != REG
      || REGNO_REG_CLASS (REGNO (lhs)) != GENERAL_REGS)
    return false;

  /* As well as loads from memory we also have to react
     to loads of invalid constants which will be turned
     into loads from the minipool.  */
  return (GET_CODE (rhs) == MEM
	  || GET_CODE (rhs) == SYMBOL_REF
	  || note_invalid_constants (insn, -1, false));
}