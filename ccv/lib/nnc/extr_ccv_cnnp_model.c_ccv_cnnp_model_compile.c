#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_21__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
struct TYPE_26__ {scalar_t__ graph; } ;
typedef  TYPE_4__ ccv_nnc_tensor_symbol_t ;
struct TYPE_27__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_5__ ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_t ;
struct TYPE_28__ {int const input_size; int output_size; TYPE_21__* compiled_data; scalar_t__ graph; int /*<<< orphan*/  outputs; int /*<<< orphan*/ * inputs; } ;
typedef  TYPE_6__ ccv_cnnp_model_t ;
struct TYPE_22__ {scalar_t__ sequences; } ;
struct TYPE_29__ {char prefix; TYPE_1__ sequence; TYPE_8__* ids; TYPE_8__* symbols; } ;
typedef  TYPE_7__ ccv_cnnp_model_add_to_array_context_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_compiled_data_t ;
struct TYPE_30__ {int rnum; } ;
typedef  TYPE_8__ ccv_array_t ;
struct TYPE_25__ {int /*<<< orphan*/  minimizer; } ;
struct TYPE_24__ {TYPE_8__* retainables; TYPE_8__* trainables; } ;
struct TYPE_23__ {int /*<<< orphan*/  loss; TYPE_3__ minimize; TYPE_2__ ids; TYPE_8__* retainables; TYPE_8__* trainables; int /*<<< orphan*/  stream_type; } ;

