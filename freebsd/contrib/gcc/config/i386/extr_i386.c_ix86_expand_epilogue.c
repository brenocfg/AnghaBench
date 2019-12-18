#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ix86_frame {int nregs; int to_allocate; } ;
typedef  scalar_t__ rtx ;
struct TYPE_4__ {TYPE_1__* machine; } ;
struct TYPE_3__ {scalar_t__ force_align_arg_pointer; scalar_t__ use_fast_prologue_epilogue; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ EH_RETURN_STACKADJ_RTX ; 
 int FIRST_PSEUDO_REGISTER ; 
 scalar_t__ GEN_INT (int) ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_EPILOGUE_USING_MOVE ; 
 scalar_t__ TARGET_USE_LEAVE ; 
 int UNITS_PER_WORD ; 
 int /*<<< orphan*/  VOIDmode ; 
 TYPE_2__* cfun ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ current_function_args_size ; 
 scalar_t__ current_function_calls_eh_return ; 
 int current_function_pops_args ; 
 scalar_t__ current_function_sp_is_unchanging ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int frame_pointer_needed ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_addsi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_leave () ; 
 int /*<<< orphan*/  gen_leave_rex64 () ; 
 int /*<<< orphan*/  gen_popdi1 (scalar_t__) ; 
 int /*<<< orphan*/  gen_popsi1 (scalar_t__) ; 
 int /*<<< orphan*/  gen_return_indirect_internal (scalar_t__) ; 
 int /*<<< orphan*/  gen_return_internal () ; 
 int /*<<< orphan*/  gen_return_pop_internal (scalar_t__) ; 
 scalar_t__ gen_rtx_MEM (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  ix86_compute_frame_layout (struct ix86_frame*) ; 
 int /*<<< orphan*/  ix86_emit_restore_regs_using_mov (scalar_t__,int,int) ; 
 scalar_t__ ix86_save_reg (int,int) ; 
 scalar_t__ optimize_size ; 
 scalar_t__ plus_constant (scalar_t__,int) ; 
 int /*<<< orphan*/  pro_epilogue_adjust_stack (scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ stack_pointer_rtx ; 

void
ix86_expand_epilogue (int style)
{
  int regno;
  int sp_valid = !frame_pointer_needed || current_function_sp_is_unchanging;
  struct ix86_frame frame;
  HOST_WIDE_INT offset;

  ix86_compute_frame_layout (&frame);

  /* Calculate start of saved registers relative to ebp.  Special care
     must be taken for the normal return case of a function using
     eh_return: the eax and edx registers are marked as saved, but not
     restored along this path.  */
  offset = frame.nregs;
  if (current_function_calls_eh_return && style != 2)
    offset -= 2;
  offset *= -UNITS_PER_WORD;

  /* If we're only restoring one register and sp is not valid then
     using a move instruction to restore the register since it's
     less work than reloading sp and popping the register.

     The default code result in stack adjustment using add/lea instruction,
     while this code results in LEAVE instruction (or discrete equivalent),
     so it is profitable in some other cases as well.  Especially when there
     are no registers to restore.  We also use this code when TARGET_USE_LEAVE
     and there is exactly one register to pop. This heuristic may need some
     tuning in future.  */
  if ((!sp_valid && frame.nregs <= 1)
      || (TARGET_EPILOGUE_USING_MOVE
	  && cfun->machine->use_fast_prologue_epilogue
	  && (frame.nregs > 1 || frame.to_allocate))
      || (frame_pointer_needed && !frame.nregs && frame.to_allocate)
      || (frame_pointer_needed && TARGET_USE_LEAVE
	  && cfun->machine->use_fast_prologue_epilogue
	  && frame.nregs == 1)
      || current_function_calls_eh_return)
    {
      /* Restore registers.  We can use ebp or esp to address the memory
	 locations.  If both are available, default to ebp, since offsets
	 are known to be small.  Only exception is esp pointing directly to the
	 end of block of saved registers, where we may simplify addressing
	 mode.  */

      if (!frame_pointer_needed || (sp_valid && !frame.to_allocate))
	ix86_emit_restore_regs_using_mov (stack_pointer_rtx,
					  frame.to_allocate, style == 2);
      else
	ix86_emit_restore_regs_using_mov (hard_frame_pointer_rtx,
					  offset, style == 2);

      /* eh_return epilogues need %ecx added to the stack pointer.  */
      if (style == 2)
	{
	  rtx tmp, sa = EH_RETURN_STACKADJ_RTX;

	  if (frame_pointer_needed)
	    {
	      tmp = gen_rtx_PLUS (Pmode, hard_frame_pointer_rtx, sa);
	      tmp = plus_constant (tmp, UNITS_PER_WORD);
	      emit_insn (gen_rtx_SET (VOIDmode, sa, tmp));

	      tmp = gen_rtx_MEM (Pmode, hard_frame_pointer_rtx);
	      emit_move_insn (hard_frame_pointer_rtx, tmp);

	      pro_epilogue_adjust_stack (stack_pointer_rtx, sa,
					 const0_rtx, style);
	    }
	  else
	    {
	      tmp = gen_rtx_PLUS (Pmode, stack_pointer_rtx, sa);
	      tmp = plus_constant (tmp, (frame.to_allocate
                                         + frame.nregs * UNITS_PER_WORD));
	      emit_insn (gen_rtx_SET (VOIDmode, stack_pointer_rtx, tmp));
	    }
	}
      else if (!frame_pointer_needed)
	pro_epilogue_adjust_stack (stack_pointer_rtx, stack_pointer_rtx,
				   GEN_INT (frame.to_allocate
					    + frame.nregs * UNITS_PER_WORD),
				   style);
      /* If not an i386, mov & pop is faster than "leave".  */
      else if (TARGET_USE_LEAVE || optimize_size
	       || !cfun->machine->use_fast_prologue_epilogue)
	emit_insn (TARGET_64BIT ? gen_leave_rex64 () : gen_leave ());
      else
	{
	  pro_epilogue_adjust_stack (stack_pointer_rtx,
				     hard_frame_pointer_rtx,
				     const0_rtx, style);
	  if (TARGET_64BIT)
	    emit_insn (gen_popdi1 (hard_frame_pointer_rtx));
	  else
	    emit_insn (gen_popsi1 (hard_frame_pointer_rtx));
	}
    }
  else
    {
      /* First step is to deallocate the stack frame so that we can
	 pop the registers.  */
      if (!sp_valid)
	{
	  gcc_assert (frame_pointer_needed);
	  pro_epilogue_adjust_stack (stack_pointer_rtx,
				     hard_frame_pointer_rtx,
				     GEN_INT (offset), style);
	}
      else if (frame.to_allocate)
	pro_epilogue_adjust_stack (stack_pointer_rtx, stack_pointer_rtx,
				   GEN_INT (frame.to_allocate), style);

      for (regno = 0; regno < FIRST_PSEUDO_REGISTER; regno++)
	if (ix86_save_reg (regno, false))
	  {
	    if (TARGET_64BIT)
	      emit_insn (gen_popdi1 (gen_rtx_REG (Pmode, regno)));
	    else
	      emit_insn (gen_popsi1 (gen_rtx_REG (Pmode, regno)));
	  }
      if (frame_pointer_needed)
	{
	  /* Leave results in shorter dependency chains on CPUs that are
	     able to grok it fast.  */
	  if (TARGET_USE_LEAVE)
	    emit_insn (TARGET_64BIT ? gen_leave_rex64 () : gen_leave ());
	  else if (TARGET_64BIT)
	    emit_insn (gen_popdi1 (hard_frame_pointer_rtx));
	  else
	    emit_insn (gen_popsi1 (hard_frame_pointer_rtx));
	}
    }

  if (cfun->machine->force_align_arg_pointer)
    {
      emit_insn (gen_addsi3 (stack_pointer_rtx,
			     cfun->machine->force_align_arg_pointer,
			     GEN_INT (-4)));
    }

  /* Sibcall epilogues don't want a return instruction.  */
  if (style == 0)
    return;

  if (current_function_pops_args && current_function_args_size)
    {
      rtx popc = GEN_INT (current_function_pops_args);

      /* i386 can only pop 64K bytes.  If asked to pop more, pop
	 return address, do explicit add, and jump indirectly to the
	 caller.  */

      if (current_function_pops_args >= 65536)
	{
	  rtx ecx = gen_rtx_REG (SImode, 2);

	  /* There is no "pascal" calling convention in 64bit ABI.  */
	  gcc_assert (!TARGET_64BIT);

	  emit_insn (gen_popsi1 (ecx));
	  emit_insn (gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx, popc));
	  emit_jump_insn (gen_return_indirect_internal (ecx));
	}
      else
	emit_jump_insn (gen_return_pop_internal (popc));
    }
  else
    emit_jump_insn (gen_return_internal ());
}