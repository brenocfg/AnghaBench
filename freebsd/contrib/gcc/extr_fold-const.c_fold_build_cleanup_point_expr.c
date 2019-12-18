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
 int /*<<< orphan*/  CLEANUP_POINT_EXPR ; 
 scalar_t__ RETURN_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

tree
fold_build_cleanup_point_expr (tree type, tree expr)
{
  /* If the expression does not have side effects then we don't have to wrap
     it with a cleanup point expression.  */
  if (!TREE_SIDE_EFFECTS (expr))
    return expr;

  /* If the expression is a return, check to see if the expression inside the
     return has no side effects or the right hand side of the modify expression
     inside the return. If either don't have side effects set we don't need to
     wrap the expression in a cleanup point expression.  Note we don't check the
     left hand side of the modify because it should always be a return decl.  */
  if (TREE_CODE (expr) == RETURN_EXPR)
    {
      tree op = TREE_OPERAND (expr, 0);
      if (!op || !TREE_SIDE_EFFECTS (op))
        return expr;
      op = TREE_OPERAND (op, 1);
      if (!TREE_SIDE_EFFECTS (op))
        return expr;
    }
  
  return build1 (CLEANUP_POINT_EXPR, type, expr);
}