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
 scalar_t__ INTEGER_CST ; 
 int MINUS_EXPR ; 
 int /*<<< orphan*/  NEGATE_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int PLUS_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool 
analyze_offset (tree offset, tree *invariant, tree *constant)
{
  tree op0, op1, constant_0, constant_1, invariant_0, invariant_1;
  enum tree_code code = TREE_CODE (offset);

  *invariant = NULL_TREE;
  *constant = NULL_TREE;

  /* Not PLUS/MINUS expression - recursion stop condition.  */
  if (code != PLUS_EXPR && code != MINUS_EXPR)
    {
      if (TREE_CODE (offset) == INTEGER_CST)
	*constant = offset;
      else
	*invariant = offset;
      return true;
    }

  op0 = TREE_OPERAND (offset, 0);
  op1 = TREE_OPERAND (offset, 1);

  /* Recursive call with the operands.  */
  if (!analyze_offset (op0, &invariant_0, &constant_0)
      || !analyze_offset (op1, &invariant_1, &constant_1))
    return false;

  /* Combine the results. Add negation to the subtrahend in case of
     subtraction.  */
  if (constant_0 && constant_1)
    return false;
  *constant = constant_0 ? constant_0 : constant_1;
  if (code == MINUS_EXPR && constant_1)
    *constant = fold_build1 (NEGATE_EXPR, TREE_TYPE (*constant), *constant);

  if (invariant_0 && invariant_1)
    *invariant = 
      fold_build2 (code, TREE_TYPE (invariant_0), invariant_0, invariant_1);
  else
    {
      *invariant = invariant_0 ? invariant_0 : invariant_1;
      if (code == MINUS_EXPR && invariant_1)
        *invariant = 
           fold_build1 (NEGATE_EXPR, TREE_TYPE (*invariant), *invariant);
    }
  return true;
}