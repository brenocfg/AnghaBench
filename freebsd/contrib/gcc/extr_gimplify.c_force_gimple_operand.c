#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  scalar_t__ (* gimple_predicate ) (scalar_t__) ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;
struct TYPE_2__ {scalar_t__ temps; int /*<<< orphan*/  into_ssa; } ;

/* Variables and functions */
 int GS_ERROR ; 
 int /*<<< orphan*/  MODIFY_EXPR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  add_referenced_var (scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  fb_rvalue ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_1__* gimplify_ctxp ; 
 int gimplify_expr (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *,scalar_t__ (*) (scalar_t__),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_ssa_p ; 
 scalar_t__ is_gimple_reg_rhs (scalar_t__) ; 
 scalar_t__ is_gimple_val (scalar_t__) ; 
 int /*<<< orphan*/  pop_gimplify_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_gimplify_context () ; 
 scalar_t__ referenced_vars ; 

tree
force_gimple_operand (tree expr, tree *stmts, bool simple, tree var)
{
  tree t;
  enum gimplify_status ret;
  gimple_predicate gimple_test_f;

  *stmts = NULL_TREE;

  if (is_gimple_val (expr))
    return expr;

  gimple_test_f = simple ? is_gimple_val : is_gimple_reg_rhs;

  push_gimplify_context ();
  gimplify_ctxp->into_ssa = in_ssa_p;

  if (var)
    expr = build2 (MODIFY_EXPR, TREE_TYPE (var), var, expr);

  ret = gimplify_expr (&expr, stmts, NULL,
		       gimple_test_f, fb_rvalue);
  gcc_assert (ret != GS_ERROR);

  if (referenced_vars)
    {
      for (t = gimplify_ctxp->temps; t ; t = TREE_CHAIN (t))
	add_referenced_var (t);
    }

  pop_gimplify_context (NULL);

  return expr;
}