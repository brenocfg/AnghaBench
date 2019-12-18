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
 scalar_t__ FP_REG_RTX_P (int /*<<< orphan*/ ) ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_df_high (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_load_df_low (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_store_df_high (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_subword (int /*<<< orphan*/ ,int) ; 
 scalar_t__ reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
mips_split_64bit_move (rtx dest, rtx src)
{
  if (FP_REG_RTX_P (dest))
    {
      /* Loading an FPR from memory or from GPRs.  */
      emit_insn (gen_load_df_low (copy_rtx (dest), mips_subword (src, 0)));
      emit_insn (gen_load_df_high (dest, mips_subword (src, 1),
				   copy_rtx (dest)));
    }
  else if (FP_REG_RTX_P (src))
    {
      /* Storing an FPR into memory or GPRs.  */
      emit_move_insn (mips_subword (dest, 0), mips_subword (src, 0));
      emit_insn (gen_store_df_high (mips_subword (dest, 1), src));
    }
  else
    {
      /* The operation can be split into two normal moves.  Decide in
	 which order to do them.  */
      rtx low_dest;

      low_dest = mips_subword (dest, 0);
      if (REG_P (low_dest)
	  && reg_overlap_mentioned_p (low_dest, src))
	{
	  emit_move_insn (mips_subword (dest, 1), mips_subword (src, 1));
	  emit_move_insn (low_dest, mips_subword (src, 0));
	}
      else
	{
	  emit_move_insn (low_dest, mips_subword (src, 0));
	  emit_move_insn (mips_subword (dest, 1), mips_subword (src, 1));
	}
    }
}