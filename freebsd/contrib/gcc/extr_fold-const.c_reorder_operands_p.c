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
 scalar_t__ TREE_CONSTANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flag_evaluation_order ; 

__attribute__((used)) static bool
reorder_operands_p (tree arg0, tree arg1)
{
  if (! flag_evaluation_order)
      return true;
  if (TREE_CONSTANT (arg0) || TREE_CONSTANT (arg1))
    return true;
  return ! TREE_SIDE_EFFECTS (arg0)
	 && ! TREE_SIDE_EFFECTS (arg1);
}