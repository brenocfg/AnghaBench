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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_3__ {int outgoing_args; int saved_regs; int locals_base; } ;
typedef  TYPE_1__ arm_stack_offsets ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ IS_NAKED (int /*<<< orphan*/ ) ; 
 size_t LAST_ARG_REGNUM ; 
 size_t LR_REGNUM ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  TARGET_SCHED_PROLOG ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  arm_current_func_type () ; 
 TYPE_1__* arm_get_frame_offsets () ; 
 int /*<<< orphan*/ * call_used_regs ; 
 scalar_t__ current_function_profile ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_addsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_blockage () ; 
 int /*<<< orphan*/  gen_movsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_prologue_use (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  gen_rtx_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 scalar_t__* regs_ever_live ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
thumb_expand_epilogue (void)
{
  HOST_WIDE_INT amount;
  arm_stack_offsets *offsets;
  int regno;

  /* Naked functions don't have prologues.  */
  if (IS_NAKED (arm_current_func_type ()))
    return;

  offsets = arm_get_frame_offsets ();
  amount = offsets->outgoing_args - offsets->saved_regs;

  if (frame_pointer_needed)
    {
      emit_insn (gen_movsi (stack_pointer_rtx, hard_frame_pointer_rtx));
      amount = offsets->locals_base - offsets->saved_regs;
    }

  gcc_assert (amount >= 0);
  if (amount)
    {
      if (amount < 512)
	emit_insn (gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx,
			       GEN_INT (amount)));
      else
	{
	  /* r3 is always free in the epilogue.  */
	  rtx reg = gen_rtx_REG (SImode, LAST_ARG_REGNUM);

	  emit_insn (gen_movsi (reg, GEN_INT (amount)));
	  emit_insn (gen_addsi3 (stack_pointer_rtx, stack_pointer_rtx, reg));
	}
    }

  /* Emit a USE (stack_pointer_rtx), so that
     the stack adjustment will not be deleted.  */
  emit_insn (gen_prologue_use (stack_pointer_rtx));

  if (current_function_profile || !TARGET_SCHED_PROLOG)
    emit_insn (gen_blockage ());

  /* Emit a clobber for each insn that will be restored in the epilogue,
     so that flow2 will get register lifetimes correct.  */
  for (regno = 0; regno < 13; regno++)
    if (regs_ever_live[regno] && !call_used_regs[regno])
      emit_insn (gen_rtx_CLOBBER (VOIDmode, gen_rtx_REG (SImode, regno)));

  if (! regs_ever_live[LR_REGNUM])
    emit_insn (gen_rtx_USE (VOIDmode, gen_rtx_REG (SImode, LR_REGNUM)));
}