/* Variables and functions */
 int CCV_NNC_AUTOGEN_ALL_EXECS ; 
 int CCV_NNC_AUTOGEN_SOURCES_AND_DESTINATIONS ; 
 int /*<<< orphan*/  CCV_NNC_SIMPLIFY_COMMON_SUBEXPRESSION_ELIMINATION ; 
 int /*<<< orphan*/  CCV_NNC_SIMPLIFY_DATA_TRANSFER_OPT ; 
 int /*<<< orphan*/  CCV_NNC_SIMPLIFY_GRAPH_PRUNING ; 
 int /*<<< orphan*/  CCV_NNC_SIMPLIFY_OPS_FUSION ; 
 int /*<<< orphan*/  CCV_STREAM_CONTEXT_CPU ; 
 int /*<<< orphan*/  CCV_STREAM_CONTEXT_GPU ; 
 scalar_t__ CCV_TENSOR_GET_MEMORY (int /*<<< orphan*/ ) ; 
 scalar_t__ CCV_TENSOR_GPU_MEMORY ; 
 int /*<<< orphan*/  SYMBOLIC_GRAPH_DESTINATIONS (scalar_t__) ; 
 int /*<<< orphan*/  SYMBOLIC_GRAPH_PASSES (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOLIC_GRAPH_SOURCES (scalar_t__) ; 
 int /*<<< orphan*/  _ccv_cnnp_add_to_array ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_21__* cccalloc (int,int) ; 
 int /*<<< orphan*/ * ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_array_clear (scalar_t__) ; 
 int /*<<< orphan*/  ccv_array_free (scalar_t__) ; 
 scalar_t__ ccv_array_get (TYPE_8__* const,int) ; 
 TYPE_8__* ccv_array_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_cnnp_model_add_to_output (TYPE_6__* const,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ccv_cnnp_model_add_to_trainable (TYPE_6__* const,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ccv_cnnp_model_build (TYPE_6__* const,scalar_t__,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_autogen (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ccv_nnc_symbolic_graph_new () ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_simplify (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__ ccv_nnc_tensor_symbol_alias_to (scalar_t__,TYPE_4__ const) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_new (scalar_t__,TYPE_5__ const,int /*<<< orphan*/ ) ; 

void ccv_cnnp_model_compile(ccv_cnnp_model_t* const model, const ccv_nnc_tensor_param_t* const inputs, const int input_size, const ccv_nnc_cmd_t minimizer, const ccv_nnc_cmd_t loss)
{
	assert(input_size == model->input_size);
	if (!model->graph) // The graph is not compiled yet.
	{
		model->graph = ccv_nnc_symbolic_graph_new();
		model->inputs = ccmalloc(sizeof(ccv_nnc_tensor_symbol_t) * input_size);
		int i;
		for (i = 0; i < input_size; i++)
			model->inputs[i] = ccv_nnc_tensor_symbol_new(model->graph, inputs[i], 0);
		ccv_cnnp_model_build(model, model->graph, model->inputs, input_size, 0, 0);
		ccv_array_t* const trainables = ccv_array_new(sizeof(ccv_nnc_tensor_symbol_t), 0, 0);
		ccv_array_t* const trainable_ids = ccv_array_new(sizeof(char*), 0, 0);
		ccv_cnnp_model_add_to_array_context_t context = {
			.sequence = {},
			.prefix = 't',
			.symbols = trainables,
			.ids = trainable_ids,
		};
		ccv_cnnp_model_add_to_trainable(model, _ccv_cnnp_add_to_array, &context);
		// Assert no trainable is alias.
		for (i = 0; i < trainables->rnum; i++)
		{
			const ccv_nnc_tensor_symbol_t trainable = *(ccv_nnc_tensor_symbol_t*)ccv_array_get(trainables, i);
			const ccv_nnc_tensor_symbol_t alias_to = ccv_nnc_tensor_symbol_alias_to(trainable.graph, trainable);
			assert(alias_to.graph == 0); // Cannot find the one alias to.
		}
		ccv_array_t* const retainables = ccv_array_new(sizeof(ccv_nnc_tensor_symbol_t), 0, 0);
		ccv_array_t* const retainable_ids = ccv_array_new(sizeof(char*), 0, 0);
		if (context.sequence.sequences)
			ccv_array_clear(context.sequence.sequences);
		context.prefix = 'r';
		context.symbols = retainables;
		context.ids = retainable_ids;
		ccv_cnnp_model_add_to_output(model, _ccv_cnnp_add_to_array, &context);
		ccv_array_free(context.sequence.sequences);
		// Assert no retainable is alias.
		for (i = 0; i < retainables->rnum; i++)
		{
			const ccv_nnc_tensor_symbol_t retained = *(ccv_nnc_tensor_symbol_t*)ccv_array_get(retainables, i);
			const ccv_nnc_tensor_symbol_t alias_to = ccv_nnc_tensor_symbol_alias_to(retained.graph, retained);
			assert(alias_to.graph == 0); // Cannot find the one alias to.
		}
		ccv_nnc_graph_exec_symbol_autogen(model->graph, 0, 0, CCV_NNC_AUTOGEN_ALL_EXECS | CCV_NNC_AUTOGEN_SOURCES_AND_DESTINATIONS);
		ccv_nnc_symbolic_graph_simplify(model->graph,
			SYMBOLIC_GRAPH_PASSES(CCV_NNC_SIMPLIFY_COMMON_SUBEXPRESSION_ELIMINATION,
				CCV_NNC_SIMPLIFY_DATA_TRANSFER_OPT,
				CCV_NNC_SIMPLIFY_OPS_FUSION,
				CCV_NNC_SIMPLIFY_GRAPH_PRUNING),
			model->outputs, model->output_size,
			SYMBOLIC_GRAPH_SOURCES(model->graph), SYMBOLIC_GRAPH_DESTINATIONS(model->graph));
		int flag = 0;
		for (i = 0; !flag && i < input_size; i++)
			flag = (CCV_TENSOR_GET_MEMORY(inputs[i].type) == CCV_TENSOR_GPU_MEMORY);
		model->compiled_data = cccalloc(1, sizeof(ccv_cnnp_compiled_data_t) + sizeof(ccv_nnc_tensor_symbol_t) * (model->output_size - 1));
		// If inputs are from GPU, stream type is GPU.
		model->compiled_data->stream_type = flag ? CCV_STREAM_CONTEXT_GPU : CCV_STREAM_CONTEXT_CPU;
		model->compiled_data->trainables = trainables;
		model->compiled_data->retainables = retainables;
		model->compiled_data->ids.trainables = trainable_ids;
		model->compiled_data->ids.retainables = retainable_ids;
		model->compiled_data->minimize.minimizer = minimizer;
		model->compiled_data->loss = loss;
	}
}