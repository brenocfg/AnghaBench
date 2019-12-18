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
 scalar_t__ STATEMENT_LIST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ alloc_stmt_list () ; 
 int /*<<< orphan*/  append_to_statement_list (scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  gimplify_stmt (scalar_t__*) ; 

void
gimplify_to_stmt_list (tree *stmt_p)
{
  gimplify_stmt (stmt_p);
  if (!*stmt_p)
    *stmt_p = alloc_stmt_list ();
  else if (TREE_CODE (*stmt_p) != STATEMENT_LIST)
    {
      tree t = *stmt_p;
      *stmt_p = alloc_stmt_list ();
      append_to_statement_list (t, stmt_p);
    }
}