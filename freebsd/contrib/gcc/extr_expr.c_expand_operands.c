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
typedef  scalar_t__ rtx ;
typedef  enum expand_modifier { ____Placeholder_expand_modifier } expand_modifier ;

/* Variables and functions */
 scalar_t__ NULL_RTX ; 
 scalar_t__ TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ copy_rtx (scalar_t__) ; 
 scalar_t__ expand_expr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ flag_evaluation_order ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_from_p (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
expand_operands (tree exp0, tree exp1, rtx target, rtx *op0, rtx *op1,
		 enum expand_modifier modifier)
{
  if (! safe_from_p (target, exp1, 1))
    target = 0;
  if (operand_equal_p (exp0, exp1, 0))
    {
      *op0 = expand_expr (exp0, target, VOIDmode, modifier);
      *op1 = copy_rtx (*op0);
    }
  else
    {
      /* If we need to preserve evaluation order, copy exp0 into its own
	 temporary variable so that it can't be clobbered by exp1.  */
      if (flag_evaluation_order && TREE_SIDE_EFFECTS (exp1))
	exp0 = save_expr (exp0);
      *op0 = expand_expr (exp0, target, VOIDmode, modifier);
      *op1 = expand_expr (exp1, NULL_RTX, VOIDmode, modifier);
    }
}