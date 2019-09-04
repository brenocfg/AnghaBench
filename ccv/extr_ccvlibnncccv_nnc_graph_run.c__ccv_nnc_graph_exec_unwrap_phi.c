#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ anchor; int /*<<< orphan*/  it; } ;
typedef  TYPE_1__ ccv_nnc_tensor_multiview_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_t ;
struct TYPE_7__ {int output_size; scalar_t__* outputs; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_info_t ;

/* Variables and functions */
 scalar_t__ CCV_IS_TENSOR_MULTIVIEW (scalar_t__) ; 
 int /*<<< orphan*/ * CCV_NNC_MULTIVIEW_DATA (TYPE_1__* const) ; 
 scalar_t__ CCV_NNC_MULTIVIEW_PHI ; 
 int /*<<< orphan*/  ccv_nnc_tensor_multiview_synchronize (TYPE_1__* const) ; 

__attribute__((used)) static void _ccv_nnc_graph_exec_unwrap_phi(ccv_nnc_graph_t* const graph, const ccv_nnc_graph_exec_info_t* const node, const int ref)
{
	int i;
	// If the output tensor is a phi multi-view tensor, we update our selection to all the subscribers.
	for (i = 0; i < node->output_size; i++)
		if (CCV_IS_TENSOR_MULTIVIEW(node->outputs[i]) &&
			((ccv_nnc_tensor_multiview_t*)node->outputs[i])->anchor == CCV_NNC_MULTIVIEW_PHI)
		{
			ccv_nnc_tensor_multiview_t* const mv = (ccv_nnc_tensor_multiview_t*)node->outputs[i];
			mv->it = CCV_NNC_MULTIVIEW_DATA(mv)[ref >= 0];
			ccv_nnc_tensor_multiview_synchronize(mv);
		}
}