#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ (* conflict_graph_enum_fn ) (int /*<<< orphan*/ ,int,void*) ;
typedef  TYPE_1__* conflict_graph_arc ;
typedef  TYPE_2__* conflict_graph ;
struct TYPE_5__ {TYPE_1__** neighbor_heads; } ;
struct TYPE_4__ {int larger; struct TYPE_4__* larger_next; struct TYPE_4__* smaller_next; int /*<<< orphan*/  smaller; } ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,void*) ; 

void
conflict_graph_enum (conflict_graph graph, int reg,
		     conflict_graph_enum_fn enum_fn, void *extra)
{
  conflict_graph_arc arc = graph->neighbor_heads[reg];
  while (arc != NULL)
    {
      /* Invoke the callback.  */
      if ((*enum_fn) (arc->smaller, arc->larger, extra))
	/* Stop if requested.  */
	break;
      
      /* Which next pointer to follow depends on whether REG is the
	 smaller or larger reg in this conflict.  */
      if (reg < arc->larger)
	arc = arc->smaller_next;
      else
	arc = arc->larger_next;
    }
}