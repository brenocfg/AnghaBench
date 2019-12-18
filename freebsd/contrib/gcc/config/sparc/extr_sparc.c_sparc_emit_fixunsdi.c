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
 int /*<<< orphan*/  CONST_DOUBLE_FROM_REAL_VALUE (int /*<<< orphan*/ ,int) ; 
 int DImode ; 
 int /*<<< orphan*/  GE ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REAL_VALUE_ATOF (char*,int) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const1_rtx ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_ashldi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int /*<<< orphan*/  gen_movdi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_FIX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_MINUS (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_xordi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
sparc_emit_fixunsdi (rtx *operands, enum machine_mode mode)
{
  rtx neglab, donelab, i0, i1, f0, in, out, limit;

  out = operands[0];
  in = force_reg (mode, operands[1]);
  neglab = gen_label_rtx ();
  donelab = gen_label_rtx ();
  i0 = gen_reg_rtx (DImode);
  i1 = gen_reg_rtx (DImode);
  limit = gen_reg_rtx (mode);
  f0 = gen_reg_rtx (mode);

  emit_move_insn (limit,
		  CONST_DOUBLE_FROM_REAL_VALUE (
		    REAL_VALUE_ATOF ("9223372036854775808.0", mode), mode));
  emit_cmp_and_jump_insns (in, limit, GE, NULL_RTX, mode, 0, neglab);

  emit_insn (gen_rtx_SET (VOIDmode,
			  out,
			  gen_rtx_FIX (DImode, gen_rtx_FIX (mode, in))));
  emit_jump_insn (gen_jump (donelab));
  emit_barrier ();

  emit_label (neglab);

  emit_insn (gen_rtx_SET (VOIDmode, f0, gen_rtx_MINUS (mode, in, limit)));
  emit_insn (gen_rtx_SET (VOIDmode,
			  i0,
			  gen_rtx_FIX (DImode, gen_rtx_FIX (mode, f0))));
  emit_insn (gen_movdi (i1, const1_rtx));
  emit_insn (gen_ashldi3 (i1, i1, GEN_INT (63)));
  emit_insn (gen_xordi3 (out, i0, i1));

  emit_label (donelab);
}