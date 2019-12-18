#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  scalar_t__ sbitmap ;
typedef  int /*<<< orphan*/ * edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_1__* basic_block ;
struct TYPE_11__ {TYPE_1__* prev_bb; } ;
struct TYPE_10__ {int index; } ;

/* Variables and functions */
 TYPE_1__* BASIC_BLOCK (int) ; 
 int /*<<< orphan*/  EDGE_FAKE ; 
 TYPE_4__* EXIT_BLOCK_PTR ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ NUM_FIXED_BLOCKS ; 
 int TEST_BIT (scalar_t__,int) ; 
 int /*<<< orphan*/  bsi_commit_edge_inserts () ; 
 int /*<<< orphan*/  bsi_end_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_insert_on_edge (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (TYPE_1__*) ; 
 int /*<<< orphan*/  bsi_prev (int /*<<< orphan*/ *) ; 
 scalar_t__ bsi_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_empty_stmt () ; 
 int /*<<< orphan*/ * find_edge (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int last_basic_block ; 
 int /*<<< orphan*/  make_edge (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ n_basic_blocks ; 
 scalar_t__ need_fake_edge_p (scalar_t__) ; 
 int /*<<< orphan*/ * split_block (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  verify_flow_info () ; 

__attribute__((used)) static int
tree_flow_call_edges_add (sbitmap blocks)
{
  int i;
  int blocks_split = 0;
  int last_bb = last_basic_block;
  bool check_last_block = false;

  if (n_basic_blocks == NUM_FIXED_BLOCKS)
    return 0;

  if (! blocks)
    check_last_block = true;
  else
    check_last_block = TEST_BIT (blocks, EXIT_BLOCK_PTR->prev_bb->index);

  /* In the last basic block, before epilogue generation, there will be
     a fallthru edge to EXIT.  Special care is required if the last insn
     of the last basic block is a call because make_edge folds duplicate
     edges, which would result in the fallthru edge also being marked
     fake, which would result in the fallthru edge being removed by
     remove_fake_edges, which would result in an invalid CFG.

     Moreover, we can't elide the outgoing fake edge, since the block
     profiler needs to take this into account in order to solve the minimal
     spanning tree in the case that the call doesn't return.

     Handle this by adding a dummy instruction in a new last basic block.  */
  if (check_last_block)
    {
      basic_block bb = EXIT_BLOCK_PTR->prev_bb;
      block_stmt_iterator bsi = bsi_last (bb);
      tree t = NULL_TREE;
      if (!bsi_end_p (bsi))
	t = bsi_stmt (bsi);

      if (t && need_fake_edge_p (t))
	{
	  edge e;

	  e = find_edge (bb, EXIT_BLOCK_PTR);
	  if (e)
	    {
	      bsi_insert_on_edge (e, build_empty_stmt ());
	      bsi_commit_edge_inserts ();
	    }
	}
    }

  /* Now add fake edges to the function exit for any non constant
     calls since there is no way that we can determine if they will
     return or not...  */
  for (i = 0; i < last_bb; i++)
    {
      basic_block bb = BASIC_BLOCK (i);
      block_stmt_iterator bsi;
      tree stmt, last_stmt;

      if (!bb)
	continue;

      if (blocks && !TEST_BIT (blocks, i))
	continue;

      bsi = bsi_last (bb);
      if (!bsi_end_p (bsi))
	{
	  last_stmt = bsi_stmt (bsi);
	  do
	    {
	      stmt = bsi_stmt (bsi);
	      if (need_fake_edge_p (stmt))
		{
		  edge e;
		  /* The handling above of the final block before the
		     epilogue should be enough to verify that there is
		     no edge to the exit block in CFG already.
		     Calling make_edge in such case would cause us to
		     mark that edge as fake and remove it later.  */
#ifdef ENABLE_CHECKING
		  if (stmt == last_stmt)
		    {
		      e = find_edge (bb, EXIT_BLOCK_PTR);
		      gcc_assert (e == NULL);
		    }
#endif

		  /* Note that the following may create a new basic block
		     and renumber the existing basic blocks.  */
		  if (stmt != last_stmt)
		    {
		      e = split_block (bb, stmt);
		      if (e)
			blocks_split++;
		    }
		  make_edge (bb, EXIT_BLOCK_PTR, EDGE_FAKE);
		}
	      bsi_prev (&bsi);
	    }
	  while (!bsi_end_p (bsi));
	}
    }

  if (blocks_split)
    verify_flow_info ();

  return blocks_split;
}