#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {intptr_t anchor; } ;
typedef  TYPE_1__ ccv_nnc_tensor_multiview_t ;
struct TYPE_7__ {int index; scalar_t__* tensors; } ;
typedef  TYPE_2__ ccv_nnc_graph_tensor_wrap_t ;
struct TYPE_8__ {scalar_t__ pair; } ;
typedef  TYPE_3__ ccv_nnc_graph_t ;

/* Variables and functions */
 scalar_t__ CCV_IS_TENSOR_MULTIVIEW (scalar_t__) ; 

__attribute__((used)) static void _ccv_nnc_rewrap_tensor_wrap(const ccv_nnc_graph_t* const graph, ccv_nnc_graph_tensor_wrap_t* const tensor_wrap)
{
	while (tensor_wrap->index > 0 && CCV_IS_TENSOR_MULTIVIEW(tensor_wrap->tensors[tensor_wrap->index - 1]) &&
			(((ccv_nnc_tensor_multiview_t*)tensor_wrap->tensors[tensor_wrap->index - 1])->anchor == (intptr_t)graph ||
			 ((ccv_nnc_tensor_multiview_t*)tensor_wrap->tensors[tensor_wrap->index - 1])->anchor == (intptr_t)graph->pair))
		--tensor_wrap->index;
}