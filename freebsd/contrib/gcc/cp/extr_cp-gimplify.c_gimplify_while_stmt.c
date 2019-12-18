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
 int /*<<< orphan*/  WHILE_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHILE_BODY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHILE_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gimplify_cp_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gimplify_while_stmt (tree *stmt_p)
{
  tree stmt = *stmt_p;
/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  *stmt_p = gimplify_cp_loop (WHILE_COND (stmt), WHILE_BODY (stmt),
			      NULL_TREE, WHILE_ATTRIBUTES (stmt), 1,
			      NULL_TREE);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
}