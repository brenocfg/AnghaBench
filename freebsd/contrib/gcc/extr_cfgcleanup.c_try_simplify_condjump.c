#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_25__ {scalar_t__ next_bb; int /*<<< orphan*/  succs; } ;
struct TYPE_24__ {int flags; TYPE_2__* dest; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (TYPE_2__*) ; 
 scalar_t__ BB_PARTITION (TYPE_2__*) ; 
 TYPE_1__* BRANCH_EDGE (TYPE_2__*) ; 
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int EDGE_CROSSING ; 
 int EDGE_FALLTHRU ; 
 scalar_t__ EXIT_BLOCK_PTR ; 
 TYPE_1__* FALLTHRU_EDGE (TYPE_2__*) ; 
 int /*<<< orphan*/  FORWARDER_BLOCK_P (TYPE_2__*) ; 
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  any_condjump_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_label (TYPE_2__*) ; 
 int /*<<< orphan*/  can_fallthru (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  delete_basic_block (TYPE_2__*) ; 
 scalar_t__ dump_file ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int) ; 
 int /*<<< orphan*/  invert_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* redirect_edge_succ_nodup (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  single_pred_p (TYPE_2__*) ; 
 TYPE_2__* single_succ (TYPE_2__*) ; 
 int /*<<< orphan*/  tidy_fallthru_edge (TYPE_1__*) ; 
 int /*<<< orphan*/  update_br_prob_note (TYPE_2__*) ; 
 int /*<<< orphan*/  update_forwarder_flag (TYPE_2__*) ; 

__attribute__((used)) static bool
try_simplify_condjump (basic_block cbranch_block)
{
  basic_block jump_block, jump_dest_block, cbranch_dest_block;
  edge cbranch_jump_edge, cbranch_fallthru_edge;
  rtx cbranch_insn;

  /* Verify that there are exactly two successors.  */
  if (EDGE_COUNT (cbranch_block->succs) != 2)
    return false;

  /* Verify that we've got a normal conditional branch at the end
     of the block.  */
  cbranch_insn = BB_END (cbranch_block);
  if (!any_condjump_p (cbranch_insn))
    return false;

  cbranch_fallthru_edge = FALLTHRU_EDGE (cbranch_block);
  cbranch_jump_edge = BRANCH_EDGE (cbranch_block);

  /* The next block must not have multiple predecessors, must not
     be the last block in the function, and must contain just the
     unconditional jump.  */
  jump_block = cbranch_fallthru_edge->dest;
  if (!single_pred_p (jump_block)
      || jump_block->next_bb == EXIT_BLOCK_PTR
      || !FORWARDER_BLOCK_P (jump_block))
    return false;
  jump_dest_block = single_succ (jump_block);

  /* If we are partitioning hot/cold basic blocks, we don't want to
     mess up unconditional or indirect jumps that cross between hot
     and cold sections.

     Basic block partitioning may result in some jumps that appear to
     be optimizable (or blocks that appear to be mergeable), but which really
     must be left untouched (they are required to make it safely across
     partition boundaries).  See the comments at the top of
     bb-reorder.c:partition_hot_cold_basic_blocks for complete details.  */

  if (BB_PARTITION (jump_block) != BB_PARTITION (jump_dest_block)
      || (cbranch_jump_edge->flags & EDGE_CROSSING))
    return false;

  /* The conditional branch must target the block after the
     unconditional branch.  */
  cbranch_dest_block = cbranch_jump_edge->dest;

  if (cbranch_dest_block == EXIT_BLOCK_PTR
      || !can_fallthru (jump_block, cbranch_dest_block))
    return false;

  /* Invert the conditional branch.  */
  if (!invert_jump (cbranch_insn, block_label (jump_dest_block), 0))
    return false;

  if (dump_file)
    fprintf (dump_file, "Simplifying condjump %i around jump %i\n",
	     INSN_UID (cbranch_insn), INSN_UID (BB_END (jump_block)));

  /* Success.  Update the CFG to match.  Note that after this point
     the edge variable names appear backwards; the redirection is done
     this way to preserve edge profile data.  */
  cbranch_jump_edge = redirect_edge_succ_nodup (cbranch_jump_edge,
						cbranch_dest_block);
  cbranch_fallthru_edge = redirect_edge_succ_nodup (cbranch_fallthru_edge,
						    jump_dest_block);
  cbranch_jump_edge->flags |= EDGE_FALLTHRU;
  cbranch_fallthru_edge->flags &= ~EDGE_FALLTHRU;
  update_br_prob_note (cbranch_block);

  /* Delete the block with the unconditional jump, and clean up the mess.  */
  delete_basic_block (jump_block);
  tidy_fallthru_edge (cbranch_jump_edge);
  update_forwarder_flag (cbranch_block);

  return true;
}