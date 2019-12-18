#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int size; scalar_t__* tensor_wraps; } ;
typedef  TYPE_1__ ccv_nnc_graph_tensor_wrap_array_t ;
struct TYPE_10__ {int /*<<< orphan*/  tensor_wraps; } ;
typedef  TYPE_2__ ccv_nnc_graph_t ;
struct TYPE_11__ {int input_size; int output_size; int update_size; scalar_t__ tensor_wraps_ref; int /*<<< orphan*/  updates; int /*<<< orphan*/  outputs; int /*<<< orphan*/  inputs; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_graph_tensor_wrap_free (scalar_t__) ; 
 int /*<<< orphan*/  ccfree (TYPE_1__* const) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* ccv_nnc_get_tensor_wrap_array (TYPE_2__* const,int const,scalar_t__*) ; 
 int /*<<< orphan*/  ccv_nnc_set_tensor_wraps (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ccv_nnc_tensors_have_wraps (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _ccv_nnc_graph_redo_tensor_wraps(ccv_nnc_graph_exec_info_t* const info, ccv_nnc_graph_t* const graph)
{
	int i;
	const int has_wrap = ccv_nnc_tensors_have_wraps(info->inputs, info->input_size) ||
		ccv_nnc_tensors_have_wraps(info->outputs, info->output_size) ||
		ccv_nnc_tensors_have_wraps(info->updates, info->update_size);
	if (has_wrap)
	{
		const int tensor_wrap_size = info->input_size + info->output_size + info->update_size;
		ccv_nnc_graph_tensor_wrap_array_t* const tensor_wrap_array = ccv_nnc_get_tensor_wrap_array(graph, tensor_wrap_size, &info->tensor_wraps_ref);
		ccv_nnc_set_tensor_wraps(tensor_wrap_array->tensor_wraps, info->inputs, info->input_size);
		const int d = info->input_size;
		ccv_nnc_set_tensor_wraps(tensor_wrap_array->tensor_wraps + d, info->outputs, info->output_size);
		const int dd = info->input_size + info->output_size;
		ccv_nnc_set_tensor_wraps(tensor_wrap_array->tensor_wraps + dd, info->updates, info->update_size);
	} else if (info->tensor_wraps_ref) {
		ccv_nnc_graph_tensor_wrap_array_t** tensor_wrap_array_ref = (ccv_nnc_graph_tensor_wrap_array_t**)ccv_array_get(graph->tensor_wraps, info->tensor_wraps_ref - 1);
		ccv_nnc_graph_tensor_wrap_array_t* const tensor_wrap_array = *tensor_wrap_array_ref;
		if (tensor_wrap_array)
		{
			for (i = 0; i < tensor_wrap_array->size; i++)
				if (tensor_wrap_array->tensor_wraps[i])
					_ccv_nnc_graph_tensor_wrap_free(tensor_wrap_array->tensor_wraps[i]);
			ccfree(tensor_wrap_array);
			*tensor_wrap_array_ref = 0;
			info->tensor_wraps_ref = 0;
		}
	}
}