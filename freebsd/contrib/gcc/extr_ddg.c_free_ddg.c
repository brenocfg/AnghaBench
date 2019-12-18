#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ddg_ptr ;
typedef  TYPE_1__* ddg_edge_ptr ;
struct TYPE_5__ {int num_nodes; scalar_t__ num_backarcs; struct TYPE_5__* nodes; struct TYPE_5__* backarcs; int /*<<< orphan*/  predecessors; int /*<<< orphan*/  successors; struct TYPE_5__* next_out; struct TYPE_5__* out; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 

void
free_ddg (ddg_ptr g)
{
  int i;

  if (!g)
    return;

  for (i = 0; i < g->num_nodes; i++)
    {
      ddg_edge_ptr e = g->nodes[i].out;

      while (e)
	{
	  ddg_edge_ptr next = e->next_out;

	  free (e);
	  e = next;
	}
      sbitmap_free (g->nodes[i].successors);
      sbitmap_free (g->nodes[i].predecessors);
    }
  if (g->num_backarcs > 0)
    free (g->backarcs);
  free (g->nodes);
  free (g);
}