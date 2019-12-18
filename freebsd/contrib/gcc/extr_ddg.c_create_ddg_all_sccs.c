#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct ddg_all_sccs {int dummy; } ;
typedef  int /*<<< orphan*/  sbitmap ;
typedef  int /*<<< orphan*/  ddg_scc_ptr ;
typedef  TYPE_2__* ddg_ptr ;
typedef  TYPE_3__* ddg_node_ptr ;
typedef  TYPE_4__* ddg_edge_ptr ;
typedef  TYPE_5__* ddg_all_sccs_ptr ;
struct TYPE_16__ {scalar_t__ num_sccs; int /*<<< orphan*/ * sccs; TYPE_2__* ddg; } ;
struct TYPE_12__ {scalar_t__ count; } ;
struct TYPE_15__ {TYPE_1__ aux; TYPE_3__* dest; TYPE_3__* src; } ;
struct TYPE_14__ {int /*<<< orphan*/  cuid; } ;
struct TYPE_13__ {int num_nodes; int num_backarcs; TYPE_4__** backarcs; } ;

/* Variables and functions */
 scalar_t__ IN_SCC ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_scc_to_ddg (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_scc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ find_nodes_on_paths (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  order_sccs (TYPE_5__*) ; 
 int /*<<< orphan*/  sbitmap_alloc (int) ; 
 int /*<<< orphan*/  sbitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbitmap_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmalloc (int) ; 

ddg_all_sccs_ptr
create_ddg_all_sccs (ddg_ptr g)
{
  int i;
  int num_nodes = g->num_nodes;
  sbitmap from = sbitmap_alloc (num_nodes);
  sbitmap to = sbitmap_alloc (num_nodes);
  sbitmap scc_nodes = sbitmap_alloc (num_nodes);
  ddg_all_sccs_ptr sccs = (ddg_all_sccs_ptr)
			  xmalloc (sizeof (struct ddg_all_sccs));

  sccs->ddg = g;
  sccs->sccs = NULL;
  sccs->num_sccs = 0;

  for (i = 0; i < g->num_backarcs; i++)
    {
      ddg_scc_ptr  scc;
      ddg_edge_ptr backarc = g->backarcs[i];
      ddg_node_ptr src = backarc->src;
      ddg_node_ptr dest = backarc->dest;

      /* If the backarc already belongs to an SCC, continue.  */
      if (backarc->aux.count == IN_SCC)
	continue;

      sbitmap_zero (from);
      sbitmap_zero (to);
      SET_BIT (from, dest->cuid);
      SET_BIT (to, src->cuid);

      if (find_nodes_on_paths (scc_nodes, g, from, to))
	{
	  scc = create_scc (g, scc_nodes);
	  add_scc_to_ddg (sccs, scc);
	}
    }
  order_sccs (sccs);
  sbitmap_free (from);
  sbitmap_free (to);
  sbitmap_free (scc_nodes);
  return sccs;
}