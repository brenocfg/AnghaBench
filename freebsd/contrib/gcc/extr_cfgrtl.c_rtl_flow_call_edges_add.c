#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sbitmap ;
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/ * edge ;
typedef  TYPE_1__* basic_block ;
struct TYPE_12__ {TYPE_1__* prev_bb; } ;
struct TYPE_11__ {int index; } ;

/* Variables and functions */
 TYPE_1__* BASIC_BLOCK (int) ; 
 scalar_t__ BB_END (TYPE_1__*) ; 
 scalar_t__ BB_HEAD (TYPE_1__*) ; 
 scalar_t__ CALL_P (scalar_t__) ; 
 int /*<<< orphan*/  EDGE_FAKE ; 
 TYPE_4__* EXIT_BLOCK_PTR ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 int NUM_FIXED_BLOCKS ; 
 scalar_t__ PREV_INSN (scalar_t__) ; 
 int TEST_BIT (scalar_t__,int) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  commit_edge_insertions () ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/ * find_edge (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_insn_on_edge (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ keep_with_call_p (scalar_t__) ; 
 int last_basic_block ; 
 int /*<<< orphan*/  make_edge (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int n_basic_blocks ; 
 scalar_t__ need_fake_edge_p (scalar_t__) ; 
 int /*<<< orphan*/ * split_block (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  verify_flow_info () ; 

__attribute__((used)) static int
rtl_flow_call_edges_add (sbitmap blocks)
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
      rtx insn = BB_END (bb);

      /* Back up past insns that must be kept in the same block as a call.  */
      while (insn != BB_HEAD (bb)
	     && keep_with_call_p (insn))
	insn = PREV_INSN (insn);

      if (need_fake_edge_p (insn))
	{
	  edge e;

	  e = find_edge (bb, EXIT_BLOCK_PTR);
	  if (e)
	    {
	      insert_insn_on_edge (gen_rtx_USE (VOIDmode, const0_rtx), e);
	      commit_edge_insertions ();
	    }
	}
    }

  /* Now add fake edges to the function exit for any non constant
     calls since there is no way that we can determine if they will
     return or not...  */

  for (i = NUM_FIXED_BLOCKS; i < last_bb; i++)
    {
      basic_block bb = BASIC_BLOCK (i);
      rtx insn;
      rtx prev_insn;

      if (!bb)
	continue;

      if (blocks && !TEST_BIT (blocks, i))
	continue;

      for (insn = BB_END (bb); ; insn = prev_insn)
	{
	  prev_insn = PREV_INSN (insn);
	  if (need_fake_edge_p (insn))
	    {
	      edge e;
	      rtx split_at_insn = insn;

	      /* Don't split the block between a call and an insn that should
		 remain in the same block as the call.  */
	      if (CALL_P (insn))
		while (split_at_insn != BB_END (bb)
		       && keep_with_call_p (NEXT_INSN (split_at_insn)))
		  split_at_insn = NEXT_INSN (split_at_insn);

	      /* The handling above of the final block before the epilogue
		 should be enough to verify that there is no edge to the exit
		 block in CFG already.  Calling make_edge in such case would
		 cause us to mark that edge as fake and remove it later.  */

#ifdef ENABLE_CHECKING
	      if (split_at_insn == BB_END (bb))
		{
		  e = find_edge (bb, EXIT_BLOCK_PTR);
		  gcc_assert (e == NULL);
		}
#endif

	      /* Note that the following may create a new basic block
		 and renumber the existing basic blocks.  */
	      if (split_at_insn != BB_END (bb))
		{
		  e = split_block (bb, split_at_insn);
		  if (e)
		    blocks_split++;
		}

	      make_edge (bb, EXIT_BLOCK_PTR, EDGE_FAKE);
	    }

	  if (insn == BB_HEAD (bb))
	    break;
	}
    }

  if (blocks_split)
    verify_flow_info ();

  return blocks_split;
}