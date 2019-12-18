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
 int ARM_HARD_FRAME_POINTER_REGNUM ; 
 scalar_t__ CALLER_INTERWORKING_SLOT_SIZE ; 
 scalar_t__ INVALID_REGNUM ; 
 int LAST_LO_REGNUM ; 
 int LR_REGNUM ; 
 int PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ TARGET_BACKTRACE ; 
 int /*<<< orphan*/  TARGET_SINGLE_PIC_BASE ; 
 scalar_t__ arm_pic_register ; 
 int /*<<< orphan*/ * call_used_regs ; 
 scalar_t__ current_function_uses_pic_offset_table ; 
 scalar_t__ flag_pic ; 
 int /*<<< orphan*/  frame_pointer_needed ; 
 scalar_t__* regs_ever_live ; 
 unsigned int thumb_find_work_register (int) ; 
 scalar_t__ thumb_force_lr_save () ; 

__attribute__((used)) static unsigned long
thumb_compute_save_reg_mask (void)
{
  unsigned long mask;
  unsigned reg;

  mask = 0;
  for (reg = 0; reg < 12; reg ++)
    if (regs_ever_live[reg] && !call_used_regs[reg])
      mask |= 1 << reg;

  if (flag_pic
      && !TARGET_SINGLE_PIC_BASE
      && arm_pic_register != INVALID_REGNUM
      && current_function_uses_pic_offset_table)
    mask |= 1 << PIC_OFFSET_TABLE_REGNUM;

  /* See if we might need r11 for calls to _interwork_r11_call_via_rN().  */
  if (!frame_pointer_needed && CALLER_INTERWORKING_SLOT_SIZE > 0)
    mask |= 1 << ARM_HARD_FRAME_POINTER_REGNUM;

  /* LR will also be pushed if any lo regs are pushed.  */
  if (mask & 0xff || thumb_force_lr_save ())
    mask |= (1 << LR_REGNUM);

  /* Make sure we have a low work register if we need one.
     We will need one if we are going to push a high register,
     but we are not currently intending to push a low register.  */
  if ((mask & 0xff) == 0
      && ((mask & 0x0f00) || TARGET_BACKTRACE))
    {
      /* Use thumb_find_work_register to choose which register
	 we will use.  If the register is live then we will
	 have to push it.  Use LAST_LO_REGNUM as our fallback
	 choice for the register to select.  */
      reg = thumb_find_work_register (1 << LAST_LO_REGNUM);

      if (! call_used_regs[reg])
	mask |= 1 << reg;
    }

  return mask;
}