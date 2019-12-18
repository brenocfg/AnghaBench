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
typedef  scalar_t__ tree ;

/* Variables and functions */
 int /*<<< orphan*/  TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ fold_indirect_ref_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_indirect_ref (tree t)
{
  tree sub = fold_indirect_ref_1 (TREE_TYPE (t), TREE_OPERAND (t, 0));

  if (sub)
    return sub;
  else
    return t;
}