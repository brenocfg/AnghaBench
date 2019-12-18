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
 int /*<<< orphan*/  CONST0_RTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LT ; 
 int /*<<< orphan*/  V2SImode ; 
 int /*<<< orphan*/  V4HImode ; 
 int /*<<< orphan*/  V8QImode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_addv2si3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pmpy2_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_pmpy2_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_unpack1_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_unpack1_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ia64_expand_vecint_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ia64_expand_dot_prod_v8qi (rtx operands[4], bool unsignedp)
{
  rtx l1, l2, h1, h2, x1, x2, p1, p2, p3, p4, s1, s2, s3;

  /* Fill in x1 and x2 with the sign extension of each element.  */
  if (unsignedp)
    x1 = x2 = CONST0_RTX (V8QImode);
  else
    {
      bool neg;

      x1 = gen_reg_rtx (V8QImode);
      x2 = gen_reg_rtx (V8QImode);

      neg = ia64_expand_vecint_compare (LT, V8QImode, x1, operands[1],
					CONST0_RTX (V8QImode));
      gcc_assert (!neg);
      neg = ia64_expand_vecint_compare (LT, V8QImode, x2, operands[2],
					CONST0_RTX (V8QImode));
      gcc_assert (!neg);
    }

  l1 = gen_reg_rtx (V4HImode);
  l2 = gen_reg_rtx (V4HImode);
  h1 = gen_reg_rtx (V4HImode);
  h2 = gen_reg_rtx (V4HImode);

  emit_insn (gen_unpack1_l (gen_lowpart (V8QImode, l1), operands[1], x1));
  emit_insn (gen_unpack1_l (gen_lowpart (V8QImode, l2), operands[2], x2));
  emit_insn (gen_unpack1_h (gen_lowpart (V8QImode, h1), operands[1], x1));
  emit_insn (gen_unpack1_h (gen_lowpart (V8QImode, h2), operands[2], x2));

  p1 = gen_reg_rtx (V2SImode);
  p2 = gen_reg_rtx (V2SImode);
  p3 = gen_reg_rtx (V2SImode);
  p4 = gen_reg_rtx (V2SImode);
  emit_insn (gen_pmpy2_r (p1, l1, l2));
  emit_insn (gen_pmpy2_l (p2, l1, l2));
  emit_insn (gen_pmpy2_r (p3, h1, h2));
  emit_insn (gen_pmpy2_l (p4, h1, h2));

  s1 = gen_reg_rtx (V2SImode);
  s2 = gen_reg_rtx (V2SImode);
  s3 = gen_reg_rtx (V2SImode);
  emit_insn (gen_addv2si3 (s1, p1, p2));
  emit_insn (gen_addv2si3 (s2, p3, p4));
  emit_insn (gen_addv2si3 (s3, s1, operands[3]));
  emit_insn (gen_addv2si3 (operands[0], s2, s3));
}