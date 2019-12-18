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
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  V4SFmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_movhlps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_sse_shufps_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ix86_expand_reduc_v4sf (rtx (*fn) (rtx, rtx, rtx), rtx dest, rtx in)
{
  rtx tmp1, tmp2, tmp3;

  tmp1 = gen_reg_rtx (V4SFmode);
  tmp2 = gen_reg_rtx (V4SFmode);
  tmp3 = gen_reg_rtx (V4SFmode);

  emit_insn (gen_sse_movhlps (tmp1, in, in));
  emit_insn (fn (tmp2, tmp1, in));

  emit_insn (gen_sse_shufps_1 (tmp3, tmp2, tmp2,
			       GEN_INT (1), GEN_INT (1),
			       GEN_INT (1+4), GEN_INT (1+4)));
  emit_insn (fn (dest, tmp2, tmp3));
}