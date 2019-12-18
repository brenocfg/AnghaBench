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
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ REG ; 
 scalar_t__ SUBREG ; 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
 scalar_t__ TImode ; 
 int /*<<< orphan*/  adjust_address (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assign_stack_temp (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
spill_xfmode_rfmode_operand (rtx in, int force, enum machine_mode mode)
{
  if (GET_CODE (in) == SUBREG
      && GET_MODE (SUBREG_REG (in)) == TImode
      && GET_CODE (SUBREG_REG (in)) == REG)
    {
      rtx memt = assign_stack_temp (TImode, 16, 0);
      emit_move_insn (memt, SUBREG_REG (in));
      return adjust_address (memt, mode, 0);
    }
  else if (force && GET_CODE (in) == REG)
    {
      rtx memx = assign_stack_temp (mode, 16, 0);
      emit_move_insn (memx, in);
      return memx;
    }
  else
    return in;
}