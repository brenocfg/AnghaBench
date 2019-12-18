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
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 scalar_t__ COND_EXPR ; 
 scalar_t__ GOTO_EXPR ; 
 scalar_t__ IS_EMPTY_STMT (scalar_t__) ; 
 scalar_t__ LABEL_EXPR ; 
 scalar_t__ SWITCH_EXPR ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bsi_start (int /*<<< orphan*/ ) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
redirection_block_p (basic_block bb)
{
  block_stmt_iterator bsi;

  /* Advance to the first executable statement.  */
  bsi = bsi_start (bb);
  while (!bsi_end_p (bsi)
          && (TREE_CODE (bsi_stmt (bsi)) == LABEL_EXPR
              || IS_EMPTY_STMT (bsi_stmt (bsi))))
    bsi_next (&bsi);

  /* Check if this is an empty block.  */
  if (bsi_end_p (bsi))
    return true;

  /* Test that we've reached the terminating control statement.  */
  return bsi_stmt (bsi)
	 && (TREE_CODE (bsi_stmt (bsi)) == COND_EXPR
	     || TREE_CODE (bsi_stmt (bsi)) == GOTO_EXPR
	     || TREE_CODE (bsi_stmt (bsi)) == SWITCH_EXPR);
}