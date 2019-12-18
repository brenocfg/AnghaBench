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

/* Variables and functions */
 int /*<<< orphan*/ * EXPR_STMT_EXPR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IS_EMPTY_STMT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wextra ; 
 int /*<<< orphan*/  TREE_NO_WARNING (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * alloc_stmt_list () ; 
 int /*<<< orphan*/ * error_mark_node ; 
 scalar_t__ extra_warnings ; 
 int /*<<< orphan*/  input_location ; 
 int /*<<< orphan*/  warn_if_unused_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ warn_unused_value ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
gimplify_expr_stmt (tree *stmt_p)
{
  tree stmt = EXPR_STMT_EXPR (*stmt_p);

  if (stmt == error_mark_node)
    stmt = NULL;

  /* Gimplification of a statement expression will nullify the
     statement if all its side effects are moved to *PRE_P and *POST_P.

     In this case we will not want to emit the gimplified statement.
     However, we may still want to emit a warning, so we do that before
     gimplification.  */
  if (stmt && (extra_warnings || warn_unused_value))
    {
      if (!TREE_SIDE_EFFECTS (stmt))
	{
	  if (!IS_EMPTY_STMT (stmt)
	      && !VOID_TYPE_P (TREE_TYPE (stmt))
	      && !TREE_NO_WARNING (stmt))
	    warning (OPT_Wextra, "statement with no effect");
	}
      else if (warn_unused_value)
	warn_if_unused_value (stmt, input_location);
    }

  if (stmt == NULL_TREE)
    stmt = alloc_stmt_list ();

  *stmt_p = stmt;
}