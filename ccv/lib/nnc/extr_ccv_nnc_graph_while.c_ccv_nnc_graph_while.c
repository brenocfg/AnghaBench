#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_tensor_wraps_ref_t ;
struct TYPE_14__ {int p_idx; int exec_idx; TYPE_9__* sub_graphs; struct TYPE_14__* p; TYPE_9__* tensor_wraps_refs; TYPE_9__* exec_info; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;
struct TYPE_15__ {int d; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_t ;
struct TYPE_16__ {int graph_ref_size; int /*<<< orphan*/  flags; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_info_t ;
struct TYPE_17__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ const CCV_NNC_GRAPH_BACKWARD ; 
 int /*<<< orphan*/  CCV_NNC_GRAPH_EXEC_P_WHILE ; 
 scalar_t__ const CCV_NNC_GRAPH_FORWARD ; 
 int* CCV_NNC_GRAPH_REF (TYPE_3__*) ; 
 int /*<<< orphan*/  CMD_GENERIC () ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* const* ccv_array_get (TYPE_9__*,int) ; 
 void* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_9__*,TYPE_1__* const*) ; 
 int /*<<< orphan*/  ccv_nnc_cmd (scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ ccv_nnc_graph_exec_new (TYPE_1__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 

ccv_nnc_graph_exec_t ccv_nnc_graph_while(ccv_nnc_graph_t* const graph, const uint32_t cmd, ccv_nnc_graph_t* const while_graph)
{
	assert(cmd == CCV_NNC_GRAPH_FORWARD || cmd == CCV_NNC_GRAPH_BACKWARD);
	ccv_nnc_graph_exec_t while_exec = ccv_nnc_graph_exec_new(graph, ccv_nnc_cmd(cmd, 0, CMD_GENERIC(), 0), ccv_nnc_no_hint, 0, 0, 0, 0);
	ccv_nnc_graph_exec_info_t* while_exec_info = (ccv_nnc_graph_exec_info_t*)ccv_array_get(graph->exec_info, while_exec.d);
	while_exec_info->flags |= CCV_NNC_GRAPH_EXEC_P_WHILE;
	if (!graph->sub_graphs)
		graph->sub_graphs = ccv_array_new(sizeof(ccv_nnc_graph_t*), 1, 0);
	int i;
	if (while_graph->tensor_wraps_refs)
	{
		// Copy wraps from sub graph to parent graph.
		if (!graph->tensor_wraps_refs)
			graph->tensor_wraps_refs = ccv_array_new(sizeof(ccv_nnc_graph_tensor_wraps_ref_t), while_graph->tensor_wraps_refs->rnum, 0);
		for (i = 0; i < while_graph->tensor_wraps_refs->rnum; i++)
			ccv_array_push(graph->tensor_wraps_refs, ccv_array_get(while_graph->tensor_wraps_refs, i));
	}
	ccv_array_push(graph->sub_graphs, &while_graph);
	while_graph->p = graph;
	while_graph->p_idx = graph->sub_graphs->rnum;
	while_graph->exec_idx = while_exec.d + 1;
	while_exec_info->graph_ref_size = 1;
	CCV_NNC_GRAPH_REF(while_exec_info)[0] = graph->sub_graphs->rnum;
	return while_exec;
}