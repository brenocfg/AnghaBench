#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* edge ;
typedef  scalar_t__ basic_block ;
struct TYPE_6__ {int flags; TYPE_1__* dest; } ;
struct TYPE_5__ {scalar_t__ prev_bb; } ;

/* Variables and functions */
 int EDGE_CROSSING ; 
 scalar_t__ flag_reorder_blocks_and_partition ; 

__attribute__((used)) static bool
better_edge_p (basic_block bb, edge e, int prob, int freq, int best_prob,
	       int best_freq, edge cur_best_edge)
{
  bool is_better_edge;

  /* The BEST_* values do not have to be best, but can be a bit smaller than
     maximum values.  */
  int diff_prob = best_prob / 10;
  int diff_freq = best_freq / 10;

  if (prob > best_prob + diff_prob)
    /* The edge has higher probability than the temporary best edge.  */
    is_better_edge = true;
  else if (prob < best_prob - diff_prob)
    /* The edge has lower probability than the temporary best edge.  */
    is_better_edge = false;
  else if (freq < best_freq - diff_freq)
    /* The edge and the temporary best edge  have almost equivalent
       probabilities.  The higher frequency of a successor now means
       that there is another edge going into that successor.
       This successor has lower frequency so it is better.  */
    is_better_edge = true;
  else if (freq > best_freq + diff_freq)
    /* This successor has higher frequency so it is worse.  */
    is_better_edge = false;
  else if (e->dest->prev_bb == bb)
    /* The edges have equivalent probabilities and the successors
       have equivalent frequencies.  Select the previous successor.  */
    is_better_edge = true;
  else
    is_better_edge = false;

  /* If we are doing hot/cold partitioning, make sure that we always favor
     non-crossing edges over crossing edges.  */

  if (!is_better_edge
      && flag_reorder_blocks_and_partition
      && cur_best_edge
      && (cur_best_edge->flags & EDGE_CROSSING)
      && !(e->flags & EDGE_CROSSING))
    is_better_edge = true;

  return is_better_edge;
}