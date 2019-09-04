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
struct TYPE_5__ {TYPE_3__* exec_info; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NNC_GRAPH_VISIT (TYPE_1__* const,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visitor ; 

void ccv_nnc_graph_autotune(ccv_nnc_graph_t* const graph, const size_t max_workspace_size, const int flags, const ccv_nnc_graph_exec_t* const sources, const int source_size, const ccv_nnc_graph_exec_t* const destinations, const int destination_size)
{
	// exec current node, for synchronous CPU execution, no stream unit.
#define visitor(node, idx, ...) \
	do { \
		node->cmd = ccv_nnc_cmd_autotune(node->cmd, max_workspace_size, node->hint, flags, node->inputs, node->input_size, node->outputs, node->output_size, 0); \
	} while (0)
	CCV_NNC_GRAPH_VISIT(graph, (ccv_nnc_graph_exec_info_t*)ccv_array_get(graph->exec_info, 0), graph->exec_info->rnum, sources, source_size, destinations, destination_size, 0, visitor);
#undef visitor
}