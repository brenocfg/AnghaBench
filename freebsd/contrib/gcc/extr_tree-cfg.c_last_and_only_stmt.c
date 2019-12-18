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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ LABEL_EXPR ; 
 int /*<<< orphan*/  NULL_TREE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_prev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_stmt (int /*<<< orphan*/ ) ; 

tree
last_and_only_stmt (basic_block bb)
{
  block_stmt_iterator i = bsi_last (bb);
  tree last, prev;

  if (bsi_end_p (i))
    return NULL_TREE;

  last = bsi_stmt (i);
  bsi_prev (&i);
  if (bsi_end_p (i))
    return last;

  /* Empty statements should no longer appear in the instruction stream.
     Everything that might have appeared before should be deleted by
     remove_useless_stmts, and the optimizers should just bsi_remove
     instead of smashing with build_empty_stmt.

     Thus the only thing that should appear here in a block containing
     one executable statement is a label.  */
  prev = bsi_stmt (i);
  if (TREE_CODE (prev) == LABEL_EXPR)
    return last;
  else
    return NULL_TREE;
}