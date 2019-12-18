#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
struct TYPE_7__ {intptr_t anchor; int kind; int repeat; } ;
typedef  TYPE_1__ ccv_nnc_tensor_multiview_t ;
struct TYPE_8__ {size_t index; int update_required; size_t count; int /*<<< orphan*/ ** tensors; } ;
typedef  TYPE_2__ ccv_nnc_graph_tensor_wrap_t ;
struct TYPE_9__ {scalar_t__ pair; } ;
typedef  TYPE_3__ ccv_nnc_graph_t ;

/* Variables and functions */
 scalar_t__ CCV_IS_TENSOR_MULTIVIEW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ ** CCV_NNC_MULTIVIEW_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void _ccv_nnc_unwrap_tensor_wrap(const ccv_nnc_graph_t* const graph, const int64_t count, const int64_t reverse_count, ccv_nnc_graph_tensor_wrap_t* const tensor_wrap)
{
	ccv_nnc_tensor_t* tensor = tensor_wrap->tensors[tensor_wrap->index];
	while (CCV_IS_TENSOR_MULTIVIEW(tensor) &&
		   (((ccv_nnc_tensor_multiview_t*)tensor)->anchor == (intptr_t)graph ||
			((ccv_nnc_tensor_multiview_t*)tensor)->anchor == (intptr_t)graph->pair))
	{
		// If the anchor is from the pair, we use the reverse_count instead (we are looking it up).
		const int i = (int)((((ccv_nnc_tensor_multiview_t*)tensor)->anchor == (intptr_t)graph) ? count : reverse_count);
		ccv_nnc_tensor_multiview_t* mv = (ccv_nnc_tensor_multiview_t*)tensor;
		const int off = mv->kind;
		const int mod = mv->repeat;
		tensor = CCV_NNC_MULTIVIEW_DATA(mv)[i >= off ? ((i - off) % mod) + off : i]; // Unwrap.
		// If reached the root.
		if (!CCV_IS_TENSOR_MULTIVIEW(tensor))
			tensor_wrap->update_required = 1; // Need to update tensor updates.
		++tensor_wrap->index;
		tensor_wrap->tensors[tensor_wrap->index] = tensor;
		assert(tensor_wrap->index < tensor_wrap->count);
	}
}