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
 scalar_t__ DECL_ARGUMENTS (scalar_t__) ; 
 scalar_t__ DECL_HAS_VALUE_EXPR_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_INCOMING_RTL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_INITIAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_RTL (scalar_t__) ; 
 scalar_t__ DECL_VALUE_EXPR (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  instantiate_decl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_decls_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_expr ; 
 int /*<<< orphan*/  walk_tree (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
instantiate_decls (tree fndecl)
{
  tree decl;

  /* Process all parameters of the function.  */
  for (decl = DECL_ARGUMENTS (fndecl); decl; decl = TREE_CHAIN (decl))
    {
      instantiate_decl (DECL_RTL (decl));
      instantiate_decl (DECL_INCOMING_RTL (decl));
      if (DECL_HAS_VALUE_EXPR_P (decl))
	{
	  tree v = DECL_VALUE_EXPR (decl);
	  walk_tree (&v, instantiate_expr, NULL, NULL);
	}
    }

  /* Now process all variables defined in the function or its subblocks.  */
  instantiate_decls_1 (DECL_INITIAL (fndecl));
}