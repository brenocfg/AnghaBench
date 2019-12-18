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
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POP_TIMEVAR_AND_RETURN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TV_NAME_LOOKUP ; 
 int /*<<< orphan*/  finish_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pop_from_top_level () ; 
 int /*<<< orphan*/  push_to_top_level () ; 
 int /*<<< orphan*/  pushdecl_namespace_level (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timevar_push (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
pushdecl_top_level_1 (tree x, tree *init, bool is_friend)
{
  timevar_push (TV_NAME_LOOKUP);
  push_to_top_level ();
  x = pushdecl_namespace_level (x, is_friend);
  if (init)
    finish_decl (x, *init, NULL_TREE);
  pop_from_top_level ();
  POP_TIMEVAR_AND_RETURN (TV_NAME_LOOKUP, x);
}