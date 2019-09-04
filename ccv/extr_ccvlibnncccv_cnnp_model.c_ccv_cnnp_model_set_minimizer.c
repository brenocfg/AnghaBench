#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/ * graph_exec_arena; TYPE_4__* update_nodes; TYPE_1__* trainables; int /*<<< orphan*/  parallel_count; int /*<<< orphan*/  minimizer; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_t ;
struct TYPE_20__ {int /*<<< orphan*/  graph; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_t ;
struct TYPE_21__ {scalar_t__ graph; } ;
typedef  TYPE_4__ ccv_nnc_graph_exec_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_arena_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_t ;
struct TYPE_22__ {TYPE_2__* graph; TYPE_2__* compiled_data; } ;
typedef  TYPE_5__ ccv_cnnp_model_t ;
typedef  TYPE_2__ ccv_cnnp_compiled_data_t ;
struct TYPE_18__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NO_GRAPH_EXEC (TYPE_3__ const) ; 
 int /*<<< orphan*/  assert (TYPE_2__* const) ; 
 int ccv_max (int /*<<< orphan*/ ,int) ; 
 TYPE_3__ ccv_nnc_graph_exec_from_symbol (int /*<<< orphan*/ * const,TYPE_4__) ; 
 int /*<<< orphan*/  ccv_nnc_graph_exec_set (int /*<<< orphan*/ ,TYPE_3__ const,int /*<<< orphan*/  const) ; 
 TYPE_4__ ccv_nnc_graph_exec_symbol_copy (TYPE_2__* const,TYPE_4__,int) ; 
 int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_set (TYPE_2__* const,TYPE_4__,int /*<<< orphan*/  const) ; 

void ccv_cnnp_model_set_minimizer(ccv_cnnp_model_t* const model, const ccv_nnc_cmd_t minimizer)
{
	ccv_cnnp_compiled_data_t* const compiled_data = model->compiled_data;
	assert(compiled_data);
	compiled_data->minimizer = minimizer;
	const int parallel_count = ccv_max(compiled_data->parallel_count, 1);
	if (compiled_data->update_nodes)
	{
		int i, j;
		const int trainable_size = compiled_data->trainables->rnum;
		ccv_nnc_graph_exec_symbol_t* const update_nodes = compiled_data->update_nodes;
		ccv_nnc_symbolic_graph_t* const symbolic_graph = model->graph;
		assert(symbolic_graph);
		ccv_nnc_graph_exec_arena_t* const graph_exec_arena = compiled_data->graph_exec_arena;
		for (i = 0; i < trainable_size; i++)
		{
			ccv_nnc_graph_exec_symbol_set(symbolic_graph, update_nodes[i], minimizer);
			ccv_nnc_graph_exec_t const update_exec = ccv_nnc_graph_exec_from_symbol(graph_exec_arena, update_nodes[i]);
			if (!CCV_NO_GRAPH_EXEC(update_exec))
				ccv_nnc_graph_exec_set(update_exec.graph, update_exec, minimizer);
			for (j = 1; j < parallel_count; j++)
			{
				ccv_nnc_graph_exec_symbol_t copy_symbol = ccv_nnc_graph_exec_symbol_copy(symbolic_graph, update_nodes[i], j);
				if (copy_symbol.graph)
					ccv_nnc_graph_exec_symbol_set(symbolic_graph, copy_symbol, minimizer);
				const ccv_nnc_graph_exec_t copy = ccv_nnc_graph_exec_from_symbol(graph_exec_arena, copy_symbol);
				if (!CCV_NO_GRAPH_EXEC(copy))
					ccv_nnc_graph_exec_set(copy.graph, copy, minimizer);
			}
		}
	}
}