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
 int MAX_EXPR ; 
 int MIN_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  omit_one_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ reorder_operands_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_minmax (enum tree_code code, tree type, tree op0, tree op1)
{
  enum tree_code compl_code;

  if (code == MIN_EXPR)
    compl_code = MAX_EXPR;
  else if (code == MAX_EXPR)
    compl_code = MIN_EXPR;
  else
    gcc_unreachable ();

  /* MIN (MAX (a, b), b) == b.  */
  if (TREE_CODE (op0) == compl_code
      && operand_equal_p (TREE_OPERAND (op0, 1), op1, 0))
    return omit_one_operand (type, op1, TREE_OPERAND (op0, 0));

  /* MIN (MAX (b, a), b) == b.  */
  if (TREE_CODE (op0) == compl_code
      && operand_equal_p (TREE_OPERAND (op0, 0), op1, 0)
      && reorder_operands_p (TREE_OPERAND (op0, 1), op1))
    return omit_one_operand (type, op1, TREE_OPERAND (op0, 1));

  /* MIN (a, MAX (a, b)) == a.  */
  if (TREE_CODE (op1) == compl_code
      && operand_equal_p (op0, TREE_OPERAND (op1, 0), 0)
      && reorder_operands_p (op0, TREE_OPERAND (op1, 1)))
    return omit_one_operand (type, op0, TREE_OPERAND (op1, 1));

  /* MIN (a, MAX (b, a)) == a.  */
  if (TREE_CODE (op1) == compl_code
      && operand_equal_p (op0, TREE_OPERAND (op1, 1), 0)
      && reorder_operands_p (op0, TREE_OPERAND (op1, 0)))
    return omit_one_operand (type, op0, TREE_OPERAND (op1, 0));

  return NULL_TREE;
}