#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* machine; } ;
struct TYPE_6__ {unsigned int n_local_regs; int n_input_regs; int n_output_regs; unsigned int reg_fp; int reg_save_b0; int reg_save_ar_pfs; scalar_t__ reg_save_gp; scalar_t__ reg_save_pr; scalar_t__ reg_save_ar_unat; scalar_t__ reg_save_ar_lc; int n_spilled; scalar_t__ initialized; int /*<<< orphan*/  mask; scalar_t__ extra_spill_size; scalar_t__ spill_size; scalar_t__ spill_cfa_off; scalar_t__ total_size; scalar_t__ n_rotate_regs; } ;
struct TYPE_5__ {scalar_t__ n_varargs; scalar_t__ ia64_eh_epilogue_bsp; scalar_t__ ia64_eh_epilogue_sp; } ;
typedef  scalar_t__ HOST_WIDE_INT ;
typedef  int /*<<< orphan*/  HARD_REG_SET ;

/* Variables and functions */
 size_t AR_LC_REGNUM ; 
 size_t AR_PFS_REGNUM ; 
 size_t AR_UNAT_REGNUM ; 
 size_t BR_REG (int) ; 
 int /*<<< orphan*/  CLEAR_HARD_REG_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COPY_HARD_REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int FR_REG (int) ; 
 size_t GR_REG (int) ; 
 scalar_t__ IA64_STACK_ALIGN (scalar_t__) ; 
 unsigned int IN_REG (int) ; 
 unsigned int LOC_REG (int) ; 
 void* MAX (int,scalar_t__) ; 
 unsigned int OUT_REG (int) ; 
 unsigned int PR_REG (int) ; 
 int /*<<< orphan*/  SET_HARD_REG_BIT (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * call_used_regs ; 
 TYPE_4__* cfun ; 
 TYPE_2__ current_frame_info ; 
 scalar_t__ current_function_calls_setjmp ; 
 int /*<<< orphan*/  current_function_decl ; 
 scalar_t__ current_function_is_leaf ; 
 scalar_t__ current_function_outgoing_args_size ; 
 scalar_t__ current_function_pretend_args_size ; 
 scalar_t__ current_function_profile ; 
 int /*<<< orphan*/  diddle_return_value (int /*<<< orphan*/  (*) (scalar_t__,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 void* find_gr_spill (int) ; 
 scalar_t__ frame_pointer_needed ; 
 scalar_t__ lookup_attribute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_reg_gr_used_mask (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int* regs_ever_live ; 
 scalar_t__ reload_completed ; 

__attribute__((used)) static void
ia64_compute_frame_size (HOST_WIDE_INT size)
{
  HOST_WIDE_INT total_size;
  HOST_WIDE_INT spill_size = 0;
  HOST_WIDE_INT extra_spill_size = 0;
  HOST_WIDE_INT pretend_args_size;
  HARD_REG_SET mask;
  int n_spilled = 0;
  int spilled_gr_p = 0;
  int spilled_fr_p = 0;
  unsigned int regno;
  int i;

  if (current_frame_info.initialized)
    return;

  memset (&current_frame_info, 0, sizeof current_frame_info);
  CLEAR_HARD_REG_SET (mask);

  /* Don't allocate scratches to the return register.  */
  diddle_return_value (mark_reg_gr_used_mask, NULL);

  /* Don't allocate scratches to the EH scratch registers.  */
  if (cfun->machine->ia64_eh_epilogue_sp)
    mark_reg_gr_used_mask (cfun->machine->ia64_eh_epilogue_sp, NULL);
  if (cfun->machine->ia64_eh_epilogue_bsp)
    mark_reg_gr_used_mask (cfun->machine->ia64_eh_epilogue_bsp, NULL);

  /* Find the size of the register stack frame.  We have only 80 local
     registers, because we reserve 8 for the inputs and 8 for the
     outputs.  */

  /* Skip HARD_FRAME_POINTER_REGNUM (loc79) when frame_pointer_needed,
     since we'll be adjusting that down later.  */
  regno = LOC_REG (78) + ! frame_pointer_needed;
  for (; regno >= LOC_REG (0); regno--)
    if (regs_ever_live[regno])
      break;
  current_frame_info.n_local_regs = regno - LOC_REG (0) + 1;

  /* For functions marked with the syscall_linkage attribute, we must mark
     all eight input registers as in use, so that locals aren't visible to
     the caller.  */

  if (cfun->machine->n_varargs > 0
      || lookup_attribute ("syscall_linkage",
			   TYPE_ATTRIBUTES (TREE_TYPE (current_function_decl))))
    current_frame_info.n_input_regs = 8;
  else
    {
      for (regno = IN_REG (7); regno >= IN_REG (0); regno--)
	if (regs_ever_live[regno])
	  break;
      current_frame_info.n_input_regs = regno - IN_REG (0) + 1;
    }

  for (regno = OUT_REG (7); regno >= OUT_REG (0); regno--)
    if (regs_ever_live[regno])
      break;
  i = regno - OUT_REG (0) + 1;

#ifndef PROFILE_HOOK
  /* When -p profiling, we need one output register for the mcount argument.
     Likewise for -a profiling for the bb_init_func argument.  For -ax
     profiling, we need two output registers for the two bb_init_trace_func
     arguments.  */
  if (current_function_profile)
    i = MAX (i, 1);
#endif
  current_frame_info.n_output_regs = i;

  /* ??? No rotating register support yet.  */
  current_frame_info.n_rotate_regs = 0;

  /* Discover which registers need spilling, and how much room that
     will take.  Begin with floating point and general registers,
     which will always wind up on the stack.  */

  for (regno = FR_REG (2); regno <= FR_REG (127); regno++)
    if (regs_ever_live[regno] && ! call_used_regs[regno])
      {
	SET_HARD_REG_BIT (mask, regno);
	spill_size += 16;
	n_spilled += 1;
	spilled_fr_p = 1;
      }

  for (regno = GR_REG (1); regno <= GR_REG (31); regno++)
    if (regs_ever_live[regno] && ! call_used_regs[regno])
      {
	SET_HARD_REG_BIT (mask, regno);
	spill_size += 8;
	n_spilled += 1;
	spilled_gr_p = 1;
      }

  for (regno = BR_REG (1); regno <= BR_REG (7); regno++)
    if (regs_ever_live[regno] && ! call_used_regs[regno])
      {
	SET_HARD_REG_BIT (mask, regno);
	spill_size += 8;
	n_spilled += 1;
      }

  /* Now come all special registers that might get saved in other
     general registers.  */

  if (frame_pointer_needed)
    {
      current_frame_info.reg_fp = find_gr_spill (1);
      /* If we did not get a register, then we take LOC79.  This is guaranteed
	 to be free, even if regs_ever_live is already set, because this is
	 HARD_FRAME_POINTER_REGNUM.  This requires incrementing n_local_regs,
	 as we don't count loc79 above.  */
      if (current_frame_info.reg_fp == 0)
	{
	  current_frame_info.reg_fp = LOC_REG (79);
	  current_frame_info.n_local_regs++;
	}
    }

  if (! current_function_is_leaf)
    {
      /* Emit a save of BR0 if we call other functions.  Do this even
	 if this function doesn't return, as EH depends on this to be
	 able to unwind the stack.  */
      SET_HARD_REG_BIT (mask, BR_REG (0));

      current_frame_info.reg_save_b0 = find_gr_spill (1);
      if (current_frame_info.reg_save_b0 == 0)
	{
	  extra_spill_size += 8;
	  n_spilled += 1;
	}

      /* Similarly for ar.pfs.  */
      SET_HARD_REG_BIT (mask, AR_PFS_REGNUM);
      current_frame_info.reg_save_ar_pfs = find_gr_spill (1);
      if (current_frame_info.reg_save_ar_pfs == 0)
	{
	  extra_spill_size += 8;
	  n_spilled += 1;
	}

      /* Similarly for gp.  Note that if we're calling setjmp, the stacked
	 registers are clobbered, so we fall back to the stack.  */
      current_frame_info.reg_save_gp
	= (current_function_calls_setjmp ? 0 : find_gr_spill (1));
      if (current_frame_info.reg_save_gp == 0)
	{
	  SET_HARD_REG_BIT (mask, GR_REG (1));
	  spill_size += 8;
	  n_spilled += 1;
	}
    }
  else
    {
      if (regs_ever_live[BR_REG (0)] && ! call_used_regs[BR_REG (0)])
	{
	  SET_HARD_REG_BIT (mask, BR_REG (0));
	  extra_spill_size += 8;
	  n_spilled += 1;
	}

      if (regs_ever_live[AR_PFS_REGNUM])
	{
	  SET_HARD_REG_BIT (mask, AR_PFS_REGNUM);
	  current_frame_info.reg_save_ar_pfs = find_gr_spill (1);
	  if (current_frame_info.reg_save_ar_pfs == 0)
	    {
	      extra_spill_size += 8;
	      n_spilled += 1;
	    }
	}
    }

  /* Unwind descriptor hackery: things are most efficient if we allocate
     consecutive GR save registers for RP, PFS, FP in that order. However,
     it is absolutely critical that FP get the only hard register that's
     guaranteed to be free, so we allocated it first.  If all three did
     happen to be allocated hard regs, and are consecutive, rearrange them
     into the preferred order now.  */
  if (current_frame_info.reg_fp != 0
      && current_frame_info.reg_save_b0 == current_frame_info.reg_fp + 1
      && current_frame_info.reg_save_ar_pfs == current_frame_info.reg_fp + 2)
    {
      current_frame_info.reg_save_b0 = current_frame_info.reg_fp;
      current_frame_info.reg_save_ar_pfs = current_frame_info.reg_fp + 1;
      current_frame_info.reg_fp = current_frame_info.reg_fp + 2;
    }

  /* See if we need to store the predicate register block.  */
  for (regno = PR_REG (0); regno <= PR_REG (63); regno++)
    if (regs_ever_live[regno] && ! call_used_regs[regno])
      break;
  if (regno <= PR_REG (63))
    {
      SET_HARD_REG_BIT (mask, PR_REG (0));
      current_frame_info.reg_save_pr = find_gr_spill (1);
      if (current_frame_info.reg_save_pr == 0)
	{
	  extra_spill_size += 8;
	  n_spilled += 1;
	}

      /* ??? Mark them all as used so that register renaming and such
	 are free to use them.  */
      for (regno = PR_REG (0); regno <= PR_REG (63); regno++)
	regs_ever_live[regno] = 1;
    }

  /* If we're forced to use st8.spill, we're forced to save and restore
     ar.unat as well.  The check for existing liveness allows inline asm
     to touch ar.unat.  */
  if (spilled_gr_p || cfun->machine->n_varargs
      || regs_ever_live[AR_UNAT_REGNUM])
    {
      regs_ever_live[AR_UNAT_REGNUM] = 1;
      SET_HARD_REG_BIT (mask, AR_UNAT_REGNUM);
      current_frame_info.reg_save_ar_unat = find_gr_spill (spill_size == 0);
      if (current_frame_info.reg_save_ar_unat == 0)
	{
	  extra_spill_size += 8;
	  n_spilled += 1;
	}
    }

  if (regs_ever_live[AR_LC_REGNUM])
    {
      SET_HARD_REG_BIT (mask, AR_LC_REGNUM);
      current_frame_info.reg_save_ar_lc = find_gr_spill (spill_size == 0);
      if (current_frame_info.reg_save_ar_lc == 0)
	{
	  extra_spill_size += 8;
	  n_spilled += 1;
	}
    }

  /* If we have an odd number of words of pretend arguments written to
     the stack, then the FR save area will be unaligned.  We round the
     size of this area up to keep things 16 byte aligned.  */
  if (spilled_fr_p)
    pretend_args_size = IA64_STACK_ALIGN (current_function_pretend_args_size);
  else
    pretend_args_size = current_function_pretend_args_size;

  total_size = (spill_size + extra_spill_size + size + pretend_args_size
		+ current_function_outgoing_args_size);
  total_size = IA64_STACK_ALIGN (total_size);

  /* We always use the 16-byte scratch area provided by the caller, but
     if we are a leaf function, there's no one to which we need to provide
     a scratch area.  */
  if (current_function_is_leaf)
    total_size = MAX (0, total_size - 16);

  current_frame_info.total_size = total_size;
  current_frame_info.spill_cfa_off = pretend_args_size - 16;
  current_frame_info.spill_size = spill_size;
  current_frame_info.extra_spill_size = extra_spill_size;
  COPY_HARD_REG_SET (current_frame_info.mask, mask);
  current_frame_info.n_spilled = n_spilled;
  current_frame_info.initialized = reload_completed;
}