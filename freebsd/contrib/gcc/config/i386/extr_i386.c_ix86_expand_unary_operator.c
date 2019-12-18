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
 scalar_t__ MEM_P (scalar_t__) ; 
 int NOT ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ force_reg (int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_CLOBBER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_e (int,int,scalar_t__) ; 
 scalar_t__ reload_in_progress ; 
 scalar_t__ rtx_equal_p (scalar_t__,scalar_t__) ; 

void
ix86_expand_unary_operator (enum rtx_code code, enum machine_mode mode,
			    rtx operands[])
{
  int matching_memory;
  rtx src, dst, op, clob;

  dst = operands[0];
  src = operands[1];

  /* If the destination is memory, and we do not have matching source
     operands, do things in registers.  */
  matching_memory = 0;
  if (MEM_P (dst))
    {
      if (rtx_equal_p (dst, src))
	matching_memory = 1;
      else
	dst = gen_reg_rtx (mode);
    }

  /* When source operand is memory, destination must match.  */
  if (MEM_P (src) && !matching_memory)
    src = force_reg (mode, src);

  /* Emit the instruction.  */

  op = gen_rtx_SET (VOIDmode, dst, gen_rtx_fmt_e (code, mode, src));
  if (reload_in_progress || code == NOT)
    {
      /* Reload doesn't know about the flags register, and doesn't know that
         it doesn't want to clobber it.  */
      gcc_assert (code == NOT);
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