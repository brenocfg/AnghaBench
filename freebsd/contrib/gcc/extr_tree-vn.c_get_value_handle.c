#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* tree_ann_common_t ;
typedef  int /*<<< orphan*/  tree ;
struct TYPE_3__ {int /*<<< orphan*/  value_handle; } ;

/* Variables and functions */
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ EXPR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ SSA_NAME ; 
 int /*<<< orphan*/  SSA_NAME_VALUE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_LIST ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ is_gimple_min_invariant (int /*<<< orphan*/ ) ; 
 TYPE_1__* tree_common_ann (int /*<<< orphan*/ ) ; 

tree
get_value_handle (tree expr)
{

  if (is_gimple_min_invariant (expr))
    return expr;

  if (TREE_CODE (expr) == SSA_NAME)
    return SSA_NAME_VALUE (expr);
  else if (EXPR_P (expr) || DECL_P (expr) || TREE_CODE (expr) == TREE_LIST
	   || TREE_CODE (expr) == CONSTRUCTOR)
    {
      tree_ann_common_t ann = tree_common_ann (expr);
      return ((ann) ? ann->value_handle : NULL_TREE);
    }
  else
    gcc_unreachable ();
}