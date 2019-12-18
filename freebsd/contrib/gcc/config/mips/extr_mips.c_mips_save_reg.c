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
 scalar_t__ DFmode ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GP_REG_FIRST ; 
 int /*<<< orphan*/  M16_REG_P (scalar_t__) ; 
 int /*<<< orphan*/  MIPS_PROLOGUE_TEMP (scalar_t__) ; 
 scalar_t__ REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_FLOAT64 ; 
 scalar_t__ TARGET_MIPS16 ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_frame_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_set_frame_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_split_64bit_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mips_split_64bit_move_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_subword (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mips_save_reg (rtx reg, rtx mem)
{
  if (GET_MODE (reg) == DFmode && !TARGET_FLOAT64)
    {
      rtx x1, x2;

      if (mips_split_64bit_move_p (mem, reg))
	mips_split_64bit_move (mem, reg);
      else
	emit_move_insn (mem, reg);

      x1 = mips_frame_set (mips_subword (mem, 0), mips_subword (reg, 0));
      x2 = mips_frame_set (mips_subword (mem, 1), mips_subword (reg, 1));
      mips_set_frame_expr (gen_rtx_PARALLEL (VOIDmode, gen_rtvec (2, x1, x2)));
    }
  else
    {
      if (TARGET_MIPS16
	  && REGNO (reg) != GP_REG_FIRST + 31
	  && !M16_REG_P (REGNO (reg)))
	{
	  /* Save a non-mips16 register by moving it through a temporary.
	     We don't need to do this for $31 since there's a special
	     instruction for it.  */
	  emit_move_insn (MIPS_PROLOGUE_TEMP (GET_MODE (reg)), reg);
	  emit_move_insn (mem, MIPS_PROLOGUE_TEMP (GET_MODE (reg)));
	}
      else
	emit_move_insn (mem, reg);

      mips_set_frame_expr (mips_frame_set (mem, reg));
    }
}