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
 scalar_t__ ERROR_MARK ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TRUTH_NOT_EXPR ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ fold_truth_not_expr (scalar_t__) ; 

tree
invert_truthvalue (tree arg)
{
  tree tem;

  if (TREE_CODE (arg) == ERROR_MARK)
    return arg;

  tem = fold_truth_not_expr (arg);
  if (!tem)
    tem = build1 (TRUTH_NOT_EXPR, TREE_TYPE (arg), arg);

  return tem;
}