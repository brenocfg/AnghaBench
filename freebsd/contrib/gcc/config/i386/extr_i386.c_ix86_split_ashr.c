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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 int DImode ; 
 int /*<<< orphan*/  GEN_INT (int const) ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int const INTVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_CMOVE ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_ashrdi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_ashrsi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_x86_64_shift_adj (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_x86_64_shrd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_x86_shift_adj_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_x86_shift_adj_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_x86_shrd_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtx_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  split_di (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  split_ti (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ix86_split_ashr (rtx *operands, rtx scratch, enum machine_mode mode)
{
  rtx low[2], high[2];
  int count;
  const int single_width = mode == DImode ? 32 : 64;

  if (GET_CODE (operands[2]) == CONST_INT)
    {
      (mode == DImode ? split_di : split_ti) (operands, 2, low, high);
      count = INTVAL (operands[2]) & (single_width * 2 - 1);

      if (count == single_width * 2 - 1)
	{
	  emit_move_insn (high[0], high[1]);
	  emit_insn ((mode == DImode
		      ? gen_ashrsi3
		      : gen_ashrdi3) (high[0], high[0],
				      GEN_INT (single_width - 1)));
	  emit_move_insn (low[0], high[0]);

	}
      else if (count >= single_width)
	{
	  emit_move_insn (low[0], high[1]);
	  emit_move_insn (high[0], low[0]);
	  emit_insn ((mode == DImode
		      ? gen_ashrsi3
		      : gen_ashrdi3) (high[0], high[0],
				      GEN_INT (single_width - 1)));
	  if (count > single_width)
	    emit_insn ((mode == DImode
			? gen_ashrsi3
			: gen_ashrdi3) (low[0], low[0],
					GEN_INT (count - single_width)));
	}
      else
	{
	  if (!rtx_equal_p (operands[0], operands[1]))
	    emit_move_insn (operands[0], operands[1]);
	  emit_insn ((mode == DImode
		      ? gen_x86_shrd_1
		      : gen_x86_64_shrd) (low[0], high[0], GEN_INT (count)));
	  emit_insn ((mode == DImode
		      ? gen_ashrsi3
		      : gen_ashrdi3) (high[0], high[0], GEN_INT (count)));
	}
    }
  else
    {
      if (!rtx_equal_p (operands[0], operands[1]))
	emit_move_insn (operands[0], operands[1]);

      (mode == DImode ? split_di : split_ti) (operands, 1, low, high);

      emit_insn ((mode == DImode
		  ? gen_x86_shrd_1
		  : gen_x86_64_shrd) (low[0], high[0], operands[2]));
      emit_insn ((mode == DImode
		  ? gen_ashrsi3
		  : gen_ashrdi3)  (high[0], high[0], operands[2]));

      if (TARGET_CMOVE && scratch)
	{
	  emit_move_insn (scratch, high[0]);
	  emit_insn ((mode == DImode
		      ? gen_ashrsi3
		      : gen_ashrdi3) (scratch, scratch,
				      GEN_INT (single_width - 1)));
	  emit_insn ((mode == DImode
		      ? gen_x86_shift_adj_1
		      : gen_x86_64_shift_adj) (low[0], high[0], operands[2],
					 scratch));
	}
      else
	emit_insn (gen_x86_shift_adj_3 (low[0], high[0], operands[2]));
    }
}