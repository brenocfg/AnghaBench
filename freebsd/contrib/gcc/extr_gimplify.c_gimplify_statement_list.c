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
typedef  int /*<<< orphan*/ * tree ;
typedef  enum gimplify_status { ____Placeholder_gimplify_status } gimplify_status ;

/* Variables and functions */
 int GS_ALL_DONE ; 
 int GS_OK ; 
 scalar_t__ STATEMENT_LIST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TSI_SAME_STMT ; 
 int /*<<< orphan*/  append_to_statement_list (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  gimplify_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_delink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_link_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * voidify_wrapper_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static enum gimplify_status
gimplify_statement_list (tree *expr_p, tree *pre_p)
{
  tree temp = voidify_wrapper_expr (*expr_p, NULL);

  tree_stmt_iterator i = tsi_start (*expr_p);

  while (!tsi_end_p (i))
    {
      tree t;

      gimplify_stmt (tsi_stmt_ptr (i));

      t = tsi_stmt (i);
      if (t == NULL)
	tsi_delink (&i);
      else if (TREE_CODE (t) == STATEMENT_LIST)
	{
	  tsi_link_before (&i, t, TSI_SAME_STMT);
	  tsi_delink (&i);
	}
      else
	tsi_next (&i);
    }

  if (temp)
    {
      append_to_statement_list (*expr_p, pre_p);
      *expr_p = temp;
      return GS_OK;
    }

  return GS_ALL_DONE;
}