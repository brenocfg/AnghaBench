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
 int /*<<< orphan*/  CONST1_RTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_DOUBLE_FROM_REAL_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REAL_VALUE_ATOF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_absxf2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_addxf3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_bge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_cmpxf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_fyl2x_xf3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_fyl2xp1_xf3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  standard_80387_constant_rtx (int) ; 

void ix86_emit_i387_log1p (rtx op0, rtx op1)
{
  rtx label1 = gen_label_rtx ();
  rtx label2 = gen_label_rtx ();

  rtx tmp = gen_reg_rtx (XFmode);
  rtx tmp2 = gen_reg_rtx (XFmode);

  emit_insn (gen_absxf2 (tmp, op1));
  emit_insn (gen_cmpxf (tmp,
    CONST_DOUBLE_FROM_REAL_VALUE (
       REAL_VALUE_ATOF ("0.29289321881345247561810596348408353", XFmode),
       XFmode)));
  emit_jump_insn (gen_bge (label1));

  emit_move_insn (tmp2, standard_80387_constant_rtx (4)); /* fldln2 */
  emit_insn (gen_fyl2xp1_xf3 (op0, tmp2, op1));
  emit_jump (label2);

  emit_label (label1);
  emit_move_insn (tmp, CONST1_RTX (XFmode));
  emit_insn (gen_addxf3 (tmp, op1, tmp));
  emit_move_insn (tmp2, standard_80387_constant_rtx (4)); /* fldln2 */
  emit_insn (gen_fyl2x_xf3 (op0, tmp2, tmp));

  emit_label (label2);
}