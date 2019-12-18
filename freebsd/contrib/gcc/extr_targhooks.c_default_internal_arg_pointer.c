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
 size_t ARG_POINTER_REGNUM ; 
 size_t FRAME_POINTER_REGNUM ; 
 size_t STACK_POINTER_REGNUM ; 
 int /*<<< orphan*/  copy_to_reg (int /*<<< orphan*/ ) ; 
 scalar_t__* fixed_regs ; 
 int /*<<< orphan*/  virtual_incoming_args_rtx ; 

rtx
default_internal_arg_pointer (void)
{
  /* If the reg that the virtual arg pointer will be translated into is
     not a fixed reg or is the stack pointer, make a copy of the virtual
     arg pointer, and address parms via the copy.  The frame pointer is
     considered fixed even though it is not marked as such.  */
  if ((ARG_POINTER_REGNUM == STACK_POINTER_REGNUM
       || ! (fixed_regs[ARG_POINTER_REGNUM]
	     || ARG_POINTER_REGNUM == FRAME_POINTER_REGNUM)))
    return copy_to_reg (virtual_incoming_args_rtx);
  else
    return virtual_incoming_args_rtx;
}