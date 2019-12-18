#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
struct redirection_data {struct el* incoming_edges; TYPE_3__* outgoing_edge; TYPE_11__* dup_block; } ;
struct local_info {int jumps_threaded; TYPE_7__* bb; } ;
struct el {struct el* next; TYPE_4__* e; } ;
typedef  TYPE_4__* edge ;
struct TYPE_24__ {int index; } ;
struct TYPE_23__ {int flags; } ;
struct TYPE_22__ {int /*<<< orphan*/  num_threaded_edges; } ;
struct TYPE_21__ {TYPE_2__* dest; TYPE_1__* src; scalar_t__ count; int /*<<< orphan*/ * aux; } ;
struct TYPE_20__ {int /*<<< orphan*/  dest; } ;
struct TYPE_19__ {int index; } ;
struct TYPE_18__ {int index; } ;
struct TYPE_17__ {int /*<<< orphan*/  count; } ;
struct TYPE_16__ {int index; int /*<<< orphan*/  frequency; int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EDGE_ABNORMAL ; 
 int EDGE_FALLTHRU ; 
 int EDGE_FALSE_VALUE ; 
 scalar_t__ EDGE_FREQUENCY (TYPE_4__*) ; 
 TYPE_13__* EDGE_SUCC (TYPE_11__*,int /*<<< orphan*/ ) ; 
 int EDGE_TRUE_VALUE ; 
 int TDF_DETAILS ; 
 scalar_t__ dump_file ; 
 int dump_flags ; 
 int /*<<< orphan*/  flush_pending_stmts (TYPE_4__*) ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,...) ; 
 int /*<<< orphan*/  free (struct el*) ; 
 TYPE_4__* redirect_edge_and_branch (TYPE_4__*,TYPE_11__*) ; 
 int /*<<< orphan*/  remove_ctrl_stmt_and_useless_edges (TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* single_succ_edge (TYPE_7__*) ; 
 TYPE_5__ thread_stats ; 

__attribute__((used)) static int
redirect_edges (void **slot, void *data)
{
  struct redirection_data *rd = (struct redirection_data *) *slot;
  struct local_info *local_info = (struct local_info *)data;
  struct el *next, *el;

  /* Walk over all the incoming edges associated associated with this
     hash table entry.  */
  for (el = rd->incoming_edges; el; el = next)
    {
      edge e = el->e;

      /* Go ahead and free this element from the list.  Doing this now
	 avoids the need for another list walk when we destroy the hash
	 table.  */
      next = el->next;
      free (el);

      /* Go ahead and clear E->aux.  It's not needed anymore and failure
         to clear it will cause all kinds of unpleasant problems later.  */
      e->aux = NULL;

      thread_stats.num_threaded_edges++;

      if (rd->dup_block)
	{
	  edge e2;

	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "  Threaded jump %d --> %d to %d\n",
		     e->src->index, e->dest->index, rd->dup_block->index);

	  rd->dup_block->count += e->count;
	  rd->dup_block->frequency += EDGE_FREQUENCY (e);
	  EDGE_SUCC (rd->dup_block, 0)->count += e->count;
	  /* Redirect the incoming edge to the appropriate duplicate
	     block.  */
	  e2 = redirect_edge_and_branch (e, rd->dup_block);
	  flush_pending_stmts (e2);

	  if ((dump_file && (dump_flags & TDF_DETAILS))
	      && e->src != e2->src)
	    fprintf (dump_file, "    basic block %d created\n", e2->src->index);
	}
      else
	{
	  if (dump_file && (dump_flags & TDF_DETAILS))
	    fprintf (dump_file, "  Threaded jump %d --> %d to %d\n",
		     e->src->index, e->dest->index, local_info->bb->index);

	  /* We are using BB as the duplicate.  Remove the unnecessary
	     outgoing edges and statements from BB.  */
	  remove_ctrl_stmt_and_useless_edges (local_info->bb,
					      rd->outgoing_edge->dest);

	  /* And fixup the flags on the single remaining edge.  */
	  single_succ_edge (local_info->bb)->flags
	    &= ~(EDGE_TRUE_VALUE | EDGE_FALSE_VALUE | EDGE_ABNORMAL);
	  single_succ_edge (local_info->bb)->flags |= EDGE_FALLTHRU;
	}
    }

  /* Indicate that we actually threaded one or more jumps.  */
  if (rd->incoming_edges)
    local_info->jumps_threaded = true;

  return 1;
}