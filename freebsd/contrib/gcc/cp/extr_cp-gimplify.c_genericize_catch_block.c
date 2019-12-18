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
 int /*<<< orphan*/  CATCH_EXPR ; 
 int /*<<< orphan*/  HANDLER_BODY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HANDLER_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_stmt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
genericize_catch_block (tree *stmt_p)
{
  tree type = HANDLER_TYPE (*stmt_p);
  tree body = HANDLER_BODY (*stmt_p);

  gimplify_stmt (&body);

  /* FIXME should the caught type go in TREE_TYPE?  */
  *stmt_p = build2 (CATCH_EXPR, void_type_node, type, body);
}