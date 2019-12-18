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
struct expr {int /*<<< orphan*/  expr; int /*<<< orphan*/  reaching_reg; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ general_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 scalar_t__ insn_invalid_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static rtx
process_insert_insn (struct expr *expr)
{
  rtx reg = expr->reaching_reg;
  rtx exp = copy_rtx (expr->expr);
  rtx pat;

  start_sequence ();

  /* If the expression is something that's an operand, like a constant,
     just copy it to a register.  */
  if (general_operand (exp, GET_MODE (reg)))
    emit_move_insn (reg, exp);

  /* Otherwise, make a new insn to compute this expression and make sure the
     insn will be recognized (this also adds any needed CLOBBERs).  Copy the
     expression to make sure we don't have any sharing issues.  */
  else
    {
      rtx insn = emit_insn (gen_rtx_SET (VOIDmode, reg, exp));

      if (insn_invalid_p (insn))
	gcc_unreachable ();
    }
  

  pat = get_insns ();
  end_sequence ();

  return pat;
}