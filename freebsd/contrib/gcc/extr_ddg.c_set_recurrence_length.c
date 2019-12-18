#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ddg_scc_ptr ;
typedef  int /*<<< orphan*/  ddg_ptr ;
typedef  TYPE_2__* ddg_node_ptr ;
typedef  TYPE_3__* ddg_edge_ptr ;
struct TYPE_7__ {int distance; scalar_t__ latency; TYPE_2__* src; TYPE_2__* dest; } ;
struct TYPE_6__ {int /*<<< orphan*/  cuid; } ;
struct TYPE_5__ {int num_backarcs; int recurrence_length; int /*<<< orphan*/  nodes; TYPE_3__** backarcs; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int longest_simple_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_recurrence_length (ddg_scc_ptr scc, ddg_ptr g)
{
  int j;
  int result = -1;

  for (j = 0; j < scc->num_backarcs; j++)
    {
      ddg_edge_ptr backarc = scc->backarcs[j];
      int length;
      int distance = backarc->distance;
      ddg_node_ptr src = backarc->dest;
      ddg_node_ptr dest = backarc->src;

      length = longest_simple_path (g, src->cuid, dest->cuid, scc->nodes);
      if (length < 0 )
	{
	  /* fprintf (stderr, "Backarc not on simple cycle in SCC.\n"); */
	  continue;
	}
      length += backarc->latency;
      result = MAX (result, (length / distance));
    }
  scc->recurrence_length = result;
}