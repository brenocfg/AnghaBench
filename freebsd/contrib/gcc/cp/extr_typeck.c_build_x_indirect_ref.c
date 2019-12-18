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
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ build_indirect_ref (scalar_t__,char const*) ; 
 scalar_t__ build_min_non_dep (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ build_min_nt (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_new_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ build_non_dependent_expr (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ processing_template_decl ; 
 scalar_t__ type_dependent_expression_p (scalar_t__) ; 

tree
build_x_indirect_ref (tree expr, const char *errorstring)
{
  tree orig_expr = expr;
  tree rval;

  if (processing_template_decl)
    {
      if (type_dependent_expression_p (expr))
	return build_min_nt (INDIRECT_REF, expr);
      expr = build_non_dependent_expr (expr);
    }

  rval = build_new_op (INDIRECT_REF, LOOKUP_NORMAL, expr, NULL_TREE,
		       NULL_TREE, /*overloaded_p=*/NULL);
  if (!rval)
    rval = build_indirect_ref (expr, errorstring);

  if (processing_template_decl && rval != error_mark_node)
    return build_min_non_dep (INDIRECT_REF, rval, orig_expr);
  else
    return rval;
}