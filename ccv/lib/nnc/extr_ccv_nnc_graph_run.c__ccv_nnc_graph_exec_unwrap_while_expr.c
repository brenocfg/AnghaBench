#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct TYPE_11__* it; } ;
typedef  TYPE_2__ ccv_nnc_tensor_multiview_t ;
struct TYPE_12__ {int index; TYPE_2__** tensors; } ;
typedef  TYPE_3__ ccv_nnc_graph_tensor_wrap_t ;
struct TYPE_13__ {int size; TYPE_3__** tensor_wraps; } ;
typedef  TYPE_4__ ccv_nnc_graph_tensor_wrap_array_t ;
struct TYPE_14__ {int /*<<< orphan*/  tensor_wraps; } ;
typedef  TYPE_5__ ccv_nnc_graph_t ;
struct TYPE_10__ {int input_size; TYPE_2__** inputs; scalar_t__ tensor_wraps_ref; } ;
struct TYPE_15__ {int flags; TYPE_1__ p_while; } ;
typedef  TYPE_6__ ccv_nnc_graph_exec_info_t ;

/* Variables and functions */
 int CCV_IS_TENSOR_MULTIVIEW (TYPE_2__*) ; 
 int CCV_NNC_GRAPH_EXEC_P_WHILE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void _ccv_nnc_graph_exec_unwrap_while_expr(const ccv_nnc_graph_t* const graph, ccv_nnc_graph_exec_info_t* const node)
{
	assert(node->flags & CCV_NNC_GRAPH_EXEC_P_WHILE);
	if (!node->p_while.tensor_wraps_ref)
		return;
	int i;
	ccv_nnc_graph_tensor_wrap_array_t* const tensor_wrap_array = *(ccv_nnc_graph_tensor_wrap_array_t**)ccv_array_get(graph->tensor_wraps, node->p_while.tensor_wraps_ref - 1);
	ccv_nnc_graph_tensor_wrap_t** const tensor_wraps = tensor_wrap_array->tensor_wraps;
	for (i = 0; i < tensor_wrap_array->size; i++)
		if (tensor_wraps[i])
		{
			assert(tensor_wraps[i]->index > 0);
			ccv_nnc_tensor_multiview_t* mv = (ccv_nnc_tensor_multiview_t*)(tensor_wraps[i]->tensors[tensor_wraps[i]->index - 1]);
			assert(CCV_IS_TENSOR_MULTIVIEW(mv));
			// Only now set the mv->it, because now this node is about to get executed.
			mv->it = tensor_wraps[i]->tensors[tensor_wraps[i]->index];
			assert(!CCV_IS_TENSOR_MULTIVIEW(mv->it));
		}
	for (i = 0; i < node->p_while.input_size; i++)
		if (tensor_wraps[i])
			node->p_while.inputs[i] = tensor_wraps[i]->tensors[tensor_wraps[i]->index];
}