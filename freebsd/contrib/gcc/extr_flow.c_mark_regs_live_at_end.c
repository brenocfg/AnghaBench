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
typedef  int /*<<< orphan*/  regset ;

/* Variables and functions */
 unsigned int EH_RETURN_DATA_REGNO (unsigned int) ; 
 scalar_t__ EH_RETURN_HANDLER_RTX ; 
 scalar_t__ EH_RETURN_STACKADJ_RTX ; 
 scalar_t__ EPILOGUE_USES (unsigned int) ; 
 int /*<<< orphan*/  EXIT_IGNORE_STACK ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 unsigned int FRAME_POINTER_REGNUM ; 
 int /*<<< orphan*/  FRAME_POINTER_REQUIRED ; 
 unsigned int HARD_FRAME_POINTER_REGNUM ; 
 scalar_t__ HAVE_epilogue ; 
 unsigned int INVALID_REGNUM ; 
 int /*<<< orphan*/  LOCAL_REGNO (unsigned int) ; 
 size_t PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ REG_P (scalar_t__) ; 
 int /*<<< orphan*/  SET_REGNO_REG_SET (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int STACK_POINTER_REGNUM ; 
 int /*<<< orphan*/  TEST_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  current_function_calls_alloca ; 
 scalar_t__ current_function_calls_eh_return ; 
 scalar_t__ current_function_sp_is_unchanging ; 
 int /*<<< orphan*/  diddle_return_value (int /*<<< orphan*/  (*) (scalar_t__,int /*<<< orphan*/ ),int /*<<< orphan*/ ) ; 
 scalar_t__ epilogue_completed ; 
 scalar_t__* fixed_regs ; 
 scalar_t__ flag_omit_frame_pointer ; 
 scalar_t__ frame_pointer_needed ; 
 scalar_t__* global_regs ; 
 int /*<<< orphan*/  mark_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* regs_ever_live ; 
 int /*<<< orphan*/  regs_invalidated_by_call ; 
 scalar_t__ reload_completed ; 

__attribute__((used)) static void
mark_regs_live_at_end (regset set)
{
  unsigned int i;

  /* If exiting needs the right stack value, consider the stack pointer
     live at the end of the function.  */
  if ((HAVE_epilogue && epilogue_completed)
      || ! EXIT_IGNORE_STACK
      || (! FRAME_POINTER_REQUIRED
	  && ! current_function_calls_alloca
	  && flag_omit_frame_pointer)
      || current_function_sp_is_unchanging)
    {
      SET_REGNO_REG_SET (set, STACK_POINTER_REGNUM);
    }

  /* Mark the frame pointer if needed at the end of the function.  If
     we end up eliminating it, it will be removed from the live list
     of each basic block by reload.  */

  if (! reload_completed || frame_pointer_needed)
    {
      SET_REGNO_REG_SET (set, FRAME_POINTER_REGNUM);
#if FRAME_POINTER_REGNUM != HARD_FRAME_POINTER_REGNUM
      /* If they are different, also mark the hard frame pointer as live.  */
      if (! LOCAL_REGNO (HARD_FRAME_POINTER_REGNUM))
	SET_REGNO_REG_SET (set, HARD_FRAME_POINTER_REGNUM);
#endif
    }

#ifndef PIC_OFFSET_TABLE_REG_CALL_CLOBBERED
  /* Many architectures have a GP register even without flag_pic.
     Assume the pic register is not in use, or will be handled by
     other means, if it is not fixed.  */
  if ((unsigned) PIC_OFFSET_TABLE_REGNUM != INVALID_REGNUM
      && fixed_regs[PIC_OFFSET_TABLE_REGNUM])
    SET_REGNO_REG_SET (set, PIC_OFFSET_TABLE_REGNUM);
#endif

  /* Mark all global registers, and all registers used by the epilogue
     as being live at the end of the function since they may be
     referenced by our caller.  */
  for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
    if (global_regs[i] || EPILOGUE_USES (i))
      SET_REGNO_REG_SET (set, i);

  if (HAVE_epilogue && epilogue_completed)
    {
      /* Mark all call-saved registers that we actually used.  */
      for (i = 0; i < FIRST_PSEUDO_REGISTER; i++)
	if (regs_ever_live[i] && ! LOCAL_REGNO (i)
	    && ! TEST_HARD_REG_BIT (regs_invalidated_by_call, i))
	  SET_REGNO_REG_SET (set, i);
    }

#ifdef EH_RETURN_DATA_REGNO
  /* Mark the registers that will contain data for the handler.  */
  if (reload_completed && current_function_calls_eh_return)
    for (i = 0; ; ++i)
      {
	unsigned regno = EH_RETURN_DATA_REGNO(i);
	if (regno == INVALID_REGNUM)
	  break;
	SET_REGNO_REG_SET (set, regno);
      }
#endif
#ifdef EH_RETURN_STACKADJ_RTX
  if ((! HAVE_epilogue || ! epilogue_completed)
      && current_function_calls_eh_return)
    {
      rtx tmp = EH_RETURN_STACKADJ_RTX;
      if (tmp && REG_P (tmp))
	mark_reg (tmp, set);
    }
#endif
#ifdef EH_RETURN_HANDLER_RTX
  if ((! HAVE_epilogue || ! epilogue_completed)
      && current_function_calls_eh_return)
    {
      rtx tmp = EH_RETURN_HANDLER_RTX;
      if (tmp && REG_P (tmp))
	mark_reg (tmp, set);
    }
#endif

  /* Mark function return value.  */
  diddle_return_value (mark_reg, set);
}