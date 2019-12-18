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
 scalar_t__ COMPOUND_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  non_lvalue (int /*<<< orphan*/ ) ; 

tree
omit_two_operands (tree type, tree result, tree omitted1, tree omitted2)
{
  tree t = fold_convert (type, result);

  if (TREE_SIDE_EFFECTS (omitted2))
    t = build2 (COMPOUND_EXPR, type, omitted2, t);
  if (TREE_SIDE_EFFECTS (omitted1))
    t = build2 (COMPOUND_EXPR, type, omitted1, t);

  return TREE_CODE (t) != COMPOUND_EXPR ? non_lvalue (t) : t;
}