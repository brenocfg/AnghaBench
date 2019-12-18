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
 scalar_t__ MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  SSA_NAME_DEF_STMT (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static tree
get_unary_op (tree name, enum tree_code opcode)
{
  tree stmt = SSA_NAME_DEF_STMT (name);
  tree rhs;

  if (TREE_CODE (stmt) != MODIFY_EXPR)
    return NULL_TREE;

  rhs = TREE_OPERAND (stmt, 1);
  if (TREE_CODE (rhs) == opcode)
    return TREE_OPERAND (rhs, 0);
  return NULL_TREE;
}