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
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ build_compound_expr (scalar_t__,scalar_t__) ; 
 scalar_t__ build_min_non_dep (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_min_nt (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_new_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ build_non_dependent_expr (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ type_dependent_expression_p (scalar_t__) ; 

tree
build_x_compound_expr (tree op1, tree op2)
{
  tree result;
  tree orig_op1 = op1;
  tree orig_op2 = op2;

  if (processing_template_decl)
    {
      if (type_dependent_expression_p (op1)
	  || type_dependent_expression_p (op2))
	return build_min_nt (COMPOUND_EXPR, op1, op2);
      op1 = build_non_dependent_expr (op1);
      op2 = build_non_dependent_expr (op2);
    }

  result = build_new_op (COMPOUND_EXPR, LOOKUP_NORMAL, op1, op2, NULL_TREE,
			 /*overloaded_p=*/NULL);
  if (!result)
    result = build_compound_expr (op1, op2);

  if (processing_template_decl && result != error_mark_node)
    return build_min_non_dep (COMPOUND_EXPR, result, orig_op1, orig_op2);

  return result;
}