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
typedef  int /*<<< orphan*/  location_t ;

/* Variables and functions */
#define  BIND_EXPR 134 
 int /*<<< orphan*/  BIND_EXPR_BLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CATCH_BODY (int /*<<< orphan*/ ) ; 
#define  CATCH_EXPR 133 
#define  COND_EXPR 132 
 int /*<<< orphan*/  COND_EXPR_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COND_EXPR_ELSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COND_EXPR_THEN (int /*<<< orphan*/ ) ; 
#define  EH_FILTER_EXPR 131 
 int /*<<< orphan*/  EH_FILTER_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ EXPR_HAS_LOCATION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXPR_LOCATION (int /*<<< orphan*/ ) ; 
 scalar_t__ LOCATION_LINE (int /*<<< orphan*/ ) ; 
#define  STATEMENT_LIST 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  TRY_CATCH_EXPR 129 
#define  TRY_FINALLY_EXPR 128 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
remove_useless_stmts_warn_notreached (tree stmt)
{
  if (EXPR_HAS_LOCATION (stmt))
    {
      location_t loc = EXPR_LOCATION (stmt);
      if (LOCATION_LINE (loc) > 0)
	{
	  warning (0, "%Hwill never be executed", &loc);
	  return true;
	}
    }

  switch (TREE_CODE (stmt))
    {
    case STATEMENT_LIST:
      {
	tree_stmt_iterator i;
	for (i = tsi_start (stmt); !tsi_end_p (i); tsi_next (&i))
	  if (remove_useless_stmts_warn_notreached (tsi_stmt (i)))
	    return true;
      }
      break;

    case COND_EXPR:
      if (remove_useless_stmts_warn_notreached (COND_EXPR_COND (stmt)))
	return true;
      if (remove_useless_stmts_warn_notreached (COND_EXPR_THEN (stmt)))
	return true;
      if (remove_useless_stmts_warn_notreached (COND_EXPR_ELSE (stmt)))
	return true;
      break;

    case TRY_FINALLY_EXPR:
    case TRY_CATCH_EXPR:
      if (remove_useless_stmts_warn_notreached (TREE_OPERAND (stmt, 0)))
	return true;
      if (remove_useless_stmts_warn_notreached (TREE_OPERAND (stmt, 1)))
	return true;
      break;

    case CATCH_EXPR:
      return remove_useless_stmts_warn_notreached (CATCH_BODY (stmt));
    case EH_FILTER_EXPR:
      return remove_useless_stmts_warn_notreached (EH_FILTER_FAILURE (stmt));
    case BIND_EXPR:
      return remove_useless_stmts_warn_notreached (BIND_EXPR_BLOCK (stmt));

    default:
      /* Not a live container.  */
      break;
    }

  return false;
}