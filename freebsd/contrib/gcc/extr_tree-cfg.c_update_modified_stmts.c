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
typedef  int /*<<< orphan*/  tree_stmt_iterator ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ STATEMENT_LIST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_stmt_if_modified (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
update_modified_stmts (tree t)
{
  if (TREE_CODE (t) == STATEMENT_LIST)
    {
      tree_stmt_iterator i;
      tree stmt;
      for (i = tsi_start (t); !tsi_end_p (i); tsi_next (&i))
        {
	  stmt = tsi_stmt (i);
	  update_stmt_if_modified (stmt);
	}
    }
  else
    update_stmt_if_modified (t);
}