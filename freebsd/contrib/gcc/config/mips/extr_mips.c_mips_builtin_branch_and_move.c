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

/* Variables and functions */
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_condjump (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_jump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_label_rtx () ; 

__attribute__((used)) static rtx
mips_builtin_branch_and_move (rtx condition, rtx target,
			      rtx value_if_true, rtx value_if_false)
{
  rtx true_label, done_label;

  true_label = gen_label_rtx ();
  done_label = gen_label_rtx ();

  /* First assume that CONDITION is false.  */
  emit_move_insn (target, value_if_false);

  /* Branch to TRUE_LABEL if CONDITION is true and DONE_LABEL otherwise.  */
  emit_jump_insn (gen_condjump (condition, true_label));
  emit_jump_insn (gen_jump (done_label));
  emit_barrier ();

  /* Fix TARGET if CONDITION is true.  */
  emit_label (true_label);
  emit_move_insn (target, value_if_true);

  emit_label (done_label);
  return target;
}