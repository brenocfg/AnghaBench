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
 int /*<<< orphan*/  AND ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  OPTAB_LIB_WIDEN ; 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  and_optab ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ simplify_binary_operation (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 

rtx
expand_and (enum machine_mode mode, rtx op0, rtx op1, rtx target)
{
  rtx tem = 0;

  if (GET_MODE (op0) == VOIDmode && GET_MODE (op1) == VOIDmode)
    tem = simplify_binary_operation (AND, mode, op0, op1);
  if (tem == 0)
    tem = expand_binop (mode, and_optab, op0, op1, target, 0, OPTAB_LIB_WIDEN);

  if (target == 0)
    target = tem;
  else if (tem != target)
    emit_move_insn (target, tem);
  return target;
}