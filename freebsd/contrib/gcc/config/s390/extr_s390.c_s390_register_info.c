#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int va_list_gpr_size; int va_list_fpr_size; TYPE_1__* machine; } ;
struct TYPE_7__ {int first_save_gpr_slot; int last_save_gpr_slot; int first_save_gpr; int first_restore_gpr; int last_save_gpr; int last_restore_gpr; scalar_t__ save_return_addr_p; scalar_t__ high_fprs; scalar_t__ fpr_bitmap; } ;
struct TYPE_6__ {int gprs; int fprs; } ;
struct TYPE_5__ {scalar_t__ split_branches_pending_p; scalar_t__ base_reg; } ;

/* Variables and functions */
 size_t BASE_REGNUM ; 
 int FP_ARG_NUM_REG ; 
 int GP_ARG_NUM_REG ; 
 size_t HARD_FRAME_POINTER_REGNUM ; 
 size_t PIC_OFFSET_TABLE_REGNUM ; 
 size_t REGNO (scalar_t__) ; 
 size_t RETURN_REGNUM ; 
 size_t STACK_POINTER_REGNUM ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_PACKED_STACK ; 
 scalar_t__ TARGET_TPF_PROFILING ; 
 TYPE_4__* cfun ; 
 TYPE_3__ cfun_frame_layout ; 
 scalar_t__ cfun_save_high_fprs_p ; 
 int /*<<< orphan*/  cfun_set_fpr_bit (int) ; 
 TYPE_2__ current_function_args_info ; 
 scalar_t__ current_function_calls_alloca ; 
 scalar_t__ current_function_calls_eh_return ; 
 int /*<<< orphan*/  current_function_is_leaf ; 
 scalar_t__ current_function_stdarg ; 
 int /*<<< orphan*/ * fixed_regs ; 
 scalar_t__ flag_pic ; 
 scalar_t__ frame_pointer_needed ; 
 scalar_t__ get_frame_size () ; 
 int /*<<< orphan*/ * global_regs ; 
 int* regs_ever_live ; 
 int /*<<< orphan*/  s390_regs_ever_clobbered (int*) ; 

