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
 int COND_EXPR ; 
 scalar_t__ EQ_EXPR ; 
 int INTEGER_CST ; 
 scalar_t__ NE_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 int TRUTH_AND_EXPR ; 
 int TRUTH_OR_EXPR ; 
 scalar_t__ boolean_true_node ; 
 int /*<<< orphan*/  boolean_type_node ; 
 scalar_t__ expand_simple_operations (scalar_t__) ; 
 scalar_t__ fold_binary (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build2 (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build3 (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ invert_truthvalue (scalar_t__) ; 
 scalar_t__ nonzero_p (scalar_t__) ; 
 scalar_t__ simplify_replace_tree (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ zero_p (scalar_t__) ; 

__attribute__((used)) static tree
tree_simplify_using_condition_1 (tree cond, tree expr)
{
  bool changed;
  tree e, te, e0, e1, e2, notcond;
  enum tree_code code = TREE_CODE (expr);

  if (code == INTEGER_CST)
    return expr;

  if (code == TRUTH_OR_EXPR
      || code == TRUTH_AND_EXPR
      || code == COND_EXPR)
    {
      changed = false;

      e0 = tree_simplify_using_condition_1 (cond, TREE_OPERAND (expr, 0));
      if (TREE_OPERAND (expr, 0) != e0)
	changed = true;

      e1 = tree_simplify_using_condition_1 (cond, TREE_OPERAND (expr, 1));
      if (TREE_OPERAND (expr, 1) != e1)
	changed = true;

      if (code == COND_EXPR)
	{
	  e2 = tree_simplify_using_condition_1 (cond, TREE_OPERAND (expr, 2));
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

  /* In case COND is equality, we may be able to simplify EXPR by copy/constant
     propagation, and vice versa.  Fold does not handle this, since it is
     considered too expensive.  */
  if (TREE_CODE (cond) == EQ_EXPR)
    {
      e0 = TREE_OPERAND (cond, 0);
      e1 = TREE_OPERAND (cond, 1);

      /* We know that e0 == e1.  Check whether we cannot simplify expr
	 using this fact.  */
      e = simplify_replace_tree (expr, e0, e1);
      if (zero_p (e) || nonzero_p (e))
	return e;

      e = simplify_replace_tree (expr, e1, e0);
      if (zero_p (e) || nonzero_p (e))
	return e;
    }
  if (TREE_CODE (expr) == EQ_EXPR)
    {
      e0 = TREE_OPERAND (expr, 0);
      e1 = TREE_OPERAND (expr, 1);

      /* If e0 == e1 (EXPR) implies !COND, then EXPR cannot be true.  */
      e = simplify_replace_tree (cond, e0, e1);
      if (zero_p (e))
	return e;
      e = simplify_replace_tree (cond, e1, e0);
      if (zero_p (e))
	return e;
    }
  if (TREE_CODE (expr) == NE_EXPR)
    {
      e0 = TREE_OPERAND (expr, 0);
      e1 = TREE_OPERAND (expr, 1);

      /* If e0 == e1 (!EXPR) implies !COND, then EXPR must be true.  */
      e = simplify_replace_tree (cond, e0, e1);
      if (zero_p (e))
	return boolean_true_node;
      e = simplify_replace_tree (cond, e1, e0);
      if (zero_p (e))
	return boolean_true_node;
    }

  te = expand_simple_operations (expr);

  /* Check whether COND ==> EXPR.  */
  notcond = invert_truthvalue (cond);
  e = fold_binary (TRUTH_OR_EXPR, boolean_type_node, notcond, te);
  if (nonzero_p (e))
    return e;

  /* Check whether COND ==> not EXPR.  */
  e = fold_binary (TRUTH_AND_EXPR, boolean_type_node, cond, te);
  if (e && zero_p (e))
    return e;

  return expr;
}