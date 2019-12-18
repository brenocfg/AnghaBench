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
typedef  int /*<<< orphan*/ * tree ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;

/* Variables and functions */
 size_t BUILT_IN_MEMCMP ; 
 int GS_OK ; 
 int /*<<< orphan*/ * SUBSTITUTE_PLACEHOLDER_IN_EXPR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * build_fold_addr_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_function_call_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** implicit_built_in_decls ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * unshare_expr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum gimplify_status
gimplify_variable_sized_compare (tree *expr_p)
{
  tree op0 = TREE_OPERAND (*expr_p, 0);
  tree op1 = TREE_OPERAND (*expr_p, 1);
  tree args, t, dest;

  t = TYPE_SIZE_UNIT (TREE_TYPE (op0));
  t = unshare_expr (t);
  t = SUBSTITUTE_PLACEHOLDER_IN_EXPR (t, op0);
  args = tree_cons (NULL, t, NULL);
  t = build_fold_addr_expr (op1);
  args = tree_cons (NULL, t, args);
  dest = build_fold_addr_expr (op0);
  args = tree_cons (NULL, dest, args);
  t = implicit_built_in_decls[BUILT_IN_MEMCMP];
  t = build_function_call_expr (t, args);
  *expr_p
    = build2 (TREE_CODE (*expr_p), TREE_TYPE (*expr_p), t, integer_zero_node);

  return GS_OK;
}