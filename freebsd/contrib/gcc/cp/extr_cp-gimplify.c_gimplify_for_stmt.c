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
 int /*<<< orphan*/  FOR_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOR_BODY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOR_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FOR_EXPR (int /*<<< orphan*/ ) ; 
 scalar_t__ FOR_INIT_STMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  gimplify_and_add (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gimplify_cp_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gimplify_for_stmt (tree *stmt_p, tree *pre_p)
{
  tree stmt = *stmt_p;

  if (FOR_INIT_STMT (stmt))
    gimplify_and_add (FOR_INIT_STMT (stmt), pre_p);

/* APPLE LOCAL begin for-fsf-4_4 3274130 5295549 */ \
  *stmt_p = gimplify_cp_loop (FOR_COND (stmt), FOR_BODY (stmt),
			      FOR_EXPR (stmt), FOR_ATTRIBUTES (stmt), 1,
			      NULL_TREE);
/* APPLE LOCAL end for-fsf-4_4 3274130 5295549 */ \
}