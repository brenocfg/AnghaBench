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
 scalar_t__ INTEGER_CST ; 
 scalar_t__ SUBSTITUTE_PLACEHOLDER_IN_EXPR (scalar_t__,scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_SIZE_UNIT (scalar_t__) ; 
 scalar_t__ WITH_SIZE_EXPR ; 
 scalar_t__ build2 (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ unshare_expr (scalar_t__) ; 

__attribute__((used)) static void
maybe_with_size_expr (tree *expr_p)
{
  tree expr = *expr_p;
  tree type = TREE_TYPE (expr);
  tree size;

  /* If we've already wrapped this or the type is error_mark_node, we can't do
     anything.  */
  if (TREE_CODE (expr) == WITH_SIZE_EXPR
      || type == error_mark_node)
    return;

  /* If the size isn't known or is a constant, we have nothing to do.  */
  size = TYPE_SIZE_UNIT (type);
  if (!size || TREE_CODE (size) == INTEGER_CST)
    return;

  /* Otherwise, make a WITH_SIZE_EXPR.  */
  size = unshare_expr (size);
  size = SUBSTITUTE_PLACEHOLDER_IN_EXPR (size, expr);
  *expr_p = build2 (WITH_SIZE_EXPR, type, expr, size);
}