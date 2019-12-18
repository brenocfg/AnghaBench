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
 scalar_t__ ARRAY_TYPE ; 
 int /*<<< orphan*/  COMPLETE_OR_VOID_TYPE_P (scalar_t__) ; 
 scalar_t__ CONSTANT_CLASS_P (scalar_t__) ; 
 scalar_t__ DECL_P (scalar_t__) ; 
 scalar_t__ EXPR_P (scalar_t__) ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  SET_EXPR_LOCATION (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATEMENT_LIST_STMT_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cur_stmt_list ; 
 int /*<<< orphan*/  emit_side_effect_warnings (scalar_t__) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ extra_warnings ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  verify_sequence_points (scalar_t__) ; 
 scalar_t__ warn_sequence_point ; 
 scalar_t__ warn_unused_value ; 

tree
c_process_expr_stmt (tree expr)
{
  if (!expr)
    return NULL_TREE;

  if (warn_sequence_point)
    verify_sequence_points (expr);

  if (TREE_TYPE (expr) != error_mark_node
      && !COMPLETE_OR_VOID_TYPE_P (TREE_TYPE (expr))
      && TREE_CODE (TREE_TYPE (expr)) != ARRAY_TYPE)
    error ("expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  if (!STATEMENT_LIST_STMT_EXPR (cur_stmt_list)
      && (extra_warnings || warn_unused_value))
    emit_side_effect_warnings (expr);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  if (DECL_P (expr) || CONSTANT_CLASS_P (expr))
    expr = build1 (NOP_EXPR, TREE_TYPE (expr), expr);

  if (EXPR_P (expr))
    SET_EXPR_LOCATION (expr, input_location);

  return expr;
}