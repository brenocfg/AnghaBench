#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_6__* s_ref; TYPE_4__* const name; } ;
typedef  TYPE_3__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_10__ {TYPE_4__* const exec_symbol_idx; TYPE_4__* const tensor_symbol_idx; } ;
struct TYPE_9__ {TYPE_4__* const tensor_symbol_idx; } ;
struct TYPE_12__ {TYPE_2__ data_parallel; TYPE_1__ backward; TYPE_6__* exec_symbol_info; TYPE_6__* tensor_symbol_info; struct TYPE_12__* const breakpoints; TYPE_6__* destinations; TYPE_6__* sources; TYPE_6__* sub_graphs; } ;
typedef  TYPE_4__ ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_13__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_graph_exec_symbol_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccfree (TYPE_4__* const) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_6__*) ; 
 scalar_t__ ccv_array_get (TYPE_6__*,int) ; 

void ccv_nnc_symbolic_graph_free(ccv_nnc_symbolic_graph_t* const graph)
{
	int i;
	for (i = 0; i < graph->exec_symbol_info->rnum; i++)
		_ccv_nnc_graph_exec_symbol_free((ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, i), 0);
	for (i = 0; i < graph->tensor_symbol_info->rnum; i++)
	{
		ccv_nnc_tensor_symbol_info_t* const symbol_info = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(graph->tensor_symbol_info, i);
		if (symbol_info->name)
			ccfree(symbol_info->name);
		if (symbol_info->s_ref)
			ccv_array_free(symbol_info->s_ref);
	}
	if (graph->sub_graphs)
	{
		for (i = 0; i < graph->sub_graphs->rnum; i++)
			ccv_nnc_symbolic_graph_free(*(ccv_nnc_symbolic_graph_t**)ccv_array_get(graph->sub_graphs, i));
		ccv_array_free(graph->sub_graphs);
	}
	if (graph->sources)
		ccv_array_free(graph->sources);
	if (graph->destinations)
		ccv_array_free(graph->destinations);
	if (graph->breakpoints)
		ccfree(graph->breakpoints);
	ccv_array_free(graph->tensor_symbol_info);
	ccv_array_free(graph->exec_symbol_info);
	if (graph->backward.tensor_symbol_idx)
		ccfree(graph->backward.tensor_symbol_idx);
	if (graph->data_parallel.tensor_symbol_idx)
		ccfree(graph->data_parallel.tensor_symbol_idx);
	if (graph->data_parallel.exec_symbol_idx)
		ccfree(graph->data_parallel.exec_symbol_idx);
	ccfree(graph);
}