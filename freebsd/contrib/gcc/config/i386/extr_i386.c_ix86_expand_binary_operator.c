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
 int /*<<< orphan*/  CCmode ; 
 int /*<<< orphan*/  FLAGS_REG ; 
 int PLUS ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ ix86_fixup_binary_operands (int,int,scalar_t__*) ; 
 scalar_t__ reload_in_progress ; 

void
ix86_expand_binary_operator (enum rtx_code code, enum machine_mode mode,
			     rtx operands[])
{
  rtx src1, src2, dst, op, clob;

  dst = ix86_fixup_binary_operands (code, mode, operands);
  src1 = operands[1];
  src2 = operands[2];

 /* Emit the instruction.  */

  op = gen_rtx_SET (VOIDmode, dst, gen_rtx_fmt_ee (code, mode, src1, src2));
  if (reload_in_progress)
    {
      /* Reload doesn't know about the flags register, and doesn't know that
         it doesn't want to clobber it.  We can only do this with PLUS.  */
      gcc_assert (code == PLUS);
      emit_insn (op);
    }
  else
    {
      clob = gen_rtx_CLOBBER (VOIDmode, gen_rtx_REG (CCmode, FLAGS_REG));
      emit_insn (gen_rtx_PARALLEL (VOIDmode, gen_rtvec (2, op, clob)));
    }

  /* Fix up the destination if needed.  */
  if (dst != operands[0])
    emit_move_insn (operands[0], dst);
}