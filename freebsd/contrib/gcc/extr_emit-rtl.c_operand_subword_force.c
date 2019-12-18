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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int BLKmode ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int VOIDmode ; 
 scalar_t__ copy_to_reg (scalar_t__) ; 
 scalar_t__ force_reg (int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 scalar_t__ operand_subword (scalar_t__,unsigned int,int,int) ; 

rtx
operand_subword_force (rtx op, unsigned int offset, enum machine_mode mode)
{
  rtx result = operand_subword (op, offset, 1, mode);

  if (result)
    return result;

  if (mode != BLKmode && mode != VOIDmode)
    {
      /* If this is a register which can not be accessed by words, copy it
	 to a pseudo register.  */
      if (REG_P (op))
	op = copy_to_reg (op);
      else
	op = force_reg (mode, op);
    }

  result = operand_subword (op, offset, 1, mode);
  gcc_assert (result);

  return result;
}