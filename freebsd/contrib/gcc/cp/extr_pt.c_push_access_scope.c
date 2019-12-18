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
 scalar_t__ DECL_CLASS_SCOPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_FRIEND_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  push_nested_class (scalar_t__) ; 
 int /*<<< orphan*/  push_to_top_level () ; 
 int /*<<< orphan*/  saved_access_scope ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
push_access_scope (tree t)
{
  gcc_assert (TREE_CODE (t) == FUNCTION_DECL
	      || TREE_CODE (t) == VAR_DECL);

  if (DECL_FRIEND_CONTEXT (t))
    push_nested_class (DECL_FRIEND_CONTEXT (t));
  else if (DECL_CLASS_SCOPE_P (t))
    push_nested_class (DECL_CONTEXT (t));
  else
    push_to_top_level ();

  if (TREE_CODE (t) == FUNCTION_DECL)
    {
      saved_access_scope = tree_cons
	(NULL_TREE, current_function_decl, saved_access_scope);
      current_function_decl = t;
    }
}