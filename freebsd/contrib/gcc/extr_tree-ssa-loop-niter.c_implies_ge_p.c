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
 int /*<<< orphan*/  boolean_type_node ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nonzero_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_simplify_using_condition_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
implies_ge_p (tree cond, tree a, tree b)
{
  tree compare = fold_build2 (GE_EXPR, boolean_type_node, a, b);

  if (nonzero_p (compare))
    return true;

  if (nonzero_p (cond))
    return false;

  compare = tree_simplify_using_condition_1 (cond, compare);

  return nonzero_p (compare);
}