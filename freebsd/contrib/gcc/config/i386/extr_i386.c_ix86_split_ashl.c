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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ ANY_QI_REG_P (scalar_t__) ; 
 int /*<<< orphan*/  CCZmode ; 
 scalar_t__ CONST_INT ; 
 int DImode ; 
 int /*<<< orphan*/  FLAGS_REG ; 
 scalar_t__ GEN_INT (int const) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int const INTVAL (scalar_t__) ; 
 int QImode ; 
 int SImode ; 
 scalar_t__ TARGET_CMOVE ; 
 scalar_t__ TARGET_PARTIAL_REG_STALL ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const1_rtx ; 
 scalar_t__ constm1_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_anddi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_andsi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_ashldi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_ashlsi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_lowpart (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_lshrdi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_lshrsi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_EQ (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_NE (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_STRICT_LOW_PART (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_ZERO_EXTEND (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_testqi_ccz_1 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_x86_64_shift_adj (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_x86_64_shld (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_x86_shift_adj_1 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_x86_shift_adj_2 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_x86_shld_1 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_xordi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_xorsi3 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ix86_expand_ashl_const (scalar_t__,int,int) ; 
 int /*<<< orphan*/  ix86_expand_clear (scalar_t__) ; 
 scalar_t__ optimize_size ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  split_di (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  split_ti (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub1 (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub10 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub11 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub12 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub3 (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub7 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub8 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub9 (scalar_t__*,int,scalar_t__*,scalar_t__*) ; 

void
ix86_split_ashl (rtx *operands, rtx scratch, enum machine_mode mode)
{
  rtx low[2], high[2];
  int count;
  const int single_width = mode == DImode ? 32 : 64;

  if (GET_CODE (operands[2]) == CONST_INT)
    {
      (mode == DImode ? split_di : split_ti) (operands, 2, low, high);
      count = INTVAL (operands[2]) & (single_width * 2 - 1);

      if (count >= single_width)
	{
	  emit_move_insn (high[0], low[1]);
	  emit_move_insn (low[0], const0_rtx);

	  if (count > single_width)
	    ix86_expand_ashl_const (high[0], count - single_width, mode);
	}
      else
	{
	  if (!rtx_equal_p (operands[0], operands[1]))
	    emit_move_insn (operands[0], operands[1]);
	  emit_insn ((mode == DImode
		     ? gen_x86_shld_1
		     : gen_x86_64_shld) (high[0], low[0], GEN_INT (count)));
	  ix86_expand_ashl_const (low[0], count, mode);
	}
      return;
    }

  (mode == DImode ? split_di : split_ti) (operands, 1, low, high);

  if (operands[1] == const1_rtx)
    {
      /* Assuming we've chosen a QImode capable registers, then 1 << N
	 can be done with two 32/64-bit shifts, no branches, no cmoves.  */
      if (ANY_QI_REG_P (low[0]) && ANY_QI_REG_P (high[0]))
	{
	  rtx s, d, flags = gen_rtx_REG (CCZmode, FLAGS_REG);

	  ix86_expand_clear (low[0]);
	  ix86_expand_clear (high[0]);
	  emit_insn (gen_testqi_ccz_1 (operands[2], GEN_INT (single_width)));

	  d = gen_lowpart (QImode, low[0]);
	  d = gen_rtx_STRICT_LOW_PART (VOIDmode, d);
	  s = gen_rtx_EQ (QImode, flags, const0_rtx);
	  emit_insn (gen_rtx_SET (VOIDmode, d, s));

	  d = gen_lowpart (QImode, high[0]);
	  d = gen_rtx_STRICT_LOW_PART (VOIDmode, d);
	  s = gen_rtx_NE (QImode, flags, const0_rtx);
	  emit_insn (gen_rtx_SET (VOIDmode, d, s));
	}

      /* Otherwise, we can get the same results by manually performing
	 a bit extract operation on bit 5/6, and then performing the two
	 shifts.  The two methods of getting 0/1 into low/high are exactly
	 the same size.  Avoiding the shift in the bit extract case helps
	 pentium4 a bit; no one else seems to care much either way.  */
      else
	{
	  rtx x;

	  if (TARGET_PARTIAL_REG_STALL && !optimize_size)
	    x = gen_rtx_ZERO_EXTEND (mode == DImode ? SImode : DImode, operands[2]);
	  else
	    x = gen_lowpart (mode == DImode ? SImode : DImode, operands[2]);
	  emit_insn (gen_rtx_SET (VOIDmode, high[0], x));

	  emit_insn ((mode == DImode
		      ? gen_lshrsi3
		      : gen_lshrdi3) (high[0], high[0], GEN_INT (mode == DImode ? 5 : 6)));
	  emit_insn ((mode == DImode
		      ? gen_andsi3
		      : gen_anddi3) (high[0], high[0], GEN_INT (1)));
	  emit_move_insn (low[0], high[0]);
	  emit_insn ((mode == DImode
		      ? gen_xorsi3
		      : gen_xordi3) (low[0], low[0], GEN_INT (1)));
	}

      emit_insn ((mode == DImode
		    ? gen_ashlsi3
		    : gen_ashldi3) (low[0], low[0], operands[2]));
      emit_insn ((mode == DImode
		    ? gen_ashlsi3
		    : gen_ashldi3) (high[0], high[0], operands[2]));
      return;
    }

  if (operands[1] == constm1_rtx)
    {
      /* For -1 << N, we can avoid the shld instruction, because we
	 know that we're shifting 0...31/63 ones into a -1.  */
      emit_move_insn (low[0], constm1_rtx);
      if (optimize_size)
	emit_move_insn (high[0], low[0]);
      else
	emit_move_insn (high[0], constm1_rtx);
    }
  else
    {
      if (!rtx_equal_p (operands[0], operands[1]))
	emit_move_insn (operands[0], operands[1]);

      (mode == DImode ? split_di : split_ti) (operands, 1, low, high);
      emit_insn ((mode == DImode
		  ? gen_x86_shld_1
		  : gen_x86_64_shld) (high[0], low[0], operands[2]));
    }

  emit_insn ((mode == DImode ? gen_ashlsi3 : gen_ashldi3) (low[0], low[0], operands[2]));

  if (TARGET_CMOVE && scratch)
    {
      ix86_expand_clear (scratch);
      emit_insn ((mode == DImode
		  ? gen_x86_shift_adj_1
		  : gen_x86_64_shift_adj) (high[0], low[0], operands[2], scratch));
    }
  else
    emit_insn (gen_x86_shift_adj_2 (high[0], low[0], operands[2]));
}