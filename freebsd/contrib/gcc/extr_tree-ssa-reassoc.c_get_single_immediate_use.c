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
typedef  int /*<<< orphan*/  use_operand_p ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ MODIFY_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ RETURN_EXPR ; 
 scalar_t__ SSA_NAME ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ single_imm_use (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
get_single_immediate_use (tree lhs)
{
  use_operand_p immuse;
  tree immusestmt;

  if (TREE_CODE (lhs) == SSA_NAME
      && single_imm_use (lhs, &immuse, &immusestmt))
    {
      if (TREE_CODE (immusestmt) == RETURN_EXPR)
	immusestmt = TREE_OPERAND (immusestmt, 0);
      if (TREE_CODE (immusestmt) == MODIFY_EXPR)
	return immusestmt;
    }
  return NULL_TREE;
}