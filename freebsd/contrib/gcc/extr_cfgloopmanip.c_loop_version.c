#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_1__ ;

/* Type definitions */
struct loops {int dummy; } ;
struct loop {unsigned int num_nodes; TYPE_2__* latch; TYPE_1__* single_exit; TYPE_2__* header; scalar_t__ inner; } ;
typedef  TYPE_1__* edge ;
typedef  TYPE_2__* basic_block ;
struct TYPE_35__ {int flags; } ;
struct TYPE_34__ {int /*<<< orphan*/  flags; } ;
struct TYPE_33__ {int flags; TYPE_2__* dest; TYPE_2__* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_IRREDUCIBLE_LOOP ; 
 int EDGE_IRREDUCIBLE_LOOP ; 
 int /*<<< orphan*/  cfg_hook_duplicate_loop_to_header_edge (struct loop*,TYPE_1__*,struct loops*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_cond_bb_edges (TYPE_2__*,TYPE_1__**,TYPE_1__**) ; 
 TYPE_1__* find_edge (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__**) ; 
 TYPE_2__* get_bb_copy (TYPE_2__*) ; 
 TYPE_2__** get_loop_body_in_dom_order (struct loop*) ; 
 TYPE_1__* loop_preheader_edge (struct loop*) ; 
 int /*<<< orphan*/  loop_split_edge_with (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct loop* loopify (struct loops*,TYPE_1__*,TYPE_5__*,TYPE_2__*,TYPE_1__*,TYPE_1__*,int) ; 
 TYPE_2__* lv_adjust_loop_entry_edge (TYPE_2__*,TYPE_2__*,TYPE_1__*,void*) ; 
 int /*<<< orphan*/  lv_flush_pending_stmts (TYPE_1__*) ; 
 int /*<<< orphan*/  move_block_after (TYPE_2__*,TYPE_2__*) ; 
 TYPE_5__* single_pred_edge (TYPE_2__*) ; 
 TYPE_1__* single_succ_edge (TYPE_2__*) ; 

struct loop *
loop_version (struct loops *loops, struct loop * loop,
	      void *cond_expr, basic_block *condition_bb,
	      bool place_after)
{
  basic_block first_head, second_head;
  edge entry, latch_edge, exit, true_edge, false_edge;
  int irred_flag;
  struct loop *nloop;
  basic_block cond_bb;

  /* CHECKME: Loop versioning does not handle nested loop at this point.  */
  if (loop->inner)
    return NULL;

  /* Record entry and latch edges for the loop */
  entry = loop_preheader_edge (loop);
  irred_flag = entry->flags & EDGE_IRREDUCIBLE_LOOP;
  entry->flags &= ~EDGE_IRREDUCIBLE_LOOP;

  /* Note down head of loop as first_head.  */
  first_head = entry->dest;

  /* Duplicate loop.  */
  if (!cfg_hook_duplicate_loop_to_header_edge (loop, entry, loops, 1,
					       NULL, NULL, NULL, NULL, 0))
    return NULL;

  /* After duplication entry edge now points to new loop head block.
     Note down new head as second_head.  */
  second_head = entry->dest;

  /* Split loop entry edge and insert new block with cond expr.  */
  cond_bb =  lv_adjust_loop_entry_edge (first_head, second_head,
					entry, cond_expr);
  if (condition_bb)
    *condition_bb = cond_bb;

  if (!cond_bb)
    {
      entry->flags |= irred_flag;
      return NULL;
    }

  latch_edge = single_succ_edge (get_bb_copy (loop->latch));

  extract_cond_bb_edges (cond_bb, &true_edge, &false_edge);
  nloop = loopify (loops,
		   latch_edge,
		   single_pred_edge (get_bb_copy (loop->header)),
		   cond_bb, true_edge, false_edge,
		   false /* Do not redirect all edges.  */);

  exit = loop->single_exit;
  if (exit)
    nloop->single_exit = find_edge (get_bb_copy (exit->src), exit->dest);

  /* loopify redirected latch_edge. Update its PENDING_STMTS.  */
  lv_flush_pending_stmts (latch_edge);

  /* loopify redirected condition_bb's succ edge. Update its PENDING_STMTS.  */
  extract_cond_bb_edges (cond_bb, &true_edge, &false_edge);
  lv_flush_pending_stmts (false_edge);
  /* Adjust irreducible flag.  */
  if (irred_flag)
    {
      cond_bb->flags |= BB_IRREDUCIBLE_LOOP;
      loop_preheader_edge (loop)->flags |= EDGE_IRREDUCIBLE_LOOP;
      loop_preheader_edge (nloop)->flags |= EDGE_IRREDUCIBLE_LOOP;
      single_pred_edge (cond_bb)->flags |= EDGE_IRREDUCIBLE_LOOP;
    }

  if (place_after)
    {
      basic_block *bbs = get_loop_body_in_dom_order (nloop), after;
      unsigned i;

      after = loop->latch;

      for (i = 0; i < nloop->num_nodes; i++)
	{
	  move_block_after (bbs[i], after);
	  after = bbs[i];
	}
      free (bbs);
    }

  /* At this point condition_bb is loop predheader with two successors,
     first_head and second_head.   Make sure that loop predheader has only
     one successor.  */
  loop_split_edge_with (loop_preheader_edge (loop), NULL);
  loop_split_edge_with (loop_preheader_edge (nloop), NULL);

  return nloop;
}