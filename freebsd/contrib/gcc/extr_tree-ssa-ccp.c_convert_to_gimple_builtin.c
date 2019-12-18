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
typedef  int /*<<< orphan*/  block_stmt_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  BSI_NEW_STMT ; 
 scalar_t__ EXPR_HAS_LOCATION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EXPR_LOCATION (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  annotate_all_with_locus (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_before (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_new_referenced_vars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_initialized_tmp_var (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_new_vars_to_rename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pop_gimplify_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_gimplify_context () ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
convert_to_gimple_builtin (block_stmt_iterator *si_p, tree expr)
{
  tree_stmt_iterator ti;
  tree stmt = bsi_stmt (*si_p);
  tree tmp, stmts = NULL;

  push_gimplify_context ();
  tmp = get_initialized_tmp_var (expr, &stmts, NULL);
  pop_gimplify_context (NULL);

  if (EXPR_HAS_LOCATION (stmt))
    annotate_all_with_locus (&stmts, EXPR_LOCATION (stmt));

  /* The replacement can expose previously unreferenced variables.  */
  for (ti = tsi_start (stmts); !tsi_end_p (ti); tsi_next (&ti))
    {
      tree new_stmt = tsi_stmt (ti);
      find_new_referenced_vars (tsi_stmt_ptr (ti));
      bsi_insert_before (si_p, new_stmt, BSI_NEW_STMT);
      mark_new_vars_to_rename (bsi_stmt (*si_p));
      bsi_next (si_p);
    }

  return tmp;
}