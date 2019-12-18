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
 int /*<<< orphan*/  EXPR_LOCUS (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ STATEMENT_LIST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_handlers_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pedwarn (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 

void
check_handlers (tree handlers)
{
  tree_stmt_iterator i;

  /* If we don't have a STATEMENT_LIST, then we've just got one
     handler, and thus nothing to warn about.  */
  if (TREE_CODE (handlers) != STATEMENT_LIST)
    return;

  i = tsi_start (handlers);
  if (!tsi_end_p (i))
    while (1)
      {
	tree handler = tsi_stmt (i);
	tsi_next (&i);

	/* No more handlers; nothing to shadow.  */
	if (tsi_end_p (i))
	  break;
	if (TREE_TYPE (handler) == NULL_TREE)
	  pedwarn ("%H%<...%> handler must be the last handler for"
		   " its try block", EXPR_LOCUS (handler));
	else
	  check_handlers_1 (handler, i);
      }
}