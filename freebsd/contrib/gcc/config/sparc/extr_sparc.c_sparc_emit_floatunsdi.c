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
 int DImode ; 
 int /*<<< orphan*/  LT ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_anddi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_iordi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int /*<<< orphan*/  gen_lshrdi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_FLOAT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sparc_emit_floatunsdi (rtx *operands, enum machine_mode mode)
{
  rtx neglab, donelab, i0, i1, f0, in, out;

  out = operands[0];
  in = force_reg (DImode, operands[1]);
  neglab = gen_label_rtx ();
  donelab = gen_label_rtx ();
  i0 = gen_reg_rtx (DImode);
  i1 = gen_reg_rtx (DImode);
  f0 = gen_reg_rtx (mode);

  emit_cmp_and_jump_insns (in, const0_rtx, LT, const0_rtx, DImode, 0, neglab);

  emit_insn (gen_rtx_SET (VOIDmode, out, gen_rtx_FLOAT (mode, in)));
  emit_jump_insn (gen_jump (donelab));
  emit_barrier ();

  emit_label (neglab);

  emit_insn (gen_lshrdi3 (i0, in, const1_rtx));
  emit_insn (gen_anddi3 (i1, in, const1_rtx));
  emit_insn (gen_iordi3 (i0, i0, i1));
  emit_insn (gen_rtx_SET (VOIDmode, f0, gen_rtx_FLOAT (mode, i0)));
  emit_insn (gen_rtx_SET (VOIDmode, out, gen_rtx_PLUS (mode, f0, f0)));

  emit_label (donelab);
}