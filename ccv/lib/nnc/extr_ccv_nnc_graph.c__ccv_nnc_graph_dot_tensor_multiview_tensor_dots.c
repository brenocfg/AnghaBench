#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int kind; int repeat; } ;
typedef  TYPE_3__ ccv_nnc_tensor_multiview_t ;
struct TYPE_13__ {int name; uintptr_t start_ptr; uintptr_t tensor_ref; size_t end_ptr; } ;
typedef  TYPE_4__ ccv_nnc_tensor_dot_t ;
struct TYPE_11__ {int /*<<< orphan*/  dim; } ;
struct TYPE_10__ {scalar_t__ u8; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; TYPE_2__ info; TYPE_1__ data; } ;

/* Variables and functions */
 size_t CCV_GET_DATA_TYPE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ CCV_IS_TENSOR_MULTIVIEW (TYPE_7__*) ; 
 TYPE_7__** CCV_NNC_MULTIVIEW_DATA (TYPE_3__ const* const) ; 
 size_t ccv_nnc_dimension_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_nnc_graph_dot_tensor_multiview_tensor_dots(const ccv_nnc_tensor_multiview_t* const mv, ccv_nnc_tensor_dot_t* const tensor_dots, int* tensor_index)
{
	const int count = mv->kind + mv->repeat;
	int i;
	for (i = 0; i < count; i++)
		if (CCV_IS_TENSOR_MULTIVIEW(CCV_NNC_MULTIVIEW_DATA(mv)[i]))
			_ccv_nnc_graph_dot_tensor_multiview_tensor_dots((ccv_nnc_tensor_multiview_t*)CCV_NNC_MULTIVIEW_DATA(mv)[i], tensor_dots, tensor_index);
		else {
			tensor_dots[*tensor_index].name = *tensor_index;
			tensor_dots[*tensor_index].start_ptr =  (uintptr_t)CCV_NNC_MULTIVIEW_DATA(mv)[i]->data.u8;
			// Because tv's pointer will get updated, it is not correct in this case to have one tensor_ref.
			tensor_dots[*tensor_index].tensor_ref = tensor_dots[*tensor_index].start_ptr;
			const size_t dim_size = ccv_nnc_dimension_count(CCV_NNC_MULTIVIEW_DATA(mv)[i]->info.dim) * CCV_GET_DATA_TYPE_SIZE(CCV_NNC_MULTIVIEW_DATA(mv)[i]->type);
			tensor_dots[*tensor_index].end_ptr = tensor_dots[*tensor_index].start_ptr + dim_size - 1;
			++(*tensor_index);
		}
}