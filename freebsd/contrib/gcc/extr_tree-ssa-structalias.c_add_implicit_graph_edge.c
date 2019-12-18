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
struct TYPE_5__ {int /*<<< orphan*/  num_implicit_edges; } ;
struct TYPE_4__ {scalar_t__* implicit_preds; } ;

/* Variables and functions */
 scalar_t__ BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_bit_p (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  bitmap_set_bit (scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  predbitmap_obstack ; 
 TYPE_2__ stats ; 

__attribute__((used)) static void
add_implicit_graph_edge (constraint_graph_t graph, unsigned int to,
			 unsigned int from)
{
  if (to == from)
    return;

  if (!graph->implicit_preds[to])
    graph->implicit_preds[to] = BITMAP_ALLOC (&predbitmap_obstack);

  if (!bitmap_bit_p (graph->implicit_preds[to], from))
    {
      stats.num_implicit_edges++;
      bitmap_set_bit (graph->implicit_preds[to], from);
    }
}