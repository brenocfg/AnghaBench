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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_6__ {TYPE_2__* machine; } ;
struct TYPE_4__ {int mask; int /*<<< orphan*/  gp_sp_offset; } ;
struct TYPE_5__ {TYPE_1__ frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 TYPE_3__* cfun ; 
 int /*<<< orphan*/  compute_frame_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_frame_size () ; 
 int /*<<< orphan*/  mips_add_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
mips_set_return_address (rtx address, rtx scratch)
{
  rtx slot_address;

  compute_frame_size (get_frame_size ());
  gcc_assert ((cfun->machine->frame.mask >> 31) & 1);
  slot_address = mips_add_offset (scratch, stack_pointer_rtx,
				  cfun->machine->frame.gp_sp_offset);

  emit_move_insn (gen_rtx_MEM (GET_MODE (address), slot_address), address);
}