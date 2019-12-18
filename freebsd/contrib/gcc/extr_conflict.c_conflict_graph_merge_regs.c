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
typedef  TYPE_1__* conflict_graph_arc ;
typedef  TYPE_2__* conflict_graph ;
struct TYPE_6__ {TYPE_1__** neighbor_heads; } ;
struct TYPE_5__ {int smaller; int larger; struct TYPE_5__* larger_next; struct TYPE_5__* smaller_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  conflict_graph_add (TYPE_2__*,int,int) ; 

void
conflict_graph_merge_regs (conflict_graph graph, int target, int src)
{
  conflict_graph_arc arc = graph->neighbor_heads[src];

  if (target == src)
    return;

  while (arc != NULL)
    {
      int other = arc->smaller;

      if (other == src)
	other = arc->larger;

      conflict_graph_add (graph, target, other);

      /* Which next pointer to follow depends on whether REG is the
	 smaller or larger reg in this conflict.  */
      if (src < arc->larger)
	arc = arc->smaller_next;
      else
	arc = arc->larger_next;
    }
}