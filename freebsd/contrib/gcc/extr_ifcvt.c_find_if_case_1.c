#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* edge ;
typedef  TYPE_4__* basic_block ;
struct TYPE_32__ {int flags; } ;
struct TYPE_29__ {TYPE_1__* rtl; } ;
struct TYPE_31__ {int index; struct TYPE_31__* prev_bb; struct TYPE_31__* next_bb; TYPE_2__ il; } ;
struct TYPE_30__ {TYPE_4__* dest; } ;
struct TYPE_28__ {int /*<<< orphan*/  global_live_at_end; int /*<<< orphan*/  global_live_at_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_COPY_PARTITION (TYPE_4__*,TYPE_4__*) ; 
 scalar_t__ BB_END (TYPE_4__*) ; 
 int /*<<< orphan*/  BRANCH_COST ; 
 int /*<<< orphan*/  COSTS_N_INSNS (int /*<<< orphan*/ ) ; 
 int EDGE_COMPLEX ; 
 int EDGE_FALLTHRU ; 
 TYPE_4__* EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/  FALLTHRU_EDGE (TYPE_4__*) ; 
 int FALSE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REG_CROSSING_JUMP ; 
 int /*<<< orphan*/  SET_BASIC_BLOCK (int,TYPE_4__*) ; 
 int TRUE ; 
 int /*<<< orphan*/  bitmap_ior (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cheap_bb_rtx_cost_p (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dead_or_predicable (TYPE_4__*,TYPE_4__*,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  delete_basic_block (TYPE_4__*) ; 
 scalar_t__ dump_file ; 
 scalar_t__ find_reg_note (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ forwarder_block_p (TYPE_4__*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int) ; 
 int /*<<< orphan*/  num_possible_if_blocks ; 
 int /*<<< orphan*/  num_true_changes ; 
 int /*<<< orphan*/  num_updated_if_blocks ; 
 TYPE_4__* redirect_edge_and_branch_force (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  redirect_edge_succ (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  single_pred_p (TYPE_4__*) ; 
 int /*<<< orphan*/  single_succ (TYPE_4__*) ; 
 TYPE_6__* single_succ_edge (TYPE_4__*) ; 
 int /*<<< orphan*/  single_succ_p (TYPE_4__*) ; 

__attribute__((used)) static int
find_if_case_1 (basic_block test_bb, edge then_edge, edge else_edge)
{
  basic_block then_bb = then_edge->dest;
  basic_block else_bb = else_edge->dest, new_bb;
  int then_bb_index;

  /* If we are partitioning hot/cold basic blocks, we don't want to
     mess up unconditional or indirect jumps that cross between hot
     and cold sections.
  
     Basic block partitioning may result in some jumps that appear to
     be optimizable (or blocks that appear to be mergeable), but which really 
     must be left untouched (they are required to make it safely across 
     partition boundaries).  See  the comments at the top of 
     bb-reorder.c:partition_hot_cold_basic_blocks for complete details.  */

  if ((BB_END (then_bb) 
       && find_reg_note (BB_END (then_bb), REG_CROSSING_JUMP, NULL_RTX))
      || (BB_END (test_bb)
	  && find_reg_note (BB_END (test_bb), REG_CROSSING_JUMP, NULL_RTX))
      || (BB_END (else_bb)
	  && find_reg_note (BB_END (else_bb), REG_CROSSING_JUMP, 
			    NULL_RTX)))
    return FALSE;

  /* THEN has one successor.  */
  if (!single_succ_p (then_bb))
    return FALSE;

  /* THEN does not fall through, but is not strange either.  */
  if (single_succ_edge (then_bb)->flags & (EDGE_COMPLEX | EDGE_FALLTHRU))
    return FALSE;

  /* THEN has one predecessor.  */
  if (!single_pred_p (then_bb))
    return FALSE;

  /* THEN must do something.  */
  if (forwarder_block_p (then_bb))
    return FALSE;

  num_possible_if_blocks++;
  if (dump_file)
    fprintf (dump_file,
	     "\nIF-CASE-1 found, start %d, then %d\n",
	     test_bb->index, then_bb->index);

  /* THEN is small.  */
  if (! cheap_bb_rtx_cost_p (then_bb, COSTS_N_INSNS (BRANCH_COST)))
    return FALSE;

  /* Registers set are dead, or are predicable.  */
  if (! dead_or_predicable (test_bb, then_bb, else_bb,
			    single_succ (then_bb), 1))
    return FALSE;

  /* Conversion went ok, including moving the insns and fixing up the
     jump.  Adjust the CFG to match.  */

  bitmap_ior (test_bb->il.rtl->global_live_at_end,
	      else_bb->il.rtl->global_live_at_start,
	      then_bb->il.rtl->global_live_at_end);


  /* We can avoid creating a new basic block if then_bb is immediately
     followed by else_bb, i.e. deleting then_bb allows test_bb to fall
     thru to else_bb.  */

  if (then_bb->next_bb == else_bb
      && then_bb->prev_bb == test_bb
      && else_bb != EXIT_BLOCK_PTR)
    {
      redirect_edge_succ (FALLTHRU_EDGE (test_bb), else_bb);
      new_bb = 0;
    }
  else
    new_bb = redirect_edge_and_branch_force (FALLTHRU_EDGE (test_bb),
                                             else_bb);

  then_bb_index = then_bb->index;
  delete_basic_block (then_bb);

  /* Make rest of code believe that the newly created block is the THEN_BB
     block we removed.  */
  if (new_bb)
    {
      new_bb->index = then_bb_index;
      SET_BASIC_BLOCK (then_bb_index, new_bb);
      /* Since the fallthru edge was redirected from test_bb to new_bb,
         we need to ensure that new_bb is in the same partition as
         test bb (you can not fall through across section boundaries).  */
      BB_COPY_PARTITION (new_bb, test_bb);
    }
  /* We've possibly created jump to next insn, cleanup_cfg will solve that
     later.  */

  num_true_changes++;
  num_updated_if_blocks++;

  return TRUE;
}