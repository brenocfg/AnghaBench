#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * rtx ;
struct TYPE_3__ {int saved_args; int frame; int outgoing_args; int saved_regs; } ;
typedef  TYPE_1__ arm_stack_offsets ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_EH_STACKADJ_REGNUM ; 
#define  ARM_FT_EXCEPTION 131 
#define  ARM_FT_FIQ 130 
#define  ARM_FT_INTERWORKED 129 
#define  ARM_FT_ISR 128 
 scalar_t__ ARM_FT_NORMAL ; 
 scalar_t__ ARM_FUNC_TYPE (unsigned long) ; 
 int /*<<< orphan*/  FALSE ; 
 int FIRST_FPA_REGNUM ; 
 int FIRST_IWMMXT_REGNUM ; 
 int FIRST_VFP_REGNUM ; 
 scalar_t__ FPUTYPE_FPA_EMU2 ; 
 int /*<<< orphan*/  FP_REGNUM ; 
 int /*<<< orphan*/ * GEN_INT (int) ; 
 int IP_REGNUM ; 
 scalar_t__ IS_INTERRUPT (unsigned long) ; 
 scalar_t__ IS_NAKED (unsigned long) ; 
 scalar_t__ IS_VOLATILE (unsigned long) ; 
 int LAST_ARM_REGNUM ; 
 int LAST_FPA_REGNUM ; 
 int LAST_IWMMXT_REGNUM ; 
 int LAST_VFP_REGNUM ; 
 int LR_REGNUM ; 
 scalar_t__ NEED_PLT_RELOC ; 
 int PC_REGNUM ; 
 int /*<<< orphan*/  Pmode ; 
 int SP_REGNUM ; 
 scalar_t__ TARGET_ABORT_NORETURN ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_IWMMXT ; 
 scalar_t__ TARGET_VFP ; 
 int /*<<< orphan*/  arm_arch4t ; 
 int /*<<< orphan*/  arm_arch5 ; 
 unsigned long arm_compute_save_reg_mask () ; 
 unsigned long arm_current_func_type () ; 
 scalar_t__ arm_fpu_arch ; 
 TYPE_1__* arm_get_frame_offsets () ; 
 int arm_get_vfp_saved_size () ; 
 int /*<<< orphan*/  arm_output_fldmx (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  asm_fprintf (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/ * asm_out_file ; 
 int /*<<< orphan*/  assemble_external_libcall (int /*<<< orphan*/ *) ; 
 int bit_count (unsigned long) ; 
 scalar_t__* call_used_regs ; 
 scalar_t__ current_function_calls_alloca ; 
 scalar_t__ current_function_calls_eh_return ; 
 int current_function_pretend_args_size ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  gcc_assert (unsigned long) ; 
 int /*<<< orphan*/ * gen_rtx_SYMBOL_REF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  output_add_immediate (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  output_asm_insn (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  print_multi_reg (int /*<<< orphan*/ *,char*,int,unsigned long) ; 
 scalar_t__* regs_ever_live ; 
 scalar_t__ return_used_this_function ; 
 int /*<<< orphan*/ * stack_pointer_rtx ; 
 scalar_t__ use_return_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

const char *
arm_output_epilogue (rtx sibling)
{
  int reg;
  unsigned long saved_regs_mask;
  unsigned long func_type;
  /* Floats_offset is the offset from the "virtual" frame.  In an APCS
     frame that is $fp + 4 for a non-variadic function.  */
  int floats_offset = 0;
  rtx operands[3];
  FILE * f = asm_out_file;
  unsigned int lrm_count = 0;
  int really_return = (sibling == NULL);
  int start_reg;
  arm_stack_offsets *offsets;

  /* If we have already generated the return instruction
     then it is futile to generate anything else.  */
  if (use_return_insn (FALSE, sibling) && return_used_this_function)
    return "";

  func_type = arm_current_func_type ();

  if (IS_NAKED (func_type))
    /* Naked functions don't have epilogues.  */
    return "";

  if (IS_VOLATILE (func_type) && TARGET_ABORT_NORETURN)
    {
      rtx op;

      /* A volatile function should never return.  Call abort.  */
      op = gen_rtx_SYMBOL_REF (Pmode, NEED_PLT_RELOC ? "abort(PLT)" : "abort");
      assemble_external_libcall (op);
      output_asm_insn ("bl\t%a0", &op);

      return "";
    }

  /* If we are throwing an exception, then we really must be doing a
     return, so we can't tail-call.  */
  gcc_assert (!current_function_calls_eh_return || really_return);

  offsets = arm_get_frame_offsets ();
  saved_regs_mask = arm_compute_save_reg_mask ();

  if (TARGET_IWMMXT)
    lrm_count = bit_count (saved_regs_mask);

  floats_offset = offsets->saved_args;
  /* Compute how far away the floats will be.  */
  for (reg = 0; reg <= LAST_ARM_REGNUM; reg++)
    if (saved_regs_mask & (1 << reg))
      floats_offset += 4;

  if (frame_pointer_needed)
    {
      /* This variable is for the Virtual Frame Pointer, not VFP regs.  */
      int vfp_offset = offsets->frame;

      if (arm_fpu_arch == FPUTYPE_FPA_EMU2)
	{
	  for (reg = LAST_FPA_REGNUM; reg >= FIRST_FPA_REGNUM; reg--)
	    if (regs_ever_live[reg] && !call_used_regs[reg])
	      {
		floats_offset += 12;
		asm_fprintf (f, "\tldfe\t%r, [%r, #-%d]\n",
			     reg, FP_REGNUM, floats_offset - vfp_offset);
	      }
	}
      else
	{
	  start_reg = LAST_FPA_REGNUM;

	  for (reg = LAST_FPA_REGNUM; reg >= FIRST_FPA_REGNUM; reg--)
	    {
	      if (regs_ever_live[reg] && !call_used_regs[reg])
		{
		  floats_offset += 12;

		  /* We can't unstack more than four registers at once.  */
		  if (start_reg - reg == 3)
		    {
		      asm_fprintf (f, "\tlfm\t%r, 4, [%r, #-%d]\n",
			           reg, FP_REGNUM, floats_offset - vfp_offset);
		      start_reg = reg - 1;
		    }
		}
	      else
		{
		  if (reg != start_reg)
		    asm_fprintf (f, "\tlfm\t%r, %d, [%r, #-%d]\n",
				 reg + 1, start_reg - reg,
				 FP_REGNUM, floats_offset - vfp_offset);
		  start_reg = reg - 1;
		}
	    }

	  /* Just in case the last register checked also needs unstacking.  */
	  if (reg != start_reg)
	    asm_fprintf (f, "\tlfm\t%r, %d, [%r, #-%d]\n",
			 reg + 1, start_reg - reg,
			 FP_REGNUM, floats_offset - vfp_offset);
	}

      if (TARGET_HARD_FLOAT && TARGET_VFP)
	{
	  int saved_size;

	  /* The fldmx insn does not have base+offset addressing modes,
	     so we use IP to hold the address.  */
	  saved_size = arm_get_vfp_saved_size ();

	  if (saved_size > 0)
	    {
	      floats_offset += saved_size;
	      asm_fprintf (f, "\tsub\t%r, %r, #%d\n", IP_REGNUM,
			   FP_REGNUM, floats_offset - vfp_offset);
	    }
	  start_reg = FIRST_VFP_REGNUM;
	  for (reg = FIRST_VFP_REGNUM; reg < LAST_VFP_REGNUM; reg += 2)
	    {
	      if ((!regs_ever_live[reg] || call_used_regs[reg])
		  && (!regs_ever_live[reg + 1] || call_used_regs[reg + 1]))
		{
		  if (start_reg != reg)
		    arm_output_fldmx (f, IP_REGNUM,
				      (start_reg - FIRST_VFP_REGNUM) / 2,
				      (reg - start_reg) / 2);
		  start_reg = reg + 2;
		}
	    }
	  if (start_reg != reg)
	    arm_output_fldmx (f, IP_REGNUM,
			      (start_reg - FIRST_VFP_REGNUM) / 2,
			      (reg - start_reg) / 2);
	}

      if (TARGET_IWMMXT)
	{
	  /* The frame pointer is guaranteed to be non-double-word aligned.
	     This is because it is set to (old_stack_pointer - 4) and the
	     old_stack_pointer was double word aligned.  Thus the offset to
	     the iWMMXt registers to be loaded must also be non-double-word
	     sized, so that the resultant address *is* double-word aligned.
	     We can ignore floats_offset since that was already included in
	     the live_regs_mask.  */
	  lrm_count += (lrm_count % 2 ? 2 : 1);

	  for (reg = LAST_IWMMXT_REGNUM; reg >= FIRST_IWMMXT_REGNUM; reg--)
	    if (regs_ever_live[reg] && !call_used_regs[reg])
	      {
		asm_fprintf (f, "\twldrd\t%r, [%r, #-%d]\n",
			     reg, FP_REGNUM, lrm_count * 4);
		lrm_count += 2;
	      }
	}

      /* saved_regs_mask should contain the IP, which at the time of stack
	 frame generation actually contains the old stack pointer.  So a
	 quick way to unwind the stack is just pop the IP register directly
	 into the stack pointer.  */
      gcc_assert (saved_regs_mask & (1 << IP_REGNUM));
      saved_regs_mask &= ~ (1 << IP_REGNUM);
      saved_regs_mask |=   (1 << SP_REGNUM);

      /* There are two registers left in saved_regs_mask - LR and PC.  We
	 only need to restore the LR register (the return address), but to
	 save time we can load it directly into the PC, unless we need a
	 special function exit sequence, or we are not really returning.  */
      if (really_return
	  && ARM_FUNC_TYPE (func_type) == ARM_FT_NORMAL
	  && !current_function_calls_eh_return)
	/* Delete the LR from the register mask, so that the LR on
	   the stack is loaded into the PC in the register mask.  */
	saved_regs_mask &= ~ (1 << LR_REGNUM);
      else
	saved_regs_mask &= ~ (1 << PC_REGNUM);

      /* We must use SP as the base register, because SP is one of the
         registers being restored.  If an interrupt or page fault
         happens in the ldm instruction, the SP might or might not
         have been restored.  That would be bad, as then SP will no
         longer indicate the safe area of stack, and we can get stack
         corruption.  Using SP as the base register means that it will
         be reset correctly to the original value, should an interrupt
         occur.  If the stack pointer already points at the right
         place, then omit the subtraction.  */
      if (offsets->outgoing_args != (1 + (int) bit_count (saved_regs_mask))
	  || current_function_calls_alloca)
	asm_fprintf (f, "\tsub\t%r, %r, #%d\n", SP_REGNUM, FP_REGNUM,
		     4 * bit_count (saved_regs_mask));
      print_multi_reg (f, "ldmfd\t%r", SP_REGNUM, saved_regs_mask);

      if (IS_INTERRUPT (func_type))
	/* Interrupt handlers will have pushed the
	   IP onto the stack, so restore it now.  */
	print_multi_reg (f, "ldmfd\t%r!", SP_REGNUM, 1 << IP_REGNUM);
    }
  else
    {
      /* Restore stack pointer if necessary.  */
      if (offsets->outgoing_args != offsets->saved_regs)
	{
	  operands[0] = operands[1] = stack_pointer_rtx;
	  operands[2] = GEN_INT (offsets->outgoing_args - offsets->saved_regs);
	  output_add_immediate (operands);
	}

      if (arm_fpu_arch == FPUTYPE_FPA_EMU2)
	{
	  for (reg = FIRST_FPA_REGNUM; reg <= LAST_FPA_REGNUM; reg++)
	    if (regs_ever_live[reg] && !call_used_regs[reg])
	      asm_fprintf (f, "\tldfe\t%r, [%r], #12\n",
			   reg, SP_REGNUM);
	}
      else
	{
	  start_reg = FIRST_FPA_REGNUM;

	  for (reg = FIRST_FPA_REGNUM; reg <= LAST_FPA_REGNUM; reg++)
	    {
	      if (regs_ever_live[reg] && !call_used_regs[reg])
		{
		  if (reg - start_reg == 3)
		    {
		      asm_fprintf (f, "\tlfmfd\t%r, 4, [%r]!\n",
				   start_reg, SP_REGNUM);
		      start_reg = reg + 1;
		    }
		}
	      else
		{
		  if (reg != start_reg)
		    asm_fprintf (f, "\tlfmfd\t%r, %d, [%r]!\n",
				 start_reg, reg - start_reg,
				 SP_REGNUM);

		  start_reg = reg + 1;
		}
	    }

	  /* Just in case the last register checked also needs unstacking.  */
	  if (reg != start_reg)
	    asm_fprintf (f, "\tlfmfd\t%r, %d, [%r]!\n",
			 start_reg, reg - start_reg, SP_REGNUM);
	}

      if (TARGET_HARD_FLOAT && TARGET_VFP)
	{
	  start_reg = FIRST_VFP_REGNUM;
	  for (reg = FIRST_VFP_REGNUM; reg < LAST_VFP_REGNUM; reg += 2)
	    {
	      if ((!regs_ever_live[reg] || call_used_regs[reg])
		  && (!regs_ever_live[reg + 1] || call_used_regs[reg + 1]))
		{
		  if (start_reg != reg)
		    arm_output_fldmx (f, SP_REGNUM,
				      (start_reg - FIRST_VFP_REGNUM) / 2,
				      (reg - start_reg) / 2);
		  start_reg = reg + 2;
		}
	    }
	  if (start_reg != reg)
	    arm_output_fldmx (f, SP_REGNUM,
			      (start_reg - FIRST_VFP_REGNUM) / 2,
			      (reg - start_reg) / 2);
	}
      if (TARGET_IWMMXT)
	for (reg = FIRST_IWMMXT_REGNUM; reg <= LAST_IWMMXT_REGNUM; reg++)
	  if (regs_ever_live[reg] && !call_used_regs[reg])
	    asm_fprintf (f, "\twldrd\t%r, [%r], #8\n", reg, SP_REGNUM);

      /* If we can, restore the LR into the PC.  */
      if (ARM_FUNC_TYPE (func_type) == ARM_FT_NORMAL
	  && really_return
	  && current_function_pretend_args_size == 0
	  && saved_regs_mask & (1 << LR_REGNUM)
	  && !current_function_calls_eh_return)
	{
	  saved_regs_mask &= ~ (1 << LR_REGNUM);
	  saved_regs_mask |=   (1 << PC_REGNUM);
	}

      /* Load the registers off the stack.  If we only have one register
	 to load use the LDR instruction - it is faster.  */
      if (saved_regs_mask == (1 << LR_REGNUM))
	{
	  asm_fprintf (f, "\tldr\t%r, [%r], #4\n", LR_REGNUM, SP_REGNUM);
	}
      else if (saved_regs_mask)
	{
	  if (saved_regs_mask & (1 << SP_REGNUM))
	    /* Note - write back to the stack register is not enabled
	       (i.e. "ldmfd sp!...").  We know that the stack pointer is
	       in the list of registers and if we add writeback the
	       instruction becomes UNPREDICTABLE.  */
	    print_multi_reg (f, "ldmfd\t%r", SP_REGNUM, saved_regs_mask);
	  else
	    print_multi_reg (f, "ldmfd\t%r!", SP_REGNUM, saved_regs_mask);
	}

      if (current_function_pretend_args_size)
	{
	  /* Unwind the pre-pushed regs.  */
	  operands[0] = operands[1] = stack_pointer_rtx;
	  operands[2] = GEN_INT (current_function_pretend_args_size);
	  output_add_immediate (operands);
	}
    }

  /* We may have already restored PC directly from the stack.  */
  if (!really_return || saved_regs_mask & (1 << PC_REGNUM))
    return "";

  /* Stack adjustment for exception handler.  */
  if (current_function_calls_eh_return)
    asm_fprintf (f, "\tadd\t%r, %r, %r\n", SP_REGNUM, SP_REGNUM,
		 ARM_EH_STACKADJ_REGNUM);

  /* Generate the return instruction.  */
  switch ((int) ARM_FUNC_TYPE (func_type))
    {
    case ARM_FT_ISR:
    case ARM_FT_FIQ:
      asm_fprintf (f, "\tsubs\t%r, %r, #4\n", PC_REGNUM, LR_REGNUM);
      break;

    case ARM_FT_EXCEPTION:
      asm_fprintf (f, "\tmovs\t%r, %r\n", PC_REGNUM, LR_REGNUM);
      break;

    case ARM_FT_INTERWORKED:
      asm_fprintf (f, "\tbx\t%r\n", LR_REGNUM);
      break;

    default:
      if (arm_arch5 || arm_arch4t)
	asm_fprintf (f, "\tbx\t%r\n", LR_REGNUM);
      else
	asm_fprintf (f, "\tmov\t%r, %r\n", PC_REGNUM, LR_REGNUM);
      break;
    }

  return "";
}