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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  IS_EMPTY_STMT (int /*<<< orphan*/ ) ; 
 scalar_t__ MODIFY_EXPR ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 scalar_t__ has_single_use (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
is_reassociable_op (tree stmt, enum tree_code code)
{
  if (!IS_EMPTY_STMT (stmt)
      && TREE_CODE (stmt) == MODIFY_EXPR
      && TREE_CODE (TREE_OPERAND (stmt, 1)) == code
      && has_single_use (TREE_OPERAND (stmt, 0)))
    return true;
  return false;
}