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
 int /*<<< orphan*/  EQ ; 
 int GET_MODE_SIZE (int) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int UNITS_PER_WORD ; 
 scalar_t__ const0_rtx ; 
 int /*<<< orphan*/  do_compare_rtx_and_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_jump_by_parts_zero_rtx (int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_jump (scalar_t__) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 scalar_t__ gen_label_rtx () ; 
 int /*<<< orphan*/  operand_subword_force (scalar_t__,int,int) ; 
 int /*<<< orphan*/  word_mode ; 

__attribute__((used)) static void
do_jump_by_parts_equality_rtx (enum machine_mode mode, rtx op0, rtx op1,
			       rtx if_false_label, rtx if_true_label)
{
  int nwords = (GET_MODE_SIZE (mode) / UNITS_PER_WORD);
  rtx drop_through_label = 0;
  int i;

  if (op1 == const0_rtx)
    {
      do_jump_by_parts_zero_rtx (mode, op0, if_false_label, if_true_label);
      return;
    }
  else if (op0 == const0_rtx)
    {
      do_jump_by_parts_zero_rtx (mode, op1, if_false_label, if_true_label);
      return;
    }

  if (! if_false_label)
    drop_through_label = if_false_label = gen_label_rtx ();

  for (i = 0; i < nwords; i++)
    do_compare_rtx_and_jump (operand_subword_force (op0, i, mode),
                             operand_subword_force (op1, i, mode),
                             EQ, 0, word_mode, NULL_RTX,
			     if_false_label, NULL_RTX);

  if (if_true_label)
    emit_jump (if_true_label);
  if (drop_through_label)
    emit_label (drop_through_label);
}