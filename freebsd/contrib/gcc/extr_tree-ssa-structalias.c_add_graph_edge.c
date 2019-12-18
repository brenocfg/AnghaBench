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
typedef  TYPE_1__* constraint_graph_t ;
struct TYPE_5__ {int /*<<< orphan*/  num_edges; } ;
struct TYPE_4__ {scalar_t__* succs; } ;

/* Variables and functions */
 scalar_t__ BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 unsigned int FIRST_REF_NODE ; 
 int /*<<< orphan*/  bitmap_bit_p (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set_bit (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  pta_obstack ; 
 TYPE_2__ stats ; 

__attribute__((used)) static bool
add_graph_edge (constraint_graph_t graph, unsigned int to,
		unsigned int from)
{
  if (to == from)
    {
      return false;
    }
  else
    {
      bool r = false;

      if (!graph->succs[from])
	graph->succs[from] = BITMAP_ALLOC (&pta_obstack);
      if (!bitmap_bit_p (graph->succs[from], to))
	{
	  r = true;
	  if (to < FIRST_REF_NODE && from < FIRST_REF_NODE)
	    stats.num_edges++;
	  bitmap_set_bit (graph->succs[from], to);
	}
      return r;
    }
}