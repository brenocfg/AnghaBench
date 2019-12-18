#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {scalar_t__ emit; } ;

/* Variables and functions */
 unsigned int ARG_POINTER_REGNUM ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 unsigned int FRAME_POINTER_REGNUM ; 
 unsigned int HARD_FRAME_POINTER_REGNUM ; 
 size_t PIC_OFFSET_TABLE_REGNUM ; 
 int Pmode ; 
 unsigned int RETURN_ADDRESS_POINTER_REGNUM ; 
 unsigned int STACK_POINTER_REGNUM ; 
 int /*<<< orphan*/  arg_pointer_rtx ; 
 TYPE_1__* cfun ; 
 scalar_t__* fixed_regs ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  frame_pointer_rtx ; 
 int /*<<< orphan*/  gen_raw_REG (int,unsigned int) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 
 int* reg_raw_mode ; 
 int /*<<< orphan*/ * regno_reg_rtx ; 
 int /*<<< orphan*/  reload_completed ; 
 int /*<<< orphan*/  reload_in_progress ; 
 int /*<<< orphan*/  return_address_pointer_rtx ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

rtx
gen_rtx_REG (enum machine_mode mode, unsigned int regno)
{
  /* In case the MD file explicitly references the frame pointer, have
     all such references point to the same frame pointer.  This is
     used during frame pointer elimination to distinguish the explicit
     references to these registers from pseudos that happened to be
     assigned to them.

     If we have eliminated the frame pointer or arg pointer, we will
     be using it as a normal register, for example as a spill
     register.  In such cases, we might be accessing it in a mode that
     is not Pmode and therefore cannot use the pre-allocated rtx.

     Also don't do this when we are making new REGs in reload, since
     we don't want to get confused with the real pointers.  */

  if (mode == Pmode && !reload_in_progress)
    {
      if (regno == FRAME_POINTER_REGNUM
	  && (!reload_completed || frame_pointer_needed))
	return frame_pointer_rtx;
#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM
      if (regno == HARD_FRAME_POINTER_REGNUM
	  && (!reload_completed || frame_pointer_needed))
	return hard_frame_pointer_rtx;
#endif
#if FRAME_POINTER_REGNUM != ARG_POINTER_REGNUM && HARD_FRAME_POINTER_REGNUM != ARG_POINTER_REGNUM
      if (regno == ARG_POINTER_REGNUM)
	return arg_pointer_rtx;
#endif
#ifdef RETURN_ADDRESS_POINTER_REGNUM
      if (regno == RETURN_ADDRESS_POINTER_REGNUM)
	return return_address_pointer_rtx;
#endif
      if (regno == (unsigned) PIC_OFFSET_TABLE_REGNUM
	  && fixed_regs[PIC_OFFSET_TABLE_REGNUM])
	return pic_offset_table_rtx;
      if (regno == STACK_POINTER_REGNUM)
	return stack_pointer_rtx;
    }

#if 0
  /* If the per-function register table has been set up, try to re-use
     an existing entry in that table to avoid useless generation of RTL.

     This code is disabled for now until we can fix the various backends
     which depend on having non-shared hard registers in some cases.   Long
     term we want to re-enable this code as it can significantly cut down
     on the amount of useless RTL that gets generated.

     We'll also need to fix some code that runs after reload that wants to
     set ORIGINAL_REGNO.  */

  if (cfun
      && cfun->emit
      && regno_reg_rtx
      && regno < FIRST_PSEUDO_REGISTER
      && reg_raw_mode[regno] == mode)
    return regno_reg_rtx[regno];
#endif

  return gen_raw_REG (mode, regno);
}