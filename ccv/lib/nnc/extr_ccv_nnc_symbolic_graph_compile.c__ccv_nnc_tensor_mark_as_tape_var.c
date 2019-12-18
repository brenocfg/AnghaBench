#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ ccv_nnc_tensor_t ;
struct TYPE_8__ {int repeat; int kind; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_nnc_tensor_multiview_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_IS_TENSOR_MULTIVIEW (TYPE_1__* const) ; 
 TYPE_1__** CCV_NNC_MULTIVIEW_DATA (TYPE_2__* const) ; 
 int /*<<< orphan*/  CCV_TAPE_ALLOC ; 

__attribute__((used)) static void _ccv_nnc_tensor_mark_as_tape_var(ccv_nnc_tensor_t* const tensor)
{
	if (!CCV_IS_TENSOR_MULTIVIEW(tensor))
		tensor->type |= CCV_TAPE_ALLOC;
	else {
		ccv_nnc_tensor_multiview_t* const mv = (ccv_nnc_tensor_multiview_t*)tensor;
		mv->type |= CCV_TAPE_ALLOC;
		int i;
		for (i = 0; i < mv->repeat + mv->kind; i++)
			_ccv_nnc_tensor_mark_as_tape_var(CCV_NNC_MULTIVIEW_DATA(mv)[i]);
	}
}