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
 scalar_t__ BINARY_CLASS_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NON_LVALUE_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_INVARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 scalar_t__ UNARY_CLASS_P (int /*<<< orphan*/ ) ; 

tree
skip_simple_arithmetic (tree expr)
{
  tree inner;

  /* We don't care about whether this can be used as an lvalue in this
     context.  */
  while (TREE_CODE (expr) == NON_LVALUE_EXPR)
    expr = TREE_OPERAND (expr, 0);

  /* If we have simple operations applied to a SAVE_EXPR or to a SAVE_EXPR and
     a constant, it will be more efficient to not make another SAVE_EXPR since
     it will allow better simplification and GCSE will be able to merge the
     computations if they actually occur.  */
  inner = expr;
  while (1)
    {
      if (UNARY_CLASS_P (inner))
	inner = TREE_OPERAND (inner, 0);
      else if (BINARY_CLASS_P (inner))
	{
	  if (TREE_INVARIANT (TREE_OPERAND (inner, 1)))
	    inner = TREE_OPERAND (inner, 0);
	  else if (TREE_INVARIANT (TREE_OPERAND (inner, 0)))
	    inner = TREE_OPERAND (inner, 1);
	  else
	    break;
	}
      else
	break;
    }

  return inner;
}