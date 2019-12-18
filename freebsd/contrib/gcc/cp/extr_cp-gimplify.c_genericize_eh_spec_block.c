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
 int /*<<< orphan*/  EH_SPEC_RAISES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EH_SPEC_STMTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  build_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_exc_ptr () ; 
 int /*<<< orphan*/  call_unexpected_node ; 
 int /*<<< orphan*/  gimple_build_eh_filter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
genericize_eh_spec_block (tree *stmt_p)
{
  tree body = EH_SPEC_STMTS (*stmt_p);
  tree allowed = EH_SPEC_RAISES (*stmt_p);
  tree failure = build_call (call_unexpected_node,
			     tree_cons (NULL_TREE, build_exc_ptr (),
					NULL_TREE));
  gimplify_stmt (&body);

  *stmt_p = gimple_build_eh_filter (body, allowed, failure);
}