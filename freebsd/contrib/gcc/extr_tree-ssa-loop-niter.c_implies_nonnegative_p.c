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
 int /*<<< orphan*/  GE_EXPR ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nonzero_p (int /*<<< orphan*/ ) ; 
 scalar_t__ tree_expr_nonnegative_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_simplify_using_condition_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
implies_nonnegative_p (tree cond, tree val)
{
  tree type = TREE_TYPE (val);
  tree compare;

  if (tree_expr_nonnegative_p (val))
    return true;

  if (nonzero_p (cond))
    return false;

  compare = fold_build2 (GE_EXPR,
			 boolean_type_node, val, build_int_cst (type, 0));
  compare = tree_simplify_using_condition_1 (cond, compare);

  return nonzero_p (compare);
}