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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ NEGATE_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_function_call_expr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_real (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_tree_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dconst1 ; 
 scalar_t__ real_zerop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
fold_builtin_cos (tree arglist, tree type, tree fndecl)
{
  tree arg = TREE_VALUE (arglist);

  if (!validate_arglist (arglist, REAL_TYPE, VOID_TYPE))
    return NULL_TREE;

  /* Optimize cos (0.0) = 1.0.  */
  if (real_zerop (arg))
    return build_real (type, dconst1);

  /* Optimize cos(-x) into cos (x).  */
  if (TREE_CODE (arg) == NEGATE_EXPR)
    {
      tree args = build_tree_list (NULL_TREE,
				   TREE_OPERAND (arg, 0));
      return build_function_call_expr (fndecl, args);
    }

  return NULL_TREE;
}