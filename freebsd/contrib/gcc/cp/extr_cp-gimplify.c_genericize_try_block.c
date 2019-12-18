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
 scalar_t__ CLEANUP_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRY_CATCH_EXPR ; 
 int /*<<< orphan*/  TRY_HANDLERS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRY_STMTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
genericize_try_block (tree *stmt_p)
{
  tree body = TRY_STMTS (*stmt_p);
  tree cleanup = TRY_HANDLERS (*stmt_p);

  gimplify_stmt (&body);

  if (CLEANUP_P (*stmt_p))
    /* A cleanup is an expression, so it doesn't need to be genericized.  */;
  else
    gimplify_stmt (&cleanup);

  *stmt_p = build2 (TRY_CATCH_EXPR, void_type_node, body, cleanup);
}