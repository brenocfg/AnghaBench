#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct deps {int dummy; } ;
typedef  scalar_t__ rtx ;
typedef  TYPE_2__* basic_block ;
struct TYPE_14__ {int queue_must_finish_empty; scalar_t__ tail; scalar_t__ head; int /*<<< orphan*/  next_tail; int /*<<< orphan*/  prev_head; scalar_t__ sched_max_insns_priority; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* dependencies_evaluation_hook ) (scalar_t__,scalar_t__) ;} ;
struct TYPE_13__ {TYPE_1__ sched; } ;
struct TYPE_12__ {int /*<<< orphan*/  next_bb; struct TYPE_12__* prev_bb; int /*<<< orphan*/  succs; int /*<<< orphan*/  preds; int /*<<< orphan*/  index; } ;

/* Variables and functions */
 TYPE_2__* BLOCK_FOR_INSN (scalar_t__) ; 
 scalar_t__ EDGE_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  NEXT_INSN (scalar_t__) ; 
 scalar_t__ NO_DEBUG ; 
 int /*<<< orphan*/  PREV_INSN (scalar_t__) ; 
 scalar_t__ REG_NOTES (scalar_t__) ; 
 scalar_t__ REG_NOTE_KIND (scalar_t__) ; 
 scalar_t__ REG_SAVE_NOTE ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  add_deps_for_risky_insns (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_forward_dependences (scalar_t__,scalar_t__) ; 
 TYPE_9__* current_sched_info ; 
 int /*<<< orphan*/  delete_basic_block (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dont_calc_deps ; 
 int /*<<< orphan*/  finish_deps_global () ; 
 int /*<<< orphan*/  free_deps (struct deps*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  init_deps (struct deps*) ; 
 int /*<<< orphan*/  init_deps_global () ; 
 TYPE_2__* last_bb ; 
 scalar_t__ n_insns ; 
 scalar_t__ no_real_insns_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  remove_note (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  restore_line_notes (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rm_line_notes (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rm_other_notes (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  save_line_notes (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  sched_analyze (struct deps*,scalar_t__,scalar_t__) ; 
 scalar_t__ sched_n_insns ; 
 int /*<<< orphan*/  schedule_block (TYPE_2__**,scalar_t__) ; 
 scalar_t__ set_priorities (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,scalar_t__) ; 
 TYPE_5__ targetm ; 
 int /*<<< orphan*/  unlink_bb_notes (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ write_symbols ; 

__attribute__((used)) static basic_block
schedule_ebb (rtx head, rtx tail)
{
  basic_block first_bb, target_bb;
  struct deps tmp_deps;
  
  first_bb = BLOCK_FOR_INSN (head);
  last_bb = BLOCK_FOR_INSN (tail);

  if (no_real_insns_p (head, tail))
    return BLOCK_FOR_INSN (tail);

  gcc_assert (INSN_P (head) && INSN_P (tail));

  if (!bitmap_bit_p (&dont_calc_deps, first_bb->index))
    {
      init_deps_global ();

      /* Compute LOG_LINKS.  */
      init_deps (&tmp_deps);
      sched_analyze (&tmp_deps, head, tail);
      free_deps (&tmp_deps);

      /* Compute INSN_DEPEND.  */
      compute_forward_dependences (head, tail);

      add_deps_for_risky_insns (head, tail);

      if (targetm.sched.dependencies_evaluation_hook)
        targetm.sched.dependencies_evaluation_hook (head, tail);

      finish_deps_global ();
    }
  else
    /* Only recovery blocks can have their dependencies already calculated,
       and they always are single block ebbs.  */       
    gcc_assert (first_bb == last_bb);

  /* Set priorities.  */
  current_sched_info->sched_max_insns_priority = 0;
  n_insns = set_priorities (head, tail);
  current_sched_info->sched_max_insns_priority++;

  current_sched_info->prev_head = PREV_INSN (head);
  current_sched_info->next_tail = NEXT_INSN (tail);

  if (write_symbols != NO_DEBUG)
    {
      save_line_notes (first_bb->index, head, tail);
      rm_line_notes (head, tail);
    }

  /* rm_other_notes only removes notes which are _inside_ the
     block---that is, it won't remove notes before the first real insn
     or after the last real insn of the block.  So if the first insn
     has a REG_SAVE_NOTE which would otherwise be emitted before the
     insn, it is redundant with the note before the start of the
     block, and so we have to take it out.  */
  if (INSN_P (head))
    {
      rtx note;

      for (note = REG_NOTES (head); note; note = XEXP (note, 1))
	if (REG_NOTE_KIND (note) == REG_SAVE_NOTE)
	  remove_note (head, note);
    }

  /* Remove remaining note insns from the block, save them in
     note_list.  These notes are restored at the end of
     schedule_block ().  */
  rm_other_notes (head, tail);

  unlink_bb_notes (first_bb, last_bb);

  current_sched_info->queue_must_finish_empty = 1;

  target_bb = first_bb;
  schedule_block (&target_bb, n_insns);

  /* We might pack all instructions into fewer blocks,
     so we may made some of them empty.  Can't assert (b == last_bb).  */
  
  /* Sanity check: verify that all region insns were scheduled.  */
  gcc_assert (sched_n_insns == n_insns);
  head = current_sched_info->head;
  tail = current_sched_info->tail;

  if (write_symbols != NO_DEBUG)
    restore_line_notes (head, tail);

  if (EDGE_COUNT (last_bb->preds) == 0)
    /* LAST_BB is unreachable.  */
    {
      gcc_assert (first_bb != last_bb
		  && EDGE_COUNT (last_bb->succs) == 0);
      last_bb = last_bb->prev_bb;
      delete_basic_block (last_bb->next_bb);
    }

  return last_bb;
}