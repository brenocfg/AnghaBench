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
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_VALUE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * build_empty_stmt () ; 
 int /*<<< orphan*/  error (char*) ; 

__attribute__((used)) static bool
diagnose_sb_0 (tree *stmt_p, tree branch_ctx, tree label_ctx)
{
  bool exit_p = true;

  if ((label_ctx ? TREE_VALUE (label_ctx) : NULL) == branch_ctx)
    return false;

  /* Try to avoid confusing the user by producing and error message
     with correct "exit" or "enter" verbage.  We prefer "exit"
     unless we can show that LABEL_CTX is nested within BRANCH_CTX.  */
  if (branch_ctx == NULL)
    exit_p = false;
  else
    {
      while (label_ctx)
	{
	  if (TREE_VALUE (label_ctx) == branch_ctx)
	    {
	      exit_p = false;
	      break;
	    }
	  label_ctx = TREE_CHAIN (label_ctx);
	}
    }

  if (exit_p)
    error ("invalid exit from OpenMP structured block");
  else
    error ("invalid entry to OpenMP structured block");

  *stmt_p = build_empty_stmt ();
  return true;
}