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
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  ENTRY_BLOCK_PTR ; 
 scalar_t__ computed_goto_p (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_basic_block (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int found_computed_goto ; 
 int /*<<< orphan*/  set_bb_for_stmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stmt_ends_bb_p (int /*<<< orphan*/ *) ; 
 scalar_t__ stmt_starts_bb_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsi_split_statement_list_before (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * tsi_stmt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
make_blocks (tree stmt_list)
{
  tree_stmt_iterator i = tsi_start (stmt_list);
  tree stmt = NULL;
  bool start_new_block = true;
  bool first_stmt_of_list = true;
  basic_block bb = ENTRY_BLOCK_PTR;

  while (!tsi_end_p (i))
    {
      tree prev_stmt;

      prev_stmt = stmt;
      stmt = tsi_stmt (i);

      /* If the statement starts a new basic block or if we have determined
	 in a previous pass that we need to create a new block for STMT, do
	 so now.  */
      if (start_new_block || stmt_starts_bb_p (stmt, prev_stmt))
	{
	  if (!first_stmt_of_list)
	    stmt_list = tsi_split_statement_list_before (&i);
	  bb = create_basic_block (stmt_list, NULL, bb);
	  start_new_block = false;
	}

      /* Now add STMT to BB and create the subgraphs for special statement
	 codes.  */
      set_bb_for_stmt (stmt, bb);

      if (computed_goto_p (stmt))
	found_computed_goto = true;

      /* If STMT is a basic block terminator, set START_NEW_BLOCK for the
	 next iteration.  */
      if (stmt_ends_bb_p (stmt))
	start_new_block = true;

      tsi_next (&i);
      first_stmt_of_list = false;
    }
}