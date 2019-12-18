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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nonimmediate_operand (int /*<<< orphan*/ ,int) ; 
 scalar_t__ optimize ; 
 scalar_t__ reg_overlap_mentioned_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
ix86_expand_sse_cmp (rtx dest, enum rtx_code code, rtx cmp_op0, rtx cmp_op1,
		     rtx op_true, rtx op_false)
{
  enum machine_mode mode = GET_MODE (dest);
  rtx x;

  cmp_op0 = force_reg (mode, cmp_op0);
  if (!nonimmediate_operand (cmp_op1, mode))
    cmp_op1 = force_reg (mode, cmp_op1);

  if (optimize
      || reg_overlap_mentioned_p (dest, op_true)
      || reg_overlap_mentioned_p (dest, op_false))
    dest = gen_reg_rtx (mode);

  x = gen_rtx_fmt_ee (code, mode, cmp_op0, cmp_op1);
  emit_insn (gen_rtx_SET (VOIDmode, dest, x));

  return dest;
}