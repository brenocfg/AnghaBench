#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {scalar_t__ total_size; scalar_t__ spill_size; scalar_t__ spill_cfa_off; scalar_t__ reg_save_gp; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST_OK_FOR_I (scalar_t__) ; 
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 TYPE_1__ current_frame_info ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  gen_adddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  pic_offset_table_rtx ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
ia64_reload_gp (void)
{
  rtx tmp;

  if (current_frame_info.reg_save_gp)
    tmp = gen_rtx_REG (DImode, current_frame_info.reg_save_gp);
  else
    {
      HOST_WIDE_INT offset;

      offset = (current_frame_info.spill_cfa_off
	        + current_frame_info.spill_size);
      if (frame_pointer_needed)
        {
          tmp = hard_frame_pointer_rtx;
          offset = -offset;
        }
      else
        {
          tmp = stack_pointer_rtx;
          offset = current_frame_info.total_size - offset;
        }

      if (CONST_OK_FOR_I (offset))
        emit_insn (gen_adddi3 (pic_offset_table_rtx,
			       tmp, GEN_INT (offset)));
      else
        {
          emit_move_insn (pic_offset_table_rtx, GEN_INT (offset));
          emit_insn (gen_adddi3 (pic_offset_table_rtx,
			         pic_offset_table_rtx, tmp));
        }

      tmp = gen_rtx_MEM (DImode, pic_offset_table_rtx);
    }

  emit_move_insn (pic_offset_table_rtx, tmp);
}