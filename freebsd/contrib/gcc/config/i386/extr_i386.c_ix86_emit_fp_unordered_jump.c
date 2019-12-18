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
 int /*<<< orphan*/  CCNOmode ; 
 int /*<<< orphan*/  CCmode ; 
 int /*<<< orphan*/  FLAGS_REG ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  HImode ; 
 scalar_t__ TARGET_USE_SAHF ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_IF_THEN_ELSE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_LABEL_REF (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_NE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_UNORDERED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_testqi_ext_ccno_0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_x86_fnstsw_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_x86_sahf_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pc_rtx ; 

void
ix86_emit_fp_unordered_jump (rtx label)
{
  rtx reg = gen_reg_rtx (HImode);
  rtx temp;

  emit_insn (gen_x86_fnstsw_1 (reg));

  if (TARGET_USE_SAHF)
    {
      emit_insn (gen_x86_sahf_1 (reg));

      temp = gen_rtx_REG (CCmode, FLAGS_REG);
      temp = gen_rtx_UNORDERED (VOIDmode, temp, const0_rtx);
    }
  else
    {
      emit_insn (gen_testqi_ext_ccno_0 (reg, GEN_INT (0x04)));

      temp = gen_rtx_REG (CCNOmode, FLAGS_REG);
      temp = gen_rtx_NE (VOIDmode, temp, const0_rtx);
    }

  temp = gen_rtx_IF_THEN_ELSE (VOIDmode, temp,
			      gen_rtx_LABEL_REF (VOIDmode, label),
			      pc_rtx);
  temp = gen_rtx_SET (VOIDmode, pc_rtx, temp);
  emit_jump_insn (temp);
}