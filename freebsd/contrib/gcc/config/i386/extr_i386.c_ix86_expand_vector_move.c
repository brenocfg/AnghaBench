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
 scalar_t__ CONSTANT_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_const_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  no_new_pseudos ; 
 scalar_t__ register_operand (int /*<<< orphan*/ ,int) ; 
 int reload_completed ; 
 int reload_in_progress ; 
 scalar_t__ standard_sse_constant_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validize_mem (int /*<<< orphan*/ ) ; 

void
ix86_expand_vector_move (enum machine_mode mode, rtx operands[])
{
  rtx op0 = operands[0], op1 = operands[1];

  /* Force constants other than zero into memory.  We do not know how
     the instructions used to build constants modify the upper 64 bits
     of the register, once we have that information we may be able
     to handle some of them more efficiently.  */
  if ((reload_in_progress | reload_completed) == 0
      && register_operand (op0, mode)
      && CONSTANT_P (op1)
      && standard_sse_constant_p (op1) <= 0)
    op1 = validize_mem (force_const_mem (mode, op1));

  /* Make operand1 a register if it isn't already.  */
  if (!no_new_pseudos
      && !register_operand (op0, mode)
      && !register_operand (op1, mode))
    {
      emit_move_insn (op0, force_reg (GET_MODE (op0), op1));
      return;
    }

  emit_insn (gen_rtx_SET (VOIDmode, op0, op1));
}