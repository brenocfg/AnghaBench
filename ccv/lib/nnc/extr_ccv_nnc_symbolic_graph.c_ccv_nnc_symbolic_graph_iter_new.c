#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_6__* exec_symbol_info; TYPE_6__* destinations; TYPE_6__* sources; } ;
typedef  TYPE_1__ ccv_nnc_symbolic_graph_t ;
struct TYPE_8__ {int idx; int /*<<< orphan*/  visit; TYPE_1__* graph; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_iter_t ;
typedef  int /*<<< orphan*/  const ccv_nnc_graph_exec_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_9__ {int const rnum; } ;

/* Variables and functions */
 scalar_t__ cccalloc (int,int) ; 
 scalar_t__ ccv_array_get (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_graph_visit_new (TYPE_1__ const* const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ ) ; 

ccv_nnc_symbolic_graph_iter_t* ccv_nnc_symbolic_graph_iter_new(const ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_graph_exec_symbol_t* const sources, const int source_size, const ccv_nnc_graph_exec_symbol_t* const destinations, const int destination_size)
{
	const ccv_nnc_graph_exec_symbol_t* const graph_sources = sources ? sources : (ccv_nnc_graph_exec_symbol_t*)ccv_array_get(graph->sources, 0);
	const int graph_source_size = source_size ? source_size : graph->sources->rnum;
	const ccv_nnc_graph_exec_symbol_t* const graph_destinations = destinations ? destinations : (ccv_nnc_graph_exec_symbol_t*)ccv_array_get(graph->destinations, 0);
	const int graph_destination_size = destination_size ? destination_size : graph->destinations->rnum;
	ccv_nnc_symbolic_graph_iter_t* const iter = (ccv_nnc_symbolic_graph_iter_t*)cccalloc(1, sizeof(ccv_nnc_symbolic_graph_iter_t));
	iter->idx = -1;
	iter->graph = graph;
	iter->visit = ccv_nnc_graph_visit_new(graph, (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, 0), graph->exec_symbol_info->rnum, graph_sources, graph_source_size, graph_destinations, graph_destination_size, 0);
	return iter;
}