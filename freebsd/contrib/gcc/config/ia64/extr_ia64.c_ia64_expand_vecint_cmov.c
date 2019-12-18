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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST0_RTX (int) ; 
 int GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ gen_rtx_AND (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_IOR (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_NOT (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int ia64_expand_vecint_compare (int,int,scalar_t__,scalar_t__,scalar_t__) ; 

void
ia64_expand_vecint_cmov (rtx operands[])
{
  enum machine_mode mode = GET_MODE (operands[0]);
  enum rtx_code code = GET_CODE (operands[3]);
  bool negate;
  rtx cmp, x, ot, of;

  cmp = gen_reg_rtx (mode);
  negate = ia64_expand_vecint_compare (code, mode, cmp,
				       operands[4], operands[5]);

  ot = operands[1+negate];
  of = operands[2-negate];

  if (ot == CONST0_RTX (mode))
    {
      if (of == CONST0_RTX (mode))
	{
	  emit_move_insn (operands[0], ot);
	  return;
	}

      x = gen_rtx_NOT (mode, cmp);
      x = gen_rtx_AND (mode, x, of);
      emit_insn (gen_rtx_SET (VOIDmode, operands[0], x));
    }
  else if (of == CONST0_RTX (mode))
    {
      x = gen_rtx_AND (mode, cmp, ot);
      emit_insn (gen_rtx_SET (VOIDmode, operands[0], x));
    }
  else
    {
      rtx t, f;

      t = gen_reg_rtx (mode);
      x = gen_rtx_AND (mode, cmp, operands[1+negate]);
      emit_insn (gen_rtx_SET (VOIDmode, t, x));

      f = gen_reg_rtx (mode);
      x = gen_rtx_NOT (mode, cmp);
      x = gen_rtx_AND (mode, x, operands[2-negate]);
      emit_insn (gen_rtx_SET (VOIDmode, f, x));

      x = gen_rtx_IOR (mode, t, f);
      emit_insn (gen_rtx_SET (VOIDmode, operands[0], x));
    }
}