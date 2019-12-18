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
struct TYPE_3__ {int outgoing_args; int frame; } ;
typedef  TYPE_1__ arm_stack_offsets ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_INT (int) ; 
 int LR_REGNUM ; 
 int /*<<< orphan*/  Pmode ; 
 unsigned long arm_compute_save_reg_mask () ; 
 TYPE_1__* arm_get_frame_offsets () ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  gen_addsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_frame_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  plus_constant (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
arm_set_return_address (rtx source, rtx scratch)
{
  arm_stack_offsets *offsets;
  HOST_WIDE_INT delta;
  rtx addr;
  unsigned long saved_regs;

  saved_regs = arm_compute_save_reg_mask ();

  if ((saved_regs & (1 << LR_REGNUM)) == 0)
    emit_move_insn (gen_rtx_REG (Pmode, LR_REGNUM), source);
  else
    {
      if (frame_pointer_needed)
	addr = plus_constant(hard_frame_pointer_rtx, -4);
      else
	{
	  /* LR will be the first saved register.  */
	  offsets = arm_get_frame_offsets ();
	  delta = offsets->outgoing_args - (offsets->frame + 4);


	  if (delta >= 4096)
	    {
	      emit_insn (gen_addsi3 (scratch, stack_pointer_rtx,
				     GEN_INT (delta & ~4095)));
	      addr = scratch;
	      delta &= 4095;
	    }
	  else
	    addr = stack_pointer_rtx;

	  addr = plus_constant (addr, delta);
	}
      emit_move_insn (gen_frame_mem (Pmode, addr), source);
    }
}