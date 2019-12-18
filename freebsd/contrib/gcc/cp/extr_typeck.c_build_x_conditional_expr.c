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
 int /*<<< orphan*/  COND_EXPR ; 
 scalar_t__ build_conditional_expr (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_min_non_dep (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_min_nt (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_non_dependent_expr (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ type_dependent_expression_p (scalar_t__) ; 

tree
build_x_conditional_expr (tree ifexp, tree op1, tree op2)
{
  tree orig_ifexp = ifexp;
  tree orig_op1 = op1;
  tree orig_op2 = op2;
  tree expr;

  if (processing_template_decl)
    {
      /* The standard says that the expression is type-dependent if
	 IFEXP is type-dependent, even though the eventual type of the
	 expression doesn't dependent on IFEXP.  */
      if (type_dependent_expression_p (ifexp)
	  /* As a GNU extension, the middle operand may be omitted.  */
	  || (op1 && type_dependent_expression_p (op1))
	  || type_dependent_expression_p (op2))
	return build_min_nt (COND_EXPR, ifexp, op1, op2);
      ifexp = build_non_dependent_expr (ifexp);
      if (op1)
	op1 = build_non_dependent_expr (op1);
      op2 = build_non_dependent_expr (op2);
    }

  expr = build_conditional_expr (ifexp, op1, op2);
  if (processing_template_decl && expr != error_mark_node)
    return build_min_non_dep (COND_EXPR, expr,
			      orig_ifexp, orig_op1, orig_op2);
  return expr;
}