__attribute__((used)) static void
s390_register_info (int clobbered_regs[])
{
  int i, j;

  /* fprs 8 - 15 are call saved for 64 Bit ABI.  */
  cfun_frame_layout.fpr_bitmap = 0;
  cfun_frame_layout.high_fprs = 0;
  if (TARGET_64BIT)
    for (i = 24; i < 32; i++)
      if (regs_ever_live[i] && !global_regs[i])
	{
	  cfun_set_fpr_bit (i - 16);
	  cfun_frame_layout.high_fprs++;
	}

  /* Find first and last gpr to be saved.  We trust regs_ever_live
     data, except that we don't save and restore global registers.

     Also, all registers with special meaning to the compiler need
     to be handled extra.  */

  s390_regs_ever_clobbered (clobbered_regs);

  for (i = 0; i < 16; i++)
    clobbered_regs[i] = clobbered_regs[i] && !global_regs[i] && !fixed_regs[i];

  if (frame_pointer_needed)
    clobbered_regs[HARD_FRAME_POINTER_REGNUM] = 1;

  if (flag_pic)
    clobbered_regs[PIC_OFFSET_TABLE_REGNUM] 
      |= regs_ever_live[PIC_OFFSET_TABLE_REGNUM];

  clobbered_regs[BASE_REGNUM] 
    |= (cfun->machine->base_reg
        && REGNO (cfun->machine->base_reg) == BASE_REGNUM);

  clobbered_regs[RETURN_REGNUM]
    |= (!current_function_is_leaf
	|| TARGET_TPF_PROFILING
	|| cfun->machine->split_branches_pending_p
	|| cfun_frame_layout.save_return_addr_p
	|| current_function_calls_eh_return
	|| current_function_stdarg);

  clobbered_regs[STACK_POINTER_REGNUM]
    |= (!current_function_is_leaf
	|| TARGET_TPF_PROFILING
	|| cfun_save_high_fprs_p
	|| get_frame_size () > 0
	|| current_function_calls_alloca
	|| current_function_stdarg);

  for (i = 6; i < 16; i++)
    if (regs_ever_live[i] || clobbered_regs[i])
      break;
  for (j = 15; j > i; j--)
    if (regs_ever_live[j] || clobbered_regs[j])
      break;

  if (i == 16)
    {
      /* Nothing to save/restore.  */
      cfun_frame_layout.first_save_gpr_slot = -1;
      cfun_frame_layout.last_save_gpr_slot = -1;
      cfun_frame_layout.first_save_gpr = -1;
      cfun_frame_layout.first_restore_gpr = -1;
      cfun_frame_layout.last_save_gpr = -1;
      cfun_frame_layout.last_restore_gpr = -1;
    }
  else
    {
      /* Save slots for gprs from i to j.  */
      cfun_frame_layout.first_save_gpr_slot = i;
      cfun_frame_layout.last_save_gpr_slot = j;

      for (i = cfun_frame_layout.first_save_gpr_slot; 
	   i < cfun_frame_layout.last_save_gpr_slot + 1; 
	   i++)
	if (clobbered_regs[i])
	  break;

      for (j = cfun_frame_layout.last_save_gpr_slot; j > i; j--)
	if (clobbered_regs[j])
	  break;
      
      if (i == cfun_frame_layout.last_save_gpr_slot + 1)
	{
	  /* Nothing to save/restore.  */
	  cfun_frame_layout.first_save_gpr = -1;
	  cfun_frame_layout.first_restore_gpr = -1;
	  cfun_frame_layout.last_save_gpr = -1;
	  cfun_frame_layout.last_restore_gpr = -1;
	}
      else
	{
	  /* Save / Restore from gpr i to j.  */
	  cfun_frame_layout.first_save_gpr = i;
	  cfun_frame_layout.first_restore_gpr = i;
	  cfun_frame_layout.last_save_gpr = j;
	  cfun_frame_layout.last_restore_gpr = j;
	}
    }

  if (current_function_stdarg)
    {
      /* Varargs functions need to save gprs 2 to 6.  */
      if (cfun->va_list_gpr_size
	  && current_function_args_info.gprs < GP_ARG_NUM_REG)
	{
	  int min_gpr = current_function_args_info.gprs;
	  int max_gpr = min_gpr + cfun->va_list_gpr_size;
	  if (max_gpr > GP_ARG_NUM_REG)
	    max_gpr = GP_ARG_NUM_REG;

	  if (cfun_frame_layout.first_save_gpr == -1
	      || cfun_frame_layout.first_save_gpr > 2 + min_gpr)
	    {
	      cfun_frame_layout.first_save_gpr = 2 + min_gpr;
	      cfun_frame_layout.first_save_gpr_slot = 2 + min_gpr;
	    }

	  if (cfun_frame_layout.last_save_gpr == -1
	      || cfun_frame_layout.last_save_gpr < 2 + max_gpr - 1)
	    {
	      cfun_frame_layout.last_save_gpr = 2 + max_gpr - 1;
	      cfun_frame_layout.last_save_gpr_slot = 2 + max_gpr - 1;
	    }
	}

      /* Mark f0, f2 for 31 bit and f0-f4 for 64 bit to be saved.  */
      if (TARGET_HARD_FLOAT && cfun->va_list_fpr_size
	  && current_function_args_info.fprs < FP_ARG_NUM_REG)
	{
	  int min_fpr = current_function_args_info.fprs;
	  int max_fpr = min_fpr + cfun->va_list_fpr_size;
	  if (max_fpr > FP_ARG_NUM_REG)
	    max_fpr = FP_ARG_NUM_REG;

	  /* ??? This is currently required to ensure proper location
	     of the fpr save slots within the va_list save area.  */
	  if (TARGET_PACKED_STACK)
	    min_fpr = 0;

	  for (i = min_fpr; i < max_fpr; i++)
	    cfun_set_fpr_bit (i);
	}
    }

  if (!TARGET_64BIT)
    for (i = 2; i < 4; i++)
      if (regs_ever_live[i + 16] && !global_regs[i + 16])
	cfun_set_fpr_bit (i);
}