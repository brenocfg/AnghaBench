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
 int /*<<< orphan*/  CONST0_RTX (int) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LT ; 
#define  V4HImode 129 
#define  V8QImode 128 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_addv2si3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_addv4hi3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_lowpart (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_unpack1_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_unpack1_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_unpack2_h (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_unpack2_l (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ia64_expand_vecint_compare (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ia64_expand_widen_sum (rtx operands[3], bool unsignedp)
{
  rtx l, h, x, s;
  enum machine_mode wmode, mode;
  rtx (*unpack_l) (rtx, rtx, rtx);
  rtx (*unpack_h) (rtx, rtx, rtx);
  rtx (*plus) (rtx, rtx, rtx);

  wmode = GET_MODE (operands[0]);
  mode = GET_MODE (operands[1]);

  switch (mode)
    {
    case V8QImode:
      unpack_l = gen_unpack1_l;
      unpack_h = gen_unpack1_h;
      plus = gen_addv4hi3;
      break;
    case V4HImode:
      unpack_l = gen_unpack2_l;
      unpack_h = gen_unpack2_h;
      plus = gen_addv2si3;
      break;
    default:
      gcc_unreachable ();
    }

  /* Fill in x with the sign extension of each element in op1.  */
  if (unsignedp)
    x = CONST0_RTX (mode);
  else
    {
      bool neg;

      x = gen_reg_rtx (mode);

      neg = ia64_expand_vecint_compare (LT, mode, x, operands[1],
					CONST0_RTX (mode));
      gcc_assert (!neg);
    }

  l = gen_reg_rtx (wmode);
  h = gen_reg_rtx (wmode);
  s = gen_reg_rtx (wmode);

  emit_insn (unpack_l (gen_lowpart (mode, l), operands[1], x));
  emit_insn (unpack_h (gen_lowpart (mode, h), operands[1], x));
  emit_insn (plus (s, l, operands[2]));
  emit_insn (plus (operands[0], h, s));
}