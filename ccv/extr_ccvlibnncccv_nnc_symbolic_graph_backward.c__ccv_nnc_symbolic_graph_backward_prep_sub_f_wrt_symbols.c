#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_17__ {int const d; TYPE_3__ const* const graph; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_t ;
struct TYPE_18__ {int assign_ref; TYPE_5__ const* const s_ref; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_19__ {TYPE_5__ const* const tensor_symbol_info; } ;
typedef  TYPE_3__ ccv_nnc_symbolic_graph_t ;
struct TYPE_20__ {int /*<<< orphan*/  input_size; int /*<<< orphan*/  output_size; } ;
typedef  TYPE_4__ ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_21__ {int const rnum; } ;
typedef  TYPE_5__ const ccv_array_t ;

/* Variables and functions */
 TYPE_1__ NO_TENSOR_SYMBOL ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_backward_exec_io (TYPE_4__ const* const,int**,int**,int*,int*) ; 
 int /*<<< orphan*/  ccv_array_clear (TYPE_5__ const* const) ; 
 scalar_t__ ccv_array_get (TYPE_5__ const* const,int const) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_5__ const* const,TYPE_1__*) ; 
 int ccv_max (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_backward_prep_sub_f_wrt_symbols(const ccv_nnc_graph_exec_symbol_info_t* const forw_exec, const ccv_nnc_symbolic_graph_t* const sub_graph, const int graph_ref, const ccv_nnc_tensor_symbol_info_t* const tensor_symbol_info, const uint64_t* const input_bitmasks, const uint64_t* const output_bitmasks, ccv_array_t* const sub_f_symbols, ccv_array_t* const sub_wrt_symbols)
{
	int i, j;
	ccv_array_clear(sub_wrt_symbols);
	int forw_outputs[ccv_max(1, forw_exec->output_size)];
	int forw_inputs[ccv_max(1, forw_exec->input_size)];
	int* back_input_map = forw_outputs;
	int* back_output_map = forw_inputs;
	int back_input_size, back_output_size;
	_ccv_nnc_symbolic_graph_backward_exec_io(forw_exec, &back_input_map, &back_output_map, &back_input_size, &back_output_size);
	for (i = 0; i < back_output_size; i++)
		if (output_bitmasks[i >> 6] & ((uint64_t)1 << (i & 63)))
		{
			const int d = back_output_map[i];
			const ccv_array_t* const s_refs = tensor_symbol_info[d].s_ref;
			const int s_ref = s_refs && s_refs->rnum > graph_ref ? *(int*)ccv_array_get(s_refs, graph_ref) - 1 : -1;
			if (s_ref >= 0)
			{
				ccv_nnc_tensor_symbol_t sub_wrt_symbol = {
					.d = s_ref,
					.graph = sub_graph,
				};
				ccv_array_push(sub_wrt_symbols, &sub_wrt_symbol);
			} else
				ccv_array_push(sub_wrt_symbols, &NO_TENSOR_SYMBOL);
		}
	ccv_array_clear(sub_f_symbols);
	for (i = 0; i < back_input_size; i++)
		if (input_bitmasks[i >> 6] & ((uint64_t)1 << (i & 63)))
		{
			const int d = back_input_map[i];
			ccv_nnc_tensor_symbol_t sub_f_symbol = {
				.d = *(int*)ccv_array_get(tensor_symbol_info[d].s_ref, graph_ref) - 1,
				.graph = sub_graph,
			};
			ccv_array_push(sub_f_symbols, &sub_f_symbol);
		}
	// Go through all its assignments (parameterized loop), making them either wrt or f.
	// The reason is these must flow through the graph, otherwise we cannot form a full
	// enclosed loop. Also because they are the additional f / wrt symbols, there is
	// no case that we cannot find their corresponding gradients in the backward sub graphs
	// (these gradients have to be parameterized to form an enclosed loop as well).
	for (i = 0; i < sub_graph->tensor_symbol_info->rnum; i++)
	{
		const ccv_nnc_tensor_symbol_info_t* const tensor_symbol_info = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(sub_graph->tensor_symbol_info, i);
		if (tensor_symbol_info->assign_ref)
		{
			const int assign_ref = tensor_symbol_info->assign_ref - 1;
			// i is the wrt, assign_ref is the f.
			int flag = 0;
			for (j = 0; !flag && j < sub_wrt_symbols->rnum; j++)
				flag = (((ccv_nnc_tensor_symbol_t*)ccv_array_get(sub_wrt_symbols, j))->d == i);
			if (!flag)
			{
				ccv_nnc_tensor_symbol_t sub_wrt_symbol = {
					.d = i,
					.graph = sub_graph,
				};
				ccv_array_push(sub_wrt_symbols, &sub_wrt_symbol);
			}
			flag = 0;
			for (j = 0; !flag && j < sub_f_symbols->rnum; j++)
				flag = (((ccv_nnc_tensor_symbol_t*)ccv_array_get(sub_f_symbols, j))->d == assign_ref);
			if (!flag)
			{
				ccv_nnc_tensor_symbol_t sub_f_symbol = {
					.d = assign_ref,
					.graph = sub_graph,
				};
				ccv_array_push(sub_f_symbols, &sub_f_symbol);
			}
		}
	}
}