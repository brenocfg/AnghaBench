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
 scalar_t__ BLOCK_SUBBLOCKS (scalar_t__) ; 
 scalar_t__ BLOCK_VARS (scalar_t__) ; 
 scalar_t__ DECL_HAS_VALUE_EXPR_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_RTL (scalar_t__) ; 
 scalar_t__ DECL_RTL_SET_P (scalar_t__) ; 
 scalar_t__ DECL_VALUE_EXPR (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  instantiate_decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_expr ; 
 int /*<<< orphan*/  walk_tree (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
instantiate_decls_1 (tree let)
{
  tree t;

  for (t = BLOCK_VARS (let); t; t = TREE_CHAIN (t))
    {
      if (DECL_RTL_SET_P (t))
	instantiate_decl (DECL_RTL (t));
      if (TREE_CODE (t) == VAR_DECL && DECL_HAS_VALUE_EXPR_P (t))
	{
	  tree v = DECL_VALUE_EXPR (t);
	  walk_tree (&v, instantiate_expr, NULL, NULL);
	}
    }

  /* Process all subblocks.  */
  for (t = BLOCK_SUBBLOCKS (let); t; t = TREE_CHAIN (t))
    instantiate_decls_1 (t);
}