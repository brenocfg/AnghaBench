#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  edge_iterator ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_11__ {int /*<<< orphan*/  prev_bb; int /*<<< orphan*/  preds; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 scalar_t__ BARRIER_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BB_SUPERBLOCK ; 
 TYPE_8__* BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 int EDGE_FALLTHRU ; 
 int /*<<< orphan*/  PREV_INSN (int /*<<< orphan*/ ) ; 
 TYPE_2__* create_basic_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_next (int /*<<< orphan*/ *) ; 
 TYPE_1__* ei_safe_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ei_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn_before (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_nonfallthru (TYPE_1__*) ; 
 int /*<<< orphan*/  update_bb_for_insn (TYPE_2__*) ; 

__attribute__((used)) static basic_block
emit_to_new_bb_before (rtx seq, rtx insn)
{
  rtx last;
  basic_block bb;
  edge e;
  edge_iterator ei;

  /* If there happens to be a fallthru edge (possibly created by cleanup_cfg
     call), we don't want it to go into newly created landing pad or other EH
     construct.  */
  for (ei = ei_start (BLOCK_FOR_INSN (insn)->preds); (e = ei_safe_edge (ei)); )
    if (e->flags & EDGE_FALLTHRU)
      force_nonfallthru (e);
    else
      ei_next (&ei);
  last = emit_insn_before (seq, insn);
  if (BARRIER_P (last))
    last = PREV_INSN (last);
  bb = create_basic_block (seq, last, BLOCK_FOR_INSN (insn)->prev_bb);
  update_bb_for_insn (bb);
  bb->flags |= BB_SUPERBLOCK;
  return bb;
}