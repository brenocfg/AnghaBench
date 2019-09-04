#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_3__ const* const exec_symbol_info; TYPE_3__* tensor_symbol_info; TYPE_3__* sub_graphs; } ;
typedef  TYPE_1__ ccv_nnc_symbolic_graph_t ;
struct TYPE_17__ {int flags; int graph_ref_size; TYPE_3__ const* const outgoings; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_18__ {int rnum; } ;
typedef  TYPE_3__ ccv_array_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int CCV_NNC_GRAPH_EXEC_CASE_OF ; 
 scalar_t__ CCV_NNC_GRAPH_EXEC_IS_DEAD (int) ; 
 int CCV_NNC_GRAPH_EXEC_P_WHILE ; 
 int const* CCV_NNC_GRAPH_REF (TYPE_2__ const* const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_dot_case_of_label (TYPE_2__ const* const,int,TYPE_3__ const* const,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_dot_node (TYPE_2__ const* const,int,TYPE_3__*,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_dot_while_label (TYPE_2__ const* const,int,TYPE_3__ const* const,TYPE_1__ const* const,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccfree (int*) ; 
 scalar_t__ ccmalloc (int) ; 
 scalar_t__ ccv_array_get (TYPE_3__ const* const,int const) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_dot_sub_graphs(const ccv_nnc_graph_exec_symbol_info_t* const exec_symbol_info, const ccv_array_t* const tensor_symbol_info, const ccv_array_t* const sub_graphs, const int flags, FILE* out, int* c)
{
	int i, j, k;
	// Output this node info within this subgraph.
	if (exec_symbol_info->flags & CCV_NNC_GRAPH_EXEC_P_WHILE)
	{
		fprintf(out, "subgraph cluster%d {\nstyle=\"rounded\";\nnode%d [style=invisible];\nlabel=<", *c, *c);
		const ccv_nnc_symbolic_graph_t* const while_graph = *(ccv_nnc_symbolic_graph_t**)ccv_array_get(sub_graphs, CCV_NNC_GRAPH_REF(exec_symbol_info)[0] - 1);
		_ccv_nnc_symbolic_graph_dot_while_label(exec_symbol_info, *c, tensor_symbol_info, while_graph, flags, out);
	} else if (exec_symbol_info->flags & CCV_NNC_GRAPH_EXEC_CASE_OF) {
		fprintf(out, "subgraph cluster%d {\nstyle=\"rounded\";\nnode%d [style=invisible];\nlabel=<", *c, *c);
		_ccv_nnc_symbolic_graph_dot_case_of_label(exec_symbol_info, *c, tensor_symbol_info, flags, out);
	}
	fputs(">;\n", out);
	++(*c);
	for (k = 0; k < exec_symbol_info->graph_ref_size; k++)
	{
		if (exec_symbol_info->flags & CCV_NNC_GRAPH_EXEC_CASE_OF)
		{
			fprintf(out, "subgraph cluster%d {\nstyle=\"rounded\";\nnode%d [style=invisible];\nlabel=\"\"\n", *c, *c);
			++(*c);
		}
		const ccv_nnc_symbolic_graph_t* const graph = *(ccv_nnc_symbolic_graph_t**)ccv_array_get(sub_graphs, CCV_NNC_GRAPH_REF(exec_symbol_info)[k] - 1);
		int* node_id = (int*)ccmalloc(sizeof(int) * graph->exec_symbol_info->rnum);
		for (i = 0; i < graph->exec_symbol_info->rnum; i++)
		{
			node_id[i] = *c;
			const ccv_nnc_graph_exec_symbol_info_t* const exec_symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, i);
			// Skip the dead one.
			if (CCV_NNC_GRAPH_EXEC_IS_DEAD(exec_symbol_info->flags))
				continue;
			if (exec_symbol_info->graph_ref_size)
				_ccv_nnc_symbolic_graph_dot_sub_graphs(exec_symbol_info, graph->tensor_symbol_info, graph->sub_graphs, flags, out, c);
			else {
				_ccv_nnc_symbolic_graph_dot_node(exec_symbol_info, *c, graph->tensor_symbol_info, flags, out);
				++(*c);
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
					if (CCV_NNC_GRAPH_REF(exec_symbol_info)[0] && CCV_NNC_GRAPH_REF(outgoing_symbol_info)[0])
						fprintf(out, "node%d -> node%d [ltail=cluster%d,lhead=cluster%d];\n", node_id[i], node_id[outgoing_idx], node_id[i], node_id[outgoing_idx]);
					else if (CCV_NNC_GRAPH_REF(exec_symbol_info)[0] && !CCV_NNC_GRAPH_REF(outgoing_symbol_info)[0])
						fprintf(out, "node%d -> node%d [ltail=cluster%d];\n", node_id[i], node_id[outgoing_idx], node_id[i]);
					else if (!CCV_NNC_GRAPH_REF(exec_symbol_info)[0] && CCV_NNC_GRAPH_REF(outgoing_symbol_info)[0])
						fprintf(out, "node%d -> node%d [lhead=cluster%d];\n", node_id[i], node_id[outgoing_idx], node_id[outgoing_idx]);
					else
						fprintf(out, "node%d -> node%d;\n", node_id[i], node_id[outgoing_idx]);
				}
		}
		fputs("}\n", out);
		ccfree(node_id);
	}
	// Extra subgraph cluster.
	if (exec_symbol_info->flags & CCV_NNC_GRAPH_EXEC_CASE_OF)
		fputs("}\n", out);
}