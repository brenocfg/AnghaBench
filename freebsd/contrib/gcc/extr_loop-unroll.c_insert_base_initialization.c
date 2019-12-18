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
struct iv_to_split {int /*<<< orphan*/  base_var; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  copy_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  force_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/ * get_ivts_expr (int /*<<< orphan*/ ,struct iv_to_split*) ; 
 int /*<<< orphan*/  single_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_sequence () ; 

__attribute__((used)) static void
insert_base_initialization (struct iv_to_split *ivts, rtx insn)
{
  rtx expr = copy_rtx (*get_ivts_expr (single_set (insn), ivts));
  rtx seq;

  start_sequence ();
  expr = force_operand (expr, ivts->base_var);
  if (expr != ivts->base_var)
    emit_move_insn (ivts->base_var, expr);
  seq = get_insns ();
  end_sequence ();

  emit_insn_before (seq, insn);
}