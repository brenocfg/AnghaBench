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
 int /*<<< orphan*/  GEN_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 int /*<<< orphan*/  PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_simple_binop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_MEM (int,scalar_t__) ; 
 scalar_t__ stack_pointer_rtx ; 

void
ix86_expand_push (enum machine_mode mode, rtx x)
{
  rtx tmp;

  tmp = expand_simple_binop (Pmode, PLUS, stack_pointer_rtx,
			     GEN_INT (-GET_MODE_SIZE (mode)),
			     stack_pointer_rtx, 1, OPTAB_DIRECT);
  if (tmp != stack_pointer_rtx)
    emit_move_insn (stack_pointer_rtx, tmp);

  tmp = gen_rtx_MEM (mode, stack_pointer_rtx);
  emit_move_insn (tmp, x);
}