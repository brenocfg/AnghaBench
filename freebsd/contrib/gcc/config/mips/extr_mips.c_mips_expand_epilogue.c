#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
struct TYPE_6__ {TYPE_2__* machine; } ;
struct TYPE_4__ {scalar_t__ total_size; scalar_t__ args_size; int mask; int fmask; } ;
struct TYPE_5__ {TYPE_1__ frame; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ EH_RETURN_STACKADJ_RTX ; 
 scalar_t__ GEN_INT (scalar_t__) ; 
 scalar_t__ GP_REG_FIRST ; 
 scalar_t__ MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ MIPS_EPILOGUE_TEMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MIPS_MAX_FIRST_STACK_STEP ; 
 int /*<<< orphan*/  Pmode ; 
 int RA_MASK ; 
 int /*<<< orphan*/  SMALL_OPERAND (scalar_t__) ; 
 scalar_t__ TARGET_ABICALLS ; 
 int /*<<< orphan*/  TARGET_EXPLICIT_RELOCS ; 
 scalar_t__ TARGET_MIPS16 ; 
 scalar_t__ TARGET_NEWABI ; 
 TYPE_3__* cfun ; 
 scalar_t__ current_function_calls_eh_return ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  frame_pointer_needed ; 
 int /*<<< orphan*/  gen_add3_insn (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_blockage () ; 
 int /*<<< orphan*/  gen_return () ; 
 int /*<<< orphan*/  gen_return_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hard_frame_pointer_rtx ; 
 scalar_t__ mips_can_use_return_insn () ; 
 int /*<<< orphan*/  mips_for_each_saved_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_restore_reg ; 
 scalar_t__ stack_pointer_rtx ; 

void
mips_expand_epilogue (int sibcall_p)
{
  HOST_WIDE_INT step1, step2;
  rtx base, target;

  if (!sibcall_p && mips_can_use_return_insn ())
    {
      emit_jump_insn (gen_return ());
      return;
    }

  /* Split the frame into two.  STEP1 is the amount of stack we should
     deallocate before restoring the registers.  STEP2 is the amount we
     should deallocate afterwards.

     Start off by assuming that no registers need to be restored.  */
  step1 = cfun->machine->frame.total_size;
  step2 = 0;

  /* Work out which register holds the frame address.  Account for the
     frame pointer offset used by mips16 code.  */
  if (!frame_pointer_needed)
    base = stack_pointer_rtx;
  else
    {
      base = hard_frame_pointer_rtx;
      if (TARGET_MIPS16)
	step1 -= cfun->machine->frame.args_size;
    }

  /* If we need to restore registers, deallocate as much stack as
     possible in the second step without going out of range.  */
  if ((cfun->machine->frame.mask | cfun->machine->frame.fmask) != 0)
    {
      step2 = MIN (step1, MIPS_MAX_FIRST_STACK_STEP);
      step1 -= step2;
    }

  /* Set TARGET to BASE + STEP1.  */
  target = base;
  if (step1 > 0)
    {
      rtx adjust;

      /* Get an rtx for STEP1 that we can add to BASE.  */
      adjust = GEN_INT (step1);
      if (!SMALL_OPERAND (step1))
	{
	  emit_move_insn (MIPS_EPILOGUE_TEMP (Pmode), adjust);
	  adjust = MIPS_EPILOGUE_TEMP (Pmode);
	}

      /* Normal mode code can copy the result straight into $sp.  */
      if (!TARGET_MIPS16)
	target = stack_pointer_rtx;

      emit_insn (gen_add3_insn (target, base, adjust));
    }

  /* Copy TARGET into the stack pointer.  */
  if (target != stack_pointer_rtx)
    emit_move_insn (stack_pointer_rtx, target);

  /* If we're using addressing macros for n32/n64 abicalls, $gp is
     implicitly used by all SYMBOL_REFs.  We must emit a blockage
     insn before restoring it.  */
  if (TARGET_ABICALLS && TARGET_NEWABI && !TARGET_EXPLICIT_RELOCS)
    emit_insn (gen_blockage ());

  /* Restore the registers.  */
  mips_for_each_saved_reg (cfun->machine->frame.total_size - step2,
			   mips_restore_reg);

  /* Deallocate the final bit of the frame.  */
  if (step2 > 0)
    emit_insn (gen_add3_insn (stack_pointer_rtx,
			      stack_pointer_rtx,
			      GEN_INT (step2)));

  /* Add in the __builtin_eh_return stack adjustment.  We need to
     use a temporary in mips16 code.  */
  if (current_function_calls_eh_return)
    {
      if (TARGET_MIPS16)
	{
	  emit_move_insn (MIPS_EPILOGUE_TEMP (Pmode), stack_pointer_rtx);
	  emit_insn (gen_add3_insn (MIPS_EPILOGUE_TEMP (Pmode),
				    MIPS_EPILOGUE_TEMP (Pmode),
				    EH_RETURN_STACKADJ_RTX));
	  emit_move_insn (stack_pointer_rtx, MIPS_EPILOGUE_TEMP (Pmode));
	}
      else
	emit_insn (gen_add3_insn (stack_pointer_rtx,
				  stack_pointer_rtx,
				  EH_RETURN_STACKADJ_RTX));
    }

  if (!sibcall_p)
    {
      /* The mips16 loads the return address into $7, not $31.  */
      if (TARGET_MIPS16 && (cfun->machine->frame.mask & RA_MASK) != 0)
	emit_jump_insn (gen_return_internal (gen_rtx_REG (Pmode,
							  GP_REG_FIRST + 7)));
      else
	emit_jump_insn (gen_return_internal (gen_rtx_REG (Pmode,
							  GP_REG_FIRST + 31)));
    }
}