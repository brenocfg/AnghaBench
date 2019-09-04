#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_4__* exec_symbol_info; int /*<<< orphan*/  tensor_symbol_info; int /*<<< orphan*/  sub_graphs; } ;
typedef  TYPE_1__ ccv_nnc_symbolic_graph_t ;
struct TYPE_8__ {scalar_t__ graph_ref_size; TYPE_4__* outgoings; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_9__ {int rnum; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CCV_NNC_GRAPH_EXEC_IS_DEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_dot_node (TYPE_2__ const* const,int,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_dot_sub_graphs (TYPE_2__ const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  ccfree (int*) ; 
 scalar_t__ ccmalloc (int) ; 
 scalar_t__ ccv_array_get (TYPE_4__*,int const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

void ccv_nnc_symbolic_graph_dot(const ccv_nnc_symbolic_graph_t* const graph, const int flags, FILE* out)
{
	fputs("digraph G {\ncompound=true;\n", out);
	int i, j;
	int c = 0;
	int* node_id = (int*)ccmalloc(sizeof(int) * graph->exec_symbol_info->rnum);
	// Output styles.
	for (i = 0; i < graph->exec_symbol_info->rnum; i++)
	{
		node_id[i] = c;
		const ccv_nnc_graph_exec_symbol_info_t* const exec_symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, i);
		// Skip the dead one.
		if (CCV_NNC_GRAPH_EXEC_IS_DEAD(exec_symbol_info->flags))
			continue;
		if (exec_symbol_info->graph_ref_size)
			_ccv_nnc_symbolic_graph_dot_sub_graphs(exec_symbol_info, graph->tensor_symbol_info, graph->sub_graphs, flags, out, &c);
		else {
			_ccv_nnc_symbolic_graph_dot_node(exec_symbol_info, c, graph->tensor_symbol_info, flags, out);
			++c;
		}
	}
	// Output connections.
	for (i = 0; i < graph->exec_symbol_info->rnum; i++)
	{
		const ccv_nnc_graph_exec_symbol_info_t* exec_symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, i);
		// Skip the dead one.
		if (CCV_NNC_GRAPH_EXEC_IS_DEAD(exec_symbol_info->flags))
			continue;
		if (exec_symbol_info->outgoings)
			for (j = 0; j < exec_symbol_info->outgoings->rnum; j++)
			{
				const int outgoing_idx = *(int*)ccv_array_get(exec_symbol_info->outgoings, j);
				const ccv_nnc_graph_exec_symbol_info_t* const outgoing_symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, outgoing_idx);
				// If both are sub-graphs, have both tail and head specified.
				if (exec_symbol_info->graph_ref_size && outgoing_symbol_info->graph_ref_size)
					fprintf(out, "node%d -> node%d [ltail=cluster%d,lhead=cluster%d];\n", node_id[i], node_id[outgoing_idx], node_id[i], node_id[outgoing_idx]);
				else if (exec_symbol_info->graph_ref_size && !outgoing_symbol_info->graph_ref_size)
					fprintf(out, "node%d -> node%d [ltail=cluster%d];\n", node_id[i], node_id[outgoing_idx], node_id[i]);
				else if (!exec_symbol_info->graph_ref_size && outgoing_symbol_info->graph_ref_size)
					fprintf(out, "node%d -> node%d [lhead=cluster%d];\n", node_id[i], node_id[outgoing_idx], node_id[outgoing_idx]);
				else
					fprintf(out, "node%d -> node%d;\n", node_id[i], node_id[outgoing_idx]);
			}
	}
	fputs("}\n", out);
	ccfree(node_id);
}