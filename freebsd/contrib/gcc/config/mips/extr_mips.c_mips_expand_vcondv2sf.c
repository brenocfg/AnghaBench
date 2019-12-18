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

/* Variables and functions */
 int /*<<< orphan*/  CCV2mode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_mips_cond_move_tf_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_scc_ps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mips_reverse_fp_cond_p (int*) ; 

void
mips_expand_vcondv2sf (rtx dest, rtx true_src, rtx false_src,
		       enum rtx_code cond, rtx cmp_op0, rtx cmp_op1)
{
  rtx cmp_result;
  bool reversed_p;

  reversed_p = mips_reverse_fp_cond_p (&cond);
  cmp_result = gen_reg_rtx (CCV2mode);
  emit_insn (gen_scc_ps (cmp_result,
			 gen_rtx_fmt_ee (cond, VOIDmode, cmp_op0, cmp_op1)));
  if (reversed_p)
    emit_insn (gen_mips_cond_move_tf_ps (dest, false_src, true_src,
					 cmp_result));
  else
    emit_insn (gen_mips_cond_move_tf_ps (dest, true_src, false_src,
					 cmp_result));
}