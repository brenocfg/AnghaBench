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

/* Variables and functions */
 scalar_t__ ARM_FT_FIQ ; 
 scalar_t__ ARM_FUNC_TYPE (unsigned long) ; 
 unsigned int EH_RETURN_DATA_REGNO (unsigned int) ; 
 size_t HARD_FRAME_POINTER_REGNUM ; 
 unsigned int INVALID_REGNUM ; 
 scalar_t__ IS_INTERRUPT (unsigned long) ; 
 int PIC_OFFSET_TABLE_REGNUM ; 
 int /*<<< orphan*/  TARGET_APCS_FRAME ; 
 int /*<<< orphan*/  TARGET_SINGLE_PIC_BASE ; 
 unsigned long arm_current_func_type () ; 
 unsigned int arm_pic_register ; 
 scalar_t__* call_used_regs ; 
 scalar_t__ current_function_calls_eh_return ; 
 int /*<<< orphan*/  current_function_is_leaf ; 
 scalar_t__ current_function_uses_pic_offset_table ; 
 scalar_t__ flag_pic ; 
 int /*<<< orphan*/  frame_pointer_needed ; 
 scalar_t__* regs_ever_live ; 

__attribute__((used)) static unsigned long
arm_compute_save_reg0_reg12_mask (void)
{
  unsigned long func_type = arm_current_func_type ();
  unsigned long save_reg_mask = 0;
  unsigned int reg;

  if (IS_INTERRUPT (func_type))
    {
      unsigned int max_reg;
      /* Interrupt functions must not corrupt any registers,
	 even call clobbered ones.  If this is a leaf function
	 we can just examine the registers used by the RTL, but
	 otherwise we have to assume that whatever function is
	 called might clobber anything, and so we have to save
	 all the call-clobbered registers as well.  */
      if (ARM_FUNC_TYPE (func_type) == ARM_FT_FIQ)
	/* FIQ handlers have registers r8 - r12 banked, so
	   we only need to check r0 - r7, Normal ISRs only
	   bank r14 and r15, so we must check up to r12.
	   r13 is the stack pointer which is always preserved,
	   so we do not need to consider it here.  */
	max_reg = 7;
      else
	max_reg = 12;

      for (reg = 0; reg <= max_reg; reg++)
	if (regs_ever_live[reg]
	    || (! current_function_is_leaf && call_used_regs [reg]))
	  save_reg_mask |= (1 << reg);

      /* Also save the pic base register if necessary.  */
      if (flag_pic
	  && !TARGET_SINGLE_PIC_BASE
	  && arm_pic_register != INVALID_REGNUM
	  && current_function_uses_pic_offset_table)
	save_reg_mask |= 1 << PIC_OFFSET_TABLE_REGNUM;
    }
  else
    {
      /* In the normal case we only need to save those registers
	 which are call saved and which are used by this function.  */
      for (reg = 0; reg <= 10; reg++)
	if (regs_ever_live[reg] && ! call_used_regs [reg])
	  save_reg_mask |= (1 << reg);

      /* Handle the frame pointer as a special case.  */
      if (! TARGET_APCS_FRAME
	  && ! frame_pointer_needed
	  && regs_ever_live[HARD_FRAME_POINTER_REGNUM]
	  && ! call_used_regs[HARD_FRAME_POINTER_REGNUM])
	save_reg_mask |= 1 << HARD_FRAME_POINTER_REGNUM;

      /* If we aren't loading the PIC register,
	 don't stack it even though it may be live.  */
      if (flag_pic
	  && !TARGET_SINGLE_PIC_BASE
	  && arm_pic_register != INVALID_REGNUM
	  && (regs_ever_live[PIC_OFFSET_TABLE_REGNUM]
	      || current_function_uses_pic_offset_table))
	save_reg_mask |= 1 << PIC_OFFSET_TABLE_REGNUM;
    }

  /* Save registers so the exception handler can modify them.  */
  if (current_function_calls_eh_return)
    {
      unsigned int i;

      for (i = 0; ; i++)
	{
	  reg = EH_RETURN_DATA_REGNO (i);
	  if (reg == INVALID_REGNUM)
	    break;
	  save_reg_mask |= 1 << reg;
	}
    }

  return save_reg_mask;
}