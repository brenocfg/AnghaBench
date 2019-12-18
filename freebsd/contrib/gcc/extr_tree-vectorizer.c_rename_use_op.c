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
typedef  int /*<<< orphan*/  use_operand_p ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  SET_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE_FROM_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_current_def (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rename_use_op (use_operand_p op_p)
{
  tree new_name;

  if (TREE_CODE (USE_FROM_PTR (op_p)) != SSA_NAME)
    return;

  new_name = get_current_def (USE_FROM_PTR (op_p));

  /* Something defined outside of the loop.  */
  if (!new_name)
    return;

  /* An ordinary ssa name defined in the loop.  */

  SET_USE (op_p, new_name);
}