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
 scalar_t__ COMPOUND_EXPR ; 
 scalar_t__ STATEMENT_LIST ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  annotate_one_with_locus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_stmt (int /*<<< orphan*/ ) ; 

void
annotate_all_with_locus (tree *stmt_p, location_t locus)
{
  tree_stmt_iterator i;

  if (!*stmt_p)
    return;

  for (i = tsi_start (*stmt_p); !tsi_end_p (i); tsi_next (&i))
    {
      tree t = tsi_stmt (i);

      /* Assuming we've already been gimplified, we shouldn't
	  see nested chaining constructs anymore.  */
      gcc_assert (TREE_CODE (t) != STATEMENT_LIST
		  && TREE_CODE (t) != COMPOUND_EXPR);

      annotate_one_with_locus (t, locus);
    }
}