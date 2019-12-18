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
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 scalar_t__ PLUS ; 
 int REGNO (scalar_t__) ; 
 scalar_t__ REG_P (scalar_t__) ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ form_sum (scalar_t__,scalar_t__) ; 
 scalar_t__* reg_equiv_constant ; 
 scalar_t__* reg_renumber ; 

__attribute__((used)) static rtx
subst_indexed_address (rtx addr)
{
  rtx op0 = 0, op1 = 0, op2 = 0;
  rtx tem;
  int regno;

  if (GET_CODE (addr) == PLUS)
    {
      /* Try to find a register to replace.  */
      op0 = XEXP (addr, 0), op1 = XEXP (addr, 1), op2 = 0;
      if (REG_P (op0)
	  && (regno = REGNO (op0)) >= FIRST_PSEUDO_REGISTER
	  && reg_renumber[regno] < 0
	  && reg_equiv_constant[regno] != 0)
	op0 = reg_equiv_constant[regno];
      else if (REG_P (op1)
	       && (regno = REGNO (op1)) >= FIRST_PSEUDO_REGISTER
	       && reg_renumber[regno] < 0
	       && reg_equiv_constant[regno] != 0)
	op1 = reg_equiv_constant[regno];
      else if (GET_CODE (op0) == PLUS
	       && (tem = subst_indexed_address (op0)) != op0)
	op0 = tem;
      else if (GET_CODE (op1) == PLUS
	       && (tem = subst_indexed_address (op1)) != op1)
	op1 = tem;
      else
	return addr;

      /* Pick out up to three things to add.  */
      if (GET_CODE (op1) == PLUS)
	op2 = XEXP (op1, 1), op1 = XEXP (op1, 0);
      else if (GET_CODE (op0) == PLUS)
	op2 = op1, op1 = XEXP (op0, 1), op0 = XEXP (op0, 0);

      /* Compute the sum.  */
      if (op2 != 0)
	op1 = form_sum (op1, op2);
      if (op1 != 0)
	op0 = form_sum (op0, op1);

      return op0;
    }
  return addr;
}