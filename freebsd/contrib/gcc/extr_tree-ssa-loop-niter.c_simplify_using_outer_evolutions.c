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
struct loop {int dummy; } ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int COND_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int TRUTH_AND_EXPR ; 
 int TRUTH_OR_EXPR ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ fold_build2 (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build3 (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ instantiate_parameters (struct loop*,scalar_t__) ; 
 scalar_t__ is_gimple_min_invariant (scalar_t__) ; 

__attribute__((used)) static tree
simplify_using_outer_evolutions (struct loop *loop, tree expr)
{
  enum tree_code code = TREE_CODE (expr);
  bool changed;
  tree e, e0, e1, e2;

  if (is_gimple_min_invariant (expr))
    return expr;

  if (code == TRUTH_OR_EXPR
      || code == TRUTH_AND_EXPR
      || code == COND_EXPR)
    {
      changed = false;

      e0 = simplify_using_outer_evolutions (loop, TREE_OPERAND (expr, 0));
      if (TREE_OPERAND (expr, 0) != e0)
	changed = true;

      e1 = simplify_using_outer_evolutions (loop, TREE_OPERAND (expr, 1));
      if (TREE_OPERAND (expr, 1) != e1)
	changed = true;

      if (code == COND_EXPR)
	{
	  e2 = simplify_using_outer_evolutions (loop, TREE_OPERAND (expr, 2));
	  if (TREE_OPERAND (expr, 2) != e2)
	    changed = true;
	}
      else
	e2 = NULL_TREE;

      if (changed)
	{
	  if (code == COND_EXPR)
	    expr = fold_build3 (code, boolean_type_node, e0, e1, e2);
	  else
	    expr = fold_build2 (code, boolean_type_node, e0, e1);
	}

      return expr;
    }

  e = instantiate_parameters (loop, expr);
  if (is_gimple_min_invariant (e))
    return e;

  return expr;
}