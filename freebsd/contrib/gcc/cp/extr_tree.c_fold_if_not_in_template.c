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
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ UNARY_PLUS_EXPR ; 
 int /*<<< orphan*/  fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ processing_template_decl ; 

tree
fold_if_not_in_template (tree expr)
{
  /* In the body of a template, there is never any need to call
     "fold".  We will call fold later when actually instantiating the
     template.  Integral constant expressions in templates will be
     evaluated via fold_non_dependent_expr, as necessary.  */
  if (processing_template_decl)
    return expr;

  /* Fold C++ front-end specific tree codes.  */
  if (TREE_CODE (expr) == UNARY_PLUS_EXPR)
    return fold_convert (TREE_TYPE (expr), TREE_OPERAND (expr, 0));

  return fold (expr);
}