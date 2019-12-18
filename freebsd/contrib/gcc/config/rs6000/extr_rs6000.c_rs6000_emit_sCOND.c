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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CCEQmode ; 
 int DImode ; 
 int EQ ; 
 int GE ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GEU ; 
 int LE ; 
 int LEU ; 
 int NE ; 
 int ORDERED ; 
 int /*<<< orphan*/  PUT_MODE (int /*<<< orphan*/ ,int) ; 
 int SImode ; 
 scalar_t__ TARGET_E500 ; 
 int /*<<< orphan*/  TARGET_FPRS ; 
 scalar_t__ TARGET_HARD_FLOAT ; 
 scalar_t__ TARGET_POWERPC64 ; 
 int UNGE ; 
 int UNLE ; 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  convert_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_e500_flip_gt_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_move_from_CR_gt_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_COMPARE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_EQ (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rs6000_compare_fp_p ; 
 int /*<<< orphan*/  rs6000_compare_op0 ; 
 int /*<<< orphan*/  rs6000_compare_op1 ; 
 int /*<<< orphan*/  rs6000_generate_compare (int) ; 
 int /*<<< orphan*/  rs6000_reverse_condition (int,int) ; 

void
rs6000_emit_sCOND (enum rtx_code code, rtx result)
{
  rtx condition_rtx;
  enum machine_mode op_mode;
  enum rtx_code cond_code;

  condition_rtx = rs6000_generate_compare (code);
  cond_code = GET_CODE (condition_rtx);

  if (TARGET_E500 && rs6000_compare_fp_p
      && !TARGET_FPRS && TARGET_HARD_FLOAT)
    {
      rtx t;

      PUT_MODE (condition_rtx, SImode);
      t = XEXP (condition_rtx, 0);

      gcc_assert (cond_code == NE || cond_code == EQ);

      if (cond_code == NE)
	emit_insn (gen_e500_flip_gt_bit (t, t));

      emit_insn (gen_move_from_CR_gt_bit (result, t));
      return;
    }

  if (cond_code == NE
      || cond_code == GE || cond_code == LE
      || cond_code == GEU || cond_code == LEU
      || cond_code == ORDERED || cond_code == UNGE || cond_code == UNLE)
    {
      rtx not_result = gen_reg_rtx (CCEQmode);
      rtx not_op, rev_cond_rtx;
      enum machine_mode cc_mode;

      cc_mode = GET_MODE (XEXP (condition_rtx, 0));

      rev_cond_rtx = gen_rtx_fmt_ee (rs6000_reverse_condition (cc_mode, cond_code),
				     SImode, XEXP (condition_rtx, 0), const0_rtx);
      not_op = gen_rtx_COMPARE (CCEQmode, rev_cond_rtx, const0_rtx);
      emit_insn (gen_rtx_SET (VOIDmode, not_result, not_op));
      condition_rtx = gen_rtx_EQ (VOIDmode, not_result, const0_rtx);
    }

  op_mode = GET_MODE (rs6000_compare_op0);
  if (op_mode == VOIDmode)
    op_mode = GET_MODE (rs6000_compare_op1);

  if (TARGET_POWERPC64 && (op_mode == DImode || rs6000_compare_fp_p))
    {
      PUT_MODE (condition_rtx, DImode);
      convert_move (result, condition_rtx, 0);
    }
  else
    {
      PUT_MODE (condition_rtx, SImode);
      emit_insn (gen_rtx_SET (VOIDmode, result, condition_rtx));
    }
}