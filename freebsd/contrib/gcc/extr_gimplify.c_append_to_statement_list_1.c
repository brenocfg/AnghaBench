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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ STATEMENT_LIST ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 int /*<<< orphan*/  TSI_CONTINUE_LINKING ; 
 scalar_t__ alloc_stmt_list () ; 
 int /*<<< orphan*/  tsi_last (scalar_t__) ; 
 int /*<<< orphan*/  tsi_link_after (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
append_to_statement_list_1 (tree t, tree *list_p)
{
  tree list = *list_p;
  tree_stmt_iterator i;

  if (!list)
    {
      if (t && TREE_CODE (t) == STATEMENT_LIST)
	{
	  *list_p = t;
	  return;
	}
      *list_p = list = alloc_stmt_list ();
    }

  i = tsi_last (list);
  tsi_link_after (&i, t, TSI_CONTINUE_LINKING);
}