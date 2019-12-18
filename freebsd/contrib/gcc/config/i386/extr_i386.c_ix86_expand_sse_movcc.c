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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST0_RTX (int) ; 
 int GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ force_reg (int,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ gen_rtx_AND (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_IOR (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_NOT (int,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ optimize ; 

__attribute__((used)) static void
ix86_expand_sse_movcc (rtx dest, rtx cmp, rtx op_true, rtx op_false)
{
  enum machine_mode mode = GET_MODE (dest);
  rtx t2, t3, x;

  if (op_false == CONST0_RTX (mode))
    {
      op_true = force_reg (mode, op_true);
      x = gen_rtx_AND (mode, cmp, op_true);
      emit_insn (gen_rtx_SET (VOIDmode, dest, x));
    }
  else if (op_true == CONST0_RTX (mode))
    {
      op_false = force_reg (mode, op_false);
      x = gen_rtx_NOT (mode, cmp);
      x = gen_rtx_AND (mode, x, op_false);
      emit_insn (gen_rtx_SET (VOIDmode, dest, x));
    }
  else
    {
      op_true = force_reg (mode, op_true);
      op_false = force_reg (mode, op_false);

      t2 = gen_reg_rtx (mode);
      if (optimize)
	t3 = gen_reg_rtx (mode);
      else
	t3 = dest;

      x = gen_rtx_AND (mode, op_true, cmp);
      emit_insn (gen_rtx_SET (VOIDmode, t2, x));

      x = gen_rtx_NOT (mode, cmp);
      x = gen_rtx_AND (mode, x, op_false);
      emit_insn (gen_rtx_SET (VOIDmode, t3, x));

      x = gen_rtx_IOR (mode, t3, t2);
      emit_insn (gen_rtx_SET (VOIDmode, dest, x));
    }
}