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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int MINUS_EXPR ; 
 int PLUS_EXPR ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 scalar_t__ chrec_convert (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_fold_minus (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ chrec_fold_plus (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_used_pointer_cast (scalar_t__) ; 
 scalar_t__ pointer_offset_p (scalar_t__) ; 

__attribute__((used)) static tree
fold_used_pointer (tree expr, tree at_stmt)
{
  tree op0, op1, new0, new1;
  enum tree_code code = TREE_CODE (expr);

  if (code == PLUS_EXPR
      || code == MINUS_EXPR)
    {
      op0 = TREE_OPERAND (expr, 0);
      op1 = TREE_OPERAND (expr, 1);

      if (pointer_offset_p (op1))
	{
	  new0 = fold_used_pointer (op0, at_stmt);
	  new1 = fold_used_pointer_cast (op1);
	}
      else if (code == PLUS_EXPR && pointer_offset_p (op0))
	{
	  new0 = fold_used_pointer_cast (op0);
	  new1 = fold_used_pointer (op1, at_stmt);
	}
      else
	return expr;

      if (new0 == op0 && new1 == op1)
	return expr;

      new0 = chrec_convert (TREE_TYPE (expr), new0, at_stmt);
      new1 = chrec_convert (TREE_TYPE (expr), new1, at_stmt);

      if (code == PLUS_EXPR)
	expr = chrec_fold_plus (TREE_TYPE (expr), new0, new1);
      else
	expr = chrec_fold_minus (TREE_TYPE (expr), new0, new1);

      return expr;
    }
  else
    return fold_used_pointer_cast (expr);
}