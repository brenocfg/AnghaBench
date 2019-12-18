#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  lines_executed; int /*<<< orphan*/  lines; } ;
struct TYPE_15__ {unsigned int num_lines; TYPE_9__ coverage; TYPE_5__* lines; TYPE_6__* functions; } ;
typedef  TYPE_4__ source_t ;
struct TYPE_12__ {TYPE_7__* blocks; TYPE_8__* branches; } ;
struct TYPE_16__ {scalar_t__ count; scalar_t__ exists; TYPE_1__ u; } ;
typedef  TYPE_5__ line_t ;
typedef  scalar_t__ gcov_type ;
struct TYPE_17__ {struct TYPE_17__* line_next; } ;
typedef  TYPE_6__ function_t ;
struct TYPE_13__ {unsigned int ident; TYPE_8__* arc; } ;
struct TYPE_14__ {TYPE_2__ cycle; } ;
struct TYPE_18__ {TYPE_3__ u; TYPE_8__* succ; struct TYPE_18__* chain; TYPE_8__* pred; } ;
typedef  TYPE_7__ block_t ;
struct TYPE_19__ {scalar_t__ count; scalar_t__ cs_count; int cycle; struct TYPE_19__* succ_next; TYPE_7__* src; TYPE_7__* dst; struct TYPE_19__* pred_next; struct TYPE_19__* line_next; } ;
typedef  TYPE_8__ arc_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_branch_counts (TYPE_9__*,TYPE_8__*) ; 
 int /*<<< orphan*/  flag_all_blocks ; 
 scalar_t__ flag_branches ; 

__attribute__((used)) static void
accumulate_line_counts (source_t *src)
{
  line_t *line;
  function_t *fn, *fn_p, *fn_n;
  unsigned ix;

  /* Reverse the function order.  */
  for (fn = src->functions, fn_p = NULL; fn;
       fn_p = fn, fn = fn_n)
    {
      fn_n = fn->line_next;
      fn->line_next = fn_p;
    }
  src->functions = fn_p;

  for (ix = src->num_lines, line = src->lines; ix--; line++)
    {
      if (!flag_all_blocks)
	{
	  arc_t *arc, *arc_p, *arc_n;

	  /* Total and reverse the branch information.  */
	  for (arc = line->u.branches, arc_p = NULL; arc;
	       arc_p = arc, arc = arc_n)
	    {
	      arc_n = arc->line_next;
	      arc->line_next = arc_p;

	      add_branch_counts (&src->coverage, arc);
	    }
	  line->u.branches = arc_p;
	}
      else if (line->u.blocks)
	{
	  /* The user expects the line count to be the number of times
	     a line has been executed. Simply summing the block count
	     will give an artificially high number.  The Right Thing
	     is to sum the entry counts to the graph of blocks on this
	     line, then find the elementary cycles of the local graph
	     and add the transition counts of those cycles.  */
	  block_t *block, *block_p, *block_n;
	  gcov_type count = 0;

	  /* Reverse the block information.  */
	  for (block = line->u.blocks, block_p = NULL; block;
	       block_p = block, block = block_n)
	    {
	      block_n = block->chain;
	      block->chain = block_p;
	      block->u.cycle.ident = ix;
	    }
	  line->u.blocks = block_p;

	  /* Sum the entry arcs.  */
	  for (block = line->u.blocks; block; block = block->chain)
	    {
	      arc_t *arc;

	      for (arc = block->pred; arc; arc = arc->pred_next)
		{
		  if (arc->src->u.cycle.ident != ix)
		    count += arc->count;
		  if (flag_branches)
		    add_branch_counts (&src->coverage, arc);
		}

	      /* Initialize the cs_count.  */
	      for (arc = block->succ; arc; arc = arc->succ_next)
		arc->cs_count = arc->count;
	    }

	  /* Find the loops. This uses the algorithm described in
	     Tiernan 'An Efficient Search Algorithm to Find the
	     Elementary Circuits of a Graph', CACM Dec 1970. We hold
	     the P array by having each block point to the arc that
	     connects to the previous block. The H array is implicitly
	     held because of the arc ordering, and the block's
	     previous arc pointer.

	     Although the algorithm is O(N^3) for highly connected
	     graphs, at worst we'll have O(N^2), as most blocks have
	     only one or two exits. Most graphs will be small.

	     For each loop we find, locate the arc with the smallest
	     transition count, and add that to the cumulative
	     count.  Decrease flow over the cycle and remove the arc
	     from consideration.  */
	  for (block = line->u.blocks; block; block = block->chain)
	    {
	      block_t *head = block;
	      arc_t *arc;

	    next_vertex:;
	      arc = head->succ;
	    current_vertex:;
	      while (arc)
		{
		  block_t *dst = arc->dst;
		  if (/* Already used that arc.  */
		      arc->cycle
		      /* Not to same graph, or before first vertex.  */
		      || dst->u.cycle.ident != ix
		      /* Already in path.  */
		      || dst->u.cycle.arc)
		    {
		      arc = arc->succ_next;
		      continue;
		    }

		  if (dst == block)
		    {
		      /* Found a closing arc.  */
		      gcov_type cycle_count = arc->cs_count;
		      arc_t *cycle_arc = arc;
		      arc_t *probe_arc;

		      /* Locate the smallest arc count of the loop.  */
		      for (dst = head; (probe_arc = dst->u.cycle.arc);
			   dst = probe_arc->src)
			if (cycle_count > probe_arc->cs_count)
			  {
			    cycle_count = probe_arc->cs_count;
			    cycle_arc = probe_arc;
			  }

		      count += cycle_count;
		      cycle_arc->cycle = 1;

		      /* Remove the flow from the cycle.  */
		      arc->cs_count -= cycle_count;
		      for (dst = head; (probe_arc = dst->u.cycle.arc);
			   dst = probe_arc->src)
			probe_arc->cs_count -= cycle_count;

		      /* Unwind to the cyclic arc.  */
		      while (head != cycle_arc->src)
			{
			  arc = head->u.cycle.arc;
			  head->u.cycle.arc = NULL;
			  head = arc->src;
			}
		      /* Move on.  */
		      arc = arc->succ_next;
		      continue;
		    }

		  /* Add new block to chain.  */
		  dst->u.cycle.arc = arc;
		  head = dst;
		  goto next_vertex;
		}
	      /* We could not add another vertex to the path. Remove
		 the last vertex from the list.  */
	      arc = head->u.cycle.arc;
	      if (arc)
		{
		  /* It was not the first vertex. Move onto next arc.  */
		  head->u.cycle.arc = NULL;
		  head = arc->src;
		  arc = arc->succ_next;
		  goto current_vertex;
		}
	      /* Mark this block as unusable.  */
	      block->u.cycle.ident = ~0U;
	    }

	  line->count = count;
	}

      if (line->exists)
	{
	  src->coverage.lines++;
	  if (line->count)
	    src->coverage.lines_executed++;
	}
    }
}