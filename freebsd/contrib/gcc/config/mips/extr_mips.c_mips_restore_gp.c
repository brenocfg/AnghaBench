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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TARGET_ABICALLS ; 
 int /*<<< orphan*/  TARGET_EXPLICIT_RELOCS ; 
 scalar_t__ TARGET_OLDABI ; 
 int /*<<< orphan*/  current_function_outgoing_args_size ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_blockage () ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  mips_add_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
mips_restore_gp (void)
{
  rtx address, slot;

  gcc_assert (TARGET_ABICALLS && TARGET_OLDABI);

  address = mips_add_offset (pic_offset_table_rtx,
			     frame_pointer_needed
			     ? hard_frame_pointer_rtx
			     : stack_pointer_rtx,
			     current_function_outgoing_args_size);
  slot = gen_rtx_MEM (Pmode, address);

  emit_move_insn (pic_offset_table_rtx, slot);
  if (!TARGET_EXPLICIT_RELOCS)
    emit_insn (gen_blockage ());
}