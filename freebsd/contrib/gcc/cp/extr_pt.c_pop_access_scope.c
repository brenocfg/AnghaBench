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
 scalar_t__ DECL_FRIEND_CONTEXT (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_function_decl ; 
 int /*<<< orphan*/  pop_from_top_level () ; 
 int /*<<< orphan*/  pop_nested_class () ; 
 int /*<<< orphan*/  saved_access_scope ; 

__attribute__((used)) static void
pop_access_scope (tree t)
{
  if (TREE_CODE (t) == FUNCTION_DECL)
    {
      current_function_decl = TREE_VALUE (saved_access_scope);
      saved_access_scope = TREE_CHAIN (saved_access_scope);
    }

  if (DECL_FRIEND_CONTEXT (t) || DECL_CLASS_SCOPE_P (t))
    pop_nested_class ();
  else
    pop_from_top_level ();
}