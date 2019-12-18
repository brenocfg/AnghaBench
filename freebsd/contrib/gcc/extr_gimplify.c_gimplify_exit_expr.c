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
typedef  int /*<<< orphan*/  tree ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;
struct TYPE_2__ {int /*<<< orphan*/  exit_label; } ;

/* Variables and functions */
 int /*<<< orphan*/  COND_EXPR ; 
 int GS_OK ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_and_jump (int /*<<< orphan*/ *) ; 
 TYPE_1__* gimplify_ctxp ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static enum gimplify_status
gimplify_exit_expr (tree *expr_p)
{
  tree cond = TREE_OPERAND (*expr_p, 0);
  tree expr;

  expr = build_and_jump (&gimplify_ctxp->exit_label);
  expr = build3 (COND_EXPR, void_type_node, cond, expr, NULL_TREE);
  *expr_p = expr;

  return GS_OK;
}