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
struct TYPE_3__ {int soft_frame; int saved_args; int outgoing_args; } ;
typedef  TYPE_1__ arm_stack_offsets ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int LR_REGNUM ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SImode ; 
 int SP_REGNUM ; 
 scalar_t__ TARGET_BACKTRACE ; 
 int THUMB_HARD_FRAME_POINTER_REGNUM ; 
 int /*<<< orphan*/  VOIDmode ; 
 TYPE_1__* arm_get_frame_offsets () ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  gen_addsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_frame_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_movsi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_rtx_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 
 unsigned long thumb_compute_save_reg_mask () ; 

void
thumb_set_return_address (rtx source, rtx scratch)
{
  arm_stack_offsets *offsets;
  HOST_WIDE_INT delta;
  int reg;
  rtx addr;
  unsigned long mask;

  emit_insn (gen_rtx_USE (VOIDmode, source));

  mask = thumb_compute_save_reg_mask ();
  if (mask & (1 << LR_REGNUM))
    {
      offsets = arm_get_frame_offsets ();

      /* Find the saved regs.  */
      if (frame_pointer_needed)
	{
	  delta = offsets->soft_frame - offsets->saved_args;
	  reg = THUMB_HARD_FRAME_POINTER_REGNUM;
	}
      else
	{
	  delta = offsets->outgoing_args - offsets->saved_args;
	  reg = SP_REGNUM;
	}
      /* Allow for the stack frame.  */
      if (TARGET_BACKTRACE)
	delta -= 16;
      /* The link register is always the first saved register.  */
      delta -= 4;

      /* Construct the address.  */
      addr = gen_rtx_REG (SImode, reg);
      if ((reg != SP_REGNUM && delta >= 128)
	  || delta >= 1024)
	{
	  emit_insn (gen_movsi (scratch, GEN_INT (delta)));
	  emit_insn (gen_addsi3 (scratch, scratch, stack_pointer_rtx));
	  addr = scratch;
	}
      else
	addr = plus_constant (addr, delta);

      emit_move_insn (gen_frame_mem (Pmode, addr), source);
    }
  else
    emit_move_insn (gen_rtx_REG (Pmode, LR_REGNUM), source);
}