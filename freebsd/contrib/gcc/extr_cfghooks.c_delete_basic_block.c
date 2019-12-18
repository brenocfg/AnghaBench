#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* basic_block ;
struct TYPE_10__ {int /*<<< orphan*/  (* delete_basic_block ) (TYPE_1__*) ;int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  succs; int /*<<< orphan*/  preds; } ;

/* Variables and functions */
 size_t CDI_DOMINATORS ; 
 size_t CDI_POST_DOMINATORS ; 
 scalar_t__ EDGE_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_PRED (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EDGE_SUCC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* cfg_hooks ; 
 int /*<<< orphan*/  delete_from_dominance_info (size_t,TYPE_1__*) ; 
 scalar_t__* dom_computed ; 
 int /*<<< orphan*/  expunge_block (TYPE_1__*) ; 
 int /*<<< orphan*/  internal_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_edge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void
delete_basic_block (basic_block bb)
{
  if (!cfg_hooks->delete_basic_block)
    internal_error ("%s does not support delete_basic_block", cfg_hooks->name);

  cfg_hooks->delete_basic_block (bb);

  /* Remove the edges into and out of this block.  Note that there may
     indeed be edges in, if we are removing an unreachable loop.  */
  while (EDGE_COUNT (bb->preds) != 0)
    remove_edge (EDGE_PRED (bb, 0));
  while (EDGE_COUNT (bb->succs) != 0)
    remove_edge (EDGE_SUCC (bb, 0));

  if (dom_computed[CDI_DOMINATORS])
    delete_from_dominance_info (CDI_DOMINATORS, bb);
  if (dom_computed[CDI_POST_DOMINATORS])
    delete_from_dominance_info (CDI_POST_DOMINATORS, bb);

  /* Remove the basic block from the array.  */
  expunge_block (bb);
}