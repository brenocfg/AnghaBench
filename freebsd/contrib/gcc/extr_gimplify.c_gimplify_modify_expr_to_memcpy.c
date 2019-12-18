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
 size_t BUILT_IN_MEMCPY ; 
 int GS_OK ; 
 int /*<<< orphan*/  INDIRECT_REF ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_fold_addr_expr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_function_call_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** implicit_built_in_decls ; 
 int /*<<< orphan*/ * tree_cons (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum gimplify_status
gimplify_modify_expr_to_memcpy (tree *expr_p, tree size, bool want_value)
{
  tree args, t, to, to_ptr, from;

  to = TREE_OPERAND (*expr_p, 0);
  from = TREE_OPERAND (*expr_p, 1);

  args = tree_cons (NULL, size, NULL);

  t = build_fold_addr_expr (from);
  args = tree_cons (NULL, t, args);

  to_ptr = build_fold_addr_expr (to);
  args = tree_cons (NULL, to_ptr, args);
  t = implicit_built_in_decls[BUILT_IN_MEMCPY];
  t = build_function_call_expr (t, args);

  if (want_value)
    {
      t = build1 (NOP_EXPR, TREE_TYPE (to_ptr), t);
      t = build1 (INDIRECT_REF, TREE_TYPE (to), t);
    }

  *expr_p = t;
  return GS_OK;
}