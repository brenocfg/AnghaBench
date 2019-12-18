#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  TYPE_1__* edge ;
typedef  int /*<<< orphan*/  block_stmt_iterator ;
typedef  TYPE_2__* basic_block ;
struct TYPE_12__ {int flags; TYPE_2__* dest; scalar_t__ count; void* probability; } ;
struct TYPE_11__ {int index; } ;
struct TYPE_10__ {int /*<<< orphan*/  dest_idx; } ;

/* Variables and functions */
 int EDGE_FALLTHRU ; 
 int EDGE_FALSE_VALUE ; 
 TYPE_8__* EDGE_SUCC (TYPE_2__*,int) ; 
 int EDGE_TRUE_VALUE ; 
 int /*<<< orphan*/  PHI_ARG_DEF_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* REG_BR_PROB_BASE ; 
 int /*<<< orphan*/  SET_USE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TDF_DETAILS ; 
 TYPE_2__* bb_for_stmt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsi_last (TYPE_2__*) ; 
 int /*<<< orphan*/  bsi_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  delete_basic_block (TYPE_2__*) ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int) ; 

__attribute__((used)) static void
replace_phi_edge_with_variable (basic_block cond_block,
				edge e, tree phi, tree new)
{
  basic_block bb = bb_for_stmt (phi);
  basic_block block_to_remove;
  block_stmt_iterator bsi;

  /* Change the PHI argument to new.  */
  SET_USE (PHI_ARG_DEF_PTR (phi, e->dest_idx), new);

  /* Remove the empty basic block.  */
  if (EDGE_SUCC (cond_block, 0)->dest == bb)
    {
      EDGE_SUCC (cond_block, 0)->flags |= EDGE_FALLTHRU;
      EDGE_SUCC (cond_block, 0)->flags &= ~(EDGE_TRUE_VALUE | EDGE_FALSE_VALUE);
      EDGE_SUCC (cond_block, 0)->probability = REG_BR_PROB_BASE;
      EDGE_SUCC (cond_block, 0)->count += EDGE_SUCC (cond_block, 1)->count;

      block_to_remove = EDGE_SUCC (cond_block, 1)->dest;
    }
  else
    {
      EDGE_SUCC (cond_block, 1)->flags |= EDGE_FALLTHRU;
      EDGE_SUCC (cond_block, 1)->flags
	&= ~(EDGE_TRUE_VALUE | EDGE_FALSE_VALUE);
      EDGE_SUCC (cond_block, 1)->probability = REG_BR_PROB_BASE;
      EDGE_SUCC (cond_block, 1)->count += EDGE_SUCC (cond_block, 0)->count;

      block_to_remove = EDGE_SUCC (cond_block, 0)->dest;
    }
  delete_basic_block (block_to_remove);

  /* Eliminate the COND_EXPR at the end of COND_BLOCK.  */
  bsi = bsi_last (cond_block);
  bsi_remove (&bsi, true);

  if (dump_file && (dump_flags & TDF_DETAILS))
    fprintf (dump_file,
	      "COND_EXPR in block %d and PHI in block %d converted to straightline code.\n",
	      cond_block->index,
	      bb->index);
}