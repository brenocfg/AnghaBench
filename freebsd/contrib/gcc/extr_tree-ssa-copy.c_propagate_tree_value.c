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

/* Variables and functions */
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  may_propagate_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_alias_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsave_expr_now (int /*<<< orphan*/ ) ; 

void
propagate_tree_value (tree *op_p, tree val)
{
#if defined ENABLE_CHECKING
  gcc_assert (!(TREE_CODE (val) == SSA_NAME
		&& TREE_CODE (*op_p) == SSA_NAME
		&& !may_propagate_copy (*op_p, val)));
#endif

  if (TREE_CODE (val) == SSA_NAME)
    {
      if (TREE_CODE (*op_p) == SSA_NAME && POINTER_TYPE_P (TREE_TYPE (*op_p)))
	merge_alias_info (*op_p, val);
      *op_p = val;
    }
  else
    *op_p = unsave_expr_now (val);
}