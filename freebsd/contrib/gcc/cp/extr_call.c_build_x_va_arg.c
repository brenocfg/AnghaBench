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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  VA_ARG_EXPR ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ build_indirect_ref (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ build_min (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  build_pointer_type (scalar_t__) ; 
 scalar_t__ build_va_arg (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  call_builtin_trap () ; 
 scalar_t__ complete_type_or_else (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ non_reference (scalar_t__) ; 
 int /*<<< orphan*/  null_node ; 
 int /*<<< orphan*/  pod_type_p (scalar_t__) ; 
 scalar_t__ processing_template_decl ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

tree
build_x_va_arg (tree expr, tree type)
{
  if (processing_template_decl)
    return build_min (VA_ARG_EXPR, type, expr);

  type = complete_type_or_else (type, NULL_TREE);

  if (expr == error_mark_node || !type)
    return error_mark_node;

  if (! pod_type_p (type))
    {
      /* Remove reference types so we don't ICE later on.  */
      tree type1 = non_reference (type);
      /* Undefined behavior [expr.call] 5.2.2/7.  */
      warning (0, "cannot receive objects of non-POD type %q#T through %<...%>; "
	       "call will abort at runtime", type);
      expr = convert (build_pointer_type (type1), null_node);
      expr = build2 (COMPOUND_EXPR, TREE_TYPE (expr),
		     call_builtin_trap (), expr);
      expr = build_indirect_ref (expr, NULL);
      return expr;
    }

  return build_va_arg (expr, type);
}