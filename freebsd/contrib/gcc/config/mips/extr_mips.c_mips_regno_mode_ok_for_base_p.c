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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int ARG_POINTER_REGNUM ; 
 int FIRST_PSEUDO_REGISTER ; 
 int FRAME_POINTER_REGNUM ; 
 int GET_MODE_SIZE (int) ; 
 int GP_REG_P (int) ; 
 int M16_REG_P (int) ; 
 int STACK_POINTER_REGNUM ; 
 scalar_t__ TARGET_MIPS16 ; 
 int* reg_renumber ; 

int
mips_regno_mode_ok_for_base_p (int regno, enum machine_mode mode, int strict)
{
  if (regno >= FIRST_PSEUDO_REGISTER)
    {
      if (!strict)
	return true;
      regno = reg_renumber[regno];
    }

  /* These fake registers will be eliminated to either the stack or
     hard frame pointer, both of which are usually valid base registers.
     Reload deals with the cases where the eliminated form isn't valid.  */
  if (regno == ARG_POINTER_REGNUM || regno == FRAME_POINTER_REGNUM)
    return true;

  /* In mips16 mode, the stack pointer can only address word and doubleword
     values, nothing smaller.  There are two problems here:

       (a) Instantiating virtual registers can introduce new uses of the
	   stack pointer.  If these virtual registers are valid addresses,
	   the stack pointer should be too.

       (b) Most uses of the stack pointer are not made explicit until
	   FRAME_POINTER_REGNUM and ARG_POINTER_REGNUM have been eliminated.
	   We don't know until that stage whether we'll be eliminating to the
	   stack pointer (which needs the restriction) or the hard frame
	   pointer (which doesn't).

     All in all, it seems more consistent to only enforce this restriction
     during and after reload.  */
  if (TARGET_MIPS16 && regno == STACK_POINTER_REGNUM)
    return !strict || GET_MODE_SIZE (mode) == 4 || GET_MODE_SIZE (mode) == 8;

  return TARGET_MIPS16 ? M16_REG_P (regno) : GP_REG_P (regno);
}