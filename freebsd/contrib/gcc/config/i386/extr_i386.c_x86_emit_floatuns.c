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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  AND ; 
 int DImode ; 
 int GET_MODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IOR ; 
 int /*<<< orphan*/  LSHIFTRT ; 
 int /*<<< orphan*/  LT ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 int Pmode ; 
 int SImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/ * const1_rtx ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expand_float (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * expand_simple_binop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * force_reg (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_jump (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gen_label_rtx () ; 
 int /*<<< orphan*/ * gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_FLOAT (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
x86_emit_floatuns (rtx operands[2])
{
  rtx neglab, donelab, i0, i1, f0, in, out;
  enum machine_mode mode, inmode;

  inmode = GET_MODE (operands[1]);
  gcc_assert (inmode == SImode || inmode == DImode);

  out = operands[0];
  in = force_reg (inmode, operands[1]);
  mode = GET_MODE (out);
  neglab = gen_label_rtx ();
  donelab = gen_label_rtx ();
  i1 = gen_reg_rtx (Pmode);
  f0 = gen_reg_rtx (mode);

  emit_cmp_and_jump_insns (in, const0_rtx, LT, const0_rtx, Pmode, 0, neglab);

  emit_insn (gen_rtx_SET (VOIDmode, out, gen_rtx_FLOAT (mode, in)));
  emit_jump_insn (gen_jump (donelab));
  emit_barrier ();

  emit_label (neglab);

  i0 = expand_simple_binop (Pmode, LSHIFTRT, in, const1_rtx, NULL, 1, OPTAB_DIRECT);
  i1 = expand_simple_binop (Pmode, AND, in, const1_rtx, NULL, 1, OPTAB_DIRECT);
  i0 = expand_simple_binop (Pmode, IOR, i0, i1, i0, 1, OPTAB_DIRECT);
  expand_float (f0, i0, 0);
  emit_insn (gen_rtx_SET (VOIDmode, out, gen_rtx_PLUS (mode, f0, f0)));

  emit_label (donelab);
}