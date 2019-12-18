#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ basic_block ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (scalar_t__) ; 
 scalar_t__ BB_PARTITION (scalar_t__) ; 
 int EDGE_COMPLEX ; 
 scalar_t__ ENTRY_BLOCK_PTR ; 
 scalar_t__ EXIT_BLOCK_PTR ; 
 int /*<<< orphan*/  JUMP_P (int /*<<< orphan*/ ) ; 
 scalar_t__ onlyjump_p (int /*<<< orphan*/ ) ; 
 scalar_t__ reload_completed ; 
 scalar_t__ simplejump_p (int /*<<< orphan*/ ) ; 
 int single_pred_p (scalar_t__) ; 
 scalar_t__ single_succ (scalar_t__) ; 
 TYPE_1__* single_succ_edge (scalar_t__) ; 
 scalar_t__ single_succ_p (scalar_t__) ; 

__attribute__((used)) static bool
cfg_layout_can_merge_blocks_p (basic_block a, basic_block b)
{
  /* If we are partitioning hot/cold basic blocks, we don't want to
     mess up unconditional or indirect jumps that cross between hot
     and cold sections.

     Basic block partitioning may result in some jumps that appear to
     be optimizable (or blocks that appear to be mergeable), but which really
     must be left untouched (they are required to make it safely across
     partition boundaries).  See  the comments at the top of
     bb-reorder.c:partition_hot_cold_basic_blocks for complete details.  */

  if (BB_PARTITION (a) != BB_PARTITION (b))
    return false;

  /* There must be exactly one edge in between the blocks.  */
  return (single_succ_p (a)
	  && single_succ (a) == b
	  && single_pred_p (b) == 1
	  && a != b
	  /* Must be simple edge.  */
	  && !(single_succ_edge (a)->flags & EDGE_COMPLEX)
	  && a != ENTRY_BLOCK_PTR && b != EXIT_BLOCK_PTR
	  /* If the jump insn has side effects,
	     we can't kill the edge.  */
	  && (!JUMP_P (BB_END (a))
	      || (reload_completed
		  ? simplejump_p (BB_END (a)) : onlyjump_p (BB_END (a)))));
}