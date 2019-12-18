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
typedef  int /*<<< orphan*/ * tree ;
typedef  int TREE_SIDE_EFFECTS ;

/* Variables and functions */
 scalar_t__ BIND_EXPR ; 
 scalar_t__ STATEMENT_LIST_STMT_EXPR (scalar_t__) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build3 (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * c_build_bind_expr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ c_dialect_objc () ; 
 scalar_t__ cur_stmt_list ; 
 int /*<<< orphan*/  objc_clear_super_receiver () ; 
 int /*<<< orphan*/ * pop_scope () ; 
 int /*<<< orphan*/ * pop_stmt_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  void_type_node ; 

tree
c_end_compound_stmt (tree stmt, bool do_scope)
{
  tree block = NULL;

  if (do_scope)
    {
      if (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = pop_scope ();
    }

  stmt = pop_stmt_list (stmt);
  stmt = c_build_bind_expr (block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  if (cur_stmt_list
      && STATEMENT_LIST_STMT_EXPR (cur_stmt_list)
      && TREE_CODE (stmt) != BIND_EXPR)
    {
      stmt = build3 (BIND_EXPR, void_type_node, NULL, stmt, NULL);
      TREE_SIDE_EFFECTS (stmt) = 1;
    }

  return stmt;
}