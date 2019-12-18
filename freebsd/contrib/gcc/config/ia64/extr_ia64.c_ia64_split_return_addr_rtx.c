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
struct TYPE_2__ {scalar_t__ reg_save_b0; scalar_t__ total_size; int /*<<< orphan*/  mask; scalar_t__ spill_size; scalar_t__ spill_cfa_off; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 unsigned int BR_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_OK_FOR_I (scalar_t__) ; 
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 unsigned int GR_REG (int) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ TEST_HARD_REG_BIT (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__ current_frame_info ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ frame_pointer_needed ; 
 int /*<<< orphan*/  gen_adddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MEM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  hard_frame_pointer_rtx ; 
 int /*<<< orphan*/  stack_pointer_rtx ; 

void
ia64_split_return_addr_rtx (rtx dest)
{
  rtx src;

  if (TEST_HARD_REG_BIT (current_frame_info.mask, BR_REG (0)))
    {
      if (current_frame_info.reg_save_b0 != 0)
	src = gen_rtx_REG (DImode, current_frame_info.reg_save_b0);
      else
	{
	  HOST_WIDE_INT off;
	  unsigned int regno;

	  /* Compute offset from CFA for BR0.  */
	  /* ??? Must be kept in sync with ia64_expand_prologue.  */
	  off = (current_frame_info.spill_cfa_off
		 + current_frame_info.spill_size);
	  for (regno = GR_REG (1); regno <= GR_REG (31); ++regno)
	    if (TEST_HARD_REG_BIT (current_frame_info.mask, regno))
	      off -= 8;

	  /* Convert CFA offset to a register based offset.  */
	  if (frame_pointer_needed)
	    src = hard_frame_pointer_rtx;
	  else
	    {
	      src = stack_pointer_rtx;
	      off += current_frame_info.total_size;
	    }

	  /* Load address into scratch register.  */
	  if (CONST_OK_FOR_I (off))
	    emit_insn (gen_adddi3 (dest, src, GEN_INT (off)));
	  else
	    {
	      emit_move_insn (dest, GEN_INT (off));
	      emit_insn (gen_adddi3 (dest, src, dest));
	    }

	  src = gen_rtx_MEM (Pmode, dest);
	}
    }
  else
    src = gen_rtx_REG (DImode, BR_REG (0));

  emit_move_insn (dest, src);
}