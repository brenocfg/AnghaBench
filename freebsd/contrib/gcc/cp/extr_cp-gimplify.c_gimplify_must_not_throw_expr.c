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
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_to_statement_list (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  build_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gimple_build_eh_filter (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_stmt (scalar_t__*) ; 
 int /*<<< orphan*/  terminate_node ; 
 scalar_t__ voidify_wrapper_expr (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gimplify_must_not_throw_expr (tree *expr_p, tree *pre_p)
{
  tree stmt = *expr_p;
  tree temp = voidify_wrapper_expr (stmt, NULL);
  tree body = TREE_OPERAND (stmt, 0);

  gimplify_stmt (&body);

  stmt = gimple_build_eh_filter (body, NULL_TREE,
				 build_call (terminate_node, NULL_TREE));

  if (temp)
    {
      append_to_statement_list (stmt, pre_p);
      *expr_p = temp;
    }
  else
    *expr_p = stmt;
}