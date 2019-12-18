#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_info_t ;
struct TYPE_6__ {TYPE_5__* exec_symbol_info; TYPE_5__* tensor_symbol_info; TYPE_5__* destinations; TYPE_5__* sources; } ;
typedef  TYPE_1__ ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_visit_t ;
typedef  int /*<<< orphan*/  const ccv_nnc_graph_exec_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_7__ {int const rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_graph_visit_free (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/ * ccv_nnc_graph_visit_new (TYPE_1__* const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_symbol_infer (TYPE_1__* const,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ccv_nnc_symbolic_graph_tensor_auto(ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_graph_exec_symbol_t* const sources, const int source_size, const ccv_nnc_graph_exec_symbol_t* const destinations, const int destination_size)
{
	assert((sources && source_size) || (!sources && !source_size));
	const ccv_nnc_graph_exec_symbol_t* const graph_sources = sources ? sources : (ccv_nnc_graph_exec_symbol_t*)ccv_array_get(graph->sources, 0);
	const int graph_source_size = source_size ? source_size : graph->sources->rnum;
	assert((destinations && destination_size) || (!destinations && !destination_size));
	const ccv_nnc_graph_exec_symbol_t* const graph_destinations = destinations ? destinations : (ccv_nnc_graph_exec_symbol_t*)ccv_array_get(graph->destinations, 0);
	const int graph_destination_size = destination_size ? destination_size : graph->destinations->rnum;
	ccv_nnc_graph_visit_t* const visit = ccv_nnc_graph_visit_new(graph, (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, 0), graph->exec_symbol_info->rnum, graph_sources, graph_source_size, graph_destinations, graph_destination_size, 0);
	ccv_nnc_symbolic_graph_symbol_infer(graph, visit, graph_sources, graph_source_size, graph_destinations, graph_destination_size, 0, 0, (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(graph->tensor_symbol_info, 0), (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, 0));
	ccv_nnc_graph_visit_free(visit);
}