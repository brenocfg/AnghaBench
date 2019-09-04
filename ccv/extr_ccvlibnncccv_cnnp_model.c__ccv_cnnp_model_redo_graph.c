#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  retainables; int /*<<< orphan*/  trainables; } ;
typedef  TYPE_1__ ccv_nnc_symbolic_graph_t ;
struct TYPE_19__ {int input_size; TYPE_1__* graph; int /*<<< orphan*/  output_size; int /*<<< orphan*/  outputs; int /*<<< orphan*/ * inputs; TYPE_1__* compiled_data; } ;
typedef  TYPE_2__ ccv_cnnp_model_t ;
typedef  TYPE_1__ ccv_cnnp_compiled_data_t ;

/* Variables and functions */
 int CCV_NNC_AUTOGEN_ALL_EXECS ; 
 int CCV_NNC_AUTOGEN_SOURCES_AND_DESTINATIONS ; 
 int /*<<< orphan*/  CCV_NNC_SIMPLIFY_COMMON_SUBEXPRESSION_ELIMINATION ; 
 int /*<<< orphan*/  CCV_NNC_SIMPLIFY_DATA_TRANSFER_OPT ; 
 int /*<<< orphan*/  CCV_NNC_SIMPLIFY_GRAPH_PRUNING ; 
 int /*<<< orphan*/  CCV_NNC_SIMPLIFY_OPS_FUSION ; 
 int /*<<< orphan*/  SYMBOLIC_GRAPH_DESTINATIONS (TYPE_1__*) ; 
 int /*<<< orphan*/  SYMBOLIC_GRAPH_PASSES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOLIC_GRAPH_SOURCES (TYPE_1__*) ; 
 int /*<<< orphan*/  _ccv_nnc_array_dedup_tensor_symbols (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ccv_array_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_cnnp_model_add_to_output (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_cnnp_model_add_to_trainable (TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_cnnp_model_build (TYPE_2__* const,TYPE_1__*,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_autogen (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_free (TYPE_1__* const) ; 
 TYPE_1__* ccv_nnc_symbolic_graph_new () ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_simplify (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_new (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_params (TYPE_1__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_cnnp_model_redo_graph(ccv_cnnp_model_t* const model)
{
	assert(model->graph);
	assert(model->compiled_data);
	ccv_cnnp_compiled_data_t* const compiled_data = model->compiled_data;
	ccv_nnc_symbolic_graph_t* const old_graph = model->graph;
	model->graph = ccv_nnc_symbolic_graph_new();
	const int input_size = model->input_size;
	int i;
	for (i = 0; i < input_size; i++)
		model->inputs[i] = ccv_nnc_tensor_symbol_new(model->graph, ccv_nnc_tensor_symbol_params(old_graph, model->inputs[i]), 0);
	// Only use the old graph to copy input parameters. Now we are done.
	ccv_nnc_symbolic_graph_free(old_graph);
	ccv_cnnp_model_build(model, model->graph, model->inputs, input_size, 0, 0);
	ccv_array_clear(compiled_data->trainables);
	ccv_cnnp_model_add_to_trainable(model, compiled_data->trainables);
	_ccv_nnc_array_dedup_tensor_symbols(compiled_data->trainables);
	ccv_array_clear(compiled_data->retainables);
	ccv_cnnp_model_add_to_output(model, compiled_data->retainables);
	_ccv_nnc_array_dedup_tensor_symbols(compiled_data->retainables);
	ccv_nnc_graph_exec_symbol_autogen(model->graph, 0, 0, CCV_NNC_AUTOGEN_ALL_EXECS | CCV_NNC_AUTOGEN_SOURCES_AND_DESTINATIONS);
	ccv_nnc_symbolic_graph_simplify(model->graph,
		SYMBOLIC_GRAPH_PASSES(CCV_NNC_SIMPLIFY_COMMON_SUBEXPRESSION_ELIMINATION,
			CCV_NNC_SIMPLIFY_DATA_TRANSFER_OPT,
			CCV_NNC_SIMPLIFY_OPS_FUSION,
			CCV_NNC_SIMPLIFY_GRAPH_PRUNING),
		model->outputs, model->output_size,
		SYMBOLIC_GRAPH_SOURCES(model->graph), SYMBOLIC_GRAPH_DESTINATIONS(model->graph));
}