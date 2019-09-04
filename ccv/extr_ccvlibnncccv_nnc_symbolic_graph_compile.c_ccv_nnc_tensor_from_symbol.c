#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ it; } ;
typedef  TYPE_1__ ccv_nnc_tensor_t ;
struct TYPE_11__ {size_t d; scalar_t__ graph; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_t ;
typedef  TYPE_1__ ccv_nnc_tensor_multiview_t ;
struct TYPE_12__ {intptr_t graph_ref; size_t vt_tensor_size; int sub_arena_size; struct TYPE_12__** sub_arenas; TYPE_1__** vt_tensors; } ;
typedef  TYPE_4__ ccv_nnc_tensor_arena_t ;

/* Variables and functions */
 scalar_t__ CCV_IS_TENSOR_MULTIVIEW (TYPE_1__*) ; 
 scalar_t__* CCV_NNC_MULTIVIEW_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

ccv_nnc_tensor_t* ccv_nnc_tensor_from_symbol(const ccv_nnc_tensor_arena_t* const tensor_arena, const ccv_nnc_tensor_symbol_t symbol)
{
	if ((intptr_t)symbol.graph == tensor_arena->graph_ref)
	{
		assert(symbol.d >= 0 && symbol.d < tensor_arena->vt_tensor_size);
		ccv_nnc_tensor_t* tensor = tensor_arena->vt_tensors[symbol.d];
		if (tensor && CCV_IS_TENSOR_MULTIVIEW(tensor))
		{
			ccv_nnc_tensor_multiview_t* mv = (ccv_nnc_tensor_multiview_t*)tensor;
			while (CCV_IS_TENSOR_MULTIVIEW(mv))
				mv = (ccv_nnc_tensor_multiview_t*)(mv->it ? mv->it : CCV_NNC_MULTIVIEW_DATA(mv)[0]);
			return (ccv_nnc_tensor_t*)mv;
		}
		return tensor;
	}
	int i;
	for (i = 0; i < tensor_arena->sub_arena_size; i++)
		if (tensor_arena->sub_arenas[i])
		{
			ccv_nnc_tensor_t* tensor = ccv_nnc_tensor_from_symbol(tensor_arena->sub_arenas[i], symbol);
			if (tensor)
				return tensor;
		}
	return 0;
}