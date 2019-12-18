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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_jump_by_parts_greater_rtx (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_jump_by_parts_greater (tree exp, int swap, rtx if_false_label,
			  rtx if_true_label)
{
  rtx op0 = expand_normal (TREE_OPERAND (exp, swap));
  rtx op1 = expand_normal (TREE_OPERAND (exp, !swap));
  enum machine_mode mode = TYPE_MODE (TREE_TYPE (TREE_OPERAND (exp, 0)));
  int unsignedp = TYPE_UNSIGNED (TREE_TYPE (TREE_OPERAND (exp, 0)));

  do_jump_by_parts_greater_rtx (mode, unsignedp, op0, op1, if_false_label,
				if_true_label);
}