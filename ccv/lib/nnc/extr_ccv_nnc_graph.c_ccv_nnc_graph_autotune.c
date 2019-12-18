#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_3__* exec_info; TYPE_3__* destinations; TYPE_3__* sources; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;
typedef  int /*<<< orphan*/  const ccv_nnc_graph_exec_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_info_t ;
struct TYPE_6__ {int const rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NNC_GRAPH_VISIT (TYPE_1__* const,int /*<<< orphan*/ *,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visitor ; 

void ccv_nnc_graph_autotune(ccv_nnc_graph_t* const graph, const size_t max_workspace_size, const int flags, const ccv_nnc_graph_exec_t* const sources, const int source_size, const ccv_nnc_graph_exec_t* const destinations, const int destination_size)
{
	// exec current node, for synchronous CPU execution, no stream unit.
	int i;
#define visitor(node, idx, ...) \
	do { \
		if (node->cmd.cmd == CCV_NNC_NOOP) \
			continue; \
		if (node->cmd.cmd == CCV_NNC_GRAPH_FORWARD || node->cmd.cmd == CCV_NNC_GRAPH_BACKWARD) \
			for (i = 0; i < node->graph_ref_size; i++) \
			{ \
				ccv_nnc_graph_t* sub_graph = *(ccv_nnc_graph_t**)ccv_array_get(graph->sub_graphs, CCV_NNC_GRAPH_REF(node)[i] - 1); \
				ccv_nnc_graph_autotune(sub_graph, max_workspace_size, flags, 0, 0, 0, 0); \
			} \
		else { \
			/* Need to unwrap these tensors */ \
			for (i = 0; i < node->input_size + node->output_size; i++) \
				if (node->inputs[i] && CCV_IS_TENSOR_MULTIVIEW(node->inputs[i])) \
					node->inputs[i] = _ccv_nnc_any_tensor_from_tensor_multiview((ccv_nnc_tensor_multiview_t*)node->inputs[i]); \
			PRINT(CCV_CLI_VERBOSE, "%s [%d]: [%d] -> [%d]\n", ccv_nnc_cmd_name(node->cmd.cmd), idx, node->input_size, node->output_size); \
			for (i = 0; i < node->input_size; i++) \
				PRINT(CCV_CLI_VERBOSE, "|-> %d. %p (%p)\n", i + 1, node->inputs[i], (node->inputs[i] ? node->inputs[i]->data.u8 : 0)); \
			for (i = 0; i < node->output_size; i++) \
				PRINT(CCV_CLI_VERBOSE, "|<- %d. %p (%p)\n", i + 1, node->outputs[i], (node->outputs[i] ? node->outputs[i]->data.u8 : 0)); \
			node->cmd = ccv_nnc_cmd_autotune(node->cmd, max_workspace_size, node->hint, flags, node->inputs, node->input_size, node->outputs, node->output_size, 0); \
		} \
	} while (0)
	const ccv_nnc_graph_exec_t* const graph_sources = sources ? sources : (graph->sources ? (ccv_nnc_graph_exec_t*)ccv_array_get(graph->sources, 0): 0);
	const int graph_source_size = source_size ? source_size : (graph->sources ? graph->sources->rnum : 0);
	const ccv_nnc_graph_exec_t* const graph_destinations = destinations ? destinations : (graph->destinations ? (ccv_nnc_graph_exec_t*)ccv_array_get(graph->destinations, 0) : 0);
	const int graph_destination_size = destination_size ? destination_size : (graph->destinations ? graph->destinations->rnum : 0);
	CCV_NNC_GRAPH_VISIT(graph, (ccv_nnc_graph_exec_info_t*)ccv_array_get(graph->exec_info, 0), graph->exec_info->rnum, graph_sources, graph_source_size, graph_destinations, graph_destination_size, 0, visitor);
#undef visitor
}