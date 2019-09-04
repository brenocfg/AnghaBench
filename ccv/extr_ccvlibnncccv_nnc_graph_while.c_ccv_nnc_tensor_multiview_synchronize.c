#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {unsigned char* u8; } ;
struct TYPE_15__ {int off; TYPE_2__ data; } ;
typedef  TYPE_4__ ccv_nnc_tensor_view_t ;
struct TYPE_14__ {unsigned char* u8; } ;
struct TYPE_16__ {TYPE_3__ data; } ;
typedef  TYPE_5__ ccv_nnc_tensor_t ;
struct TYPE_17__ {struct TYPE_17__* p; TYPE_8__* sp; int /*<<< orphan*/  offset; TYPE_10__* it; } ;
typedef  TYPE_6__ ccv_nnc_tensor_multiview_t ;
struct TYPE_18__ {int rnum; } ;
struct TYPE_12__ {int /*<<< orphan*/  u8; } ;
struct TYPE_11__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_IS_TENSOR_MULTIVIEW (TYPE_10__*) ; 
 scalar_t__ CCV_IS_TENSOR_VIEW (TYPE_5__* const) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_array_get (TYPE_8__*,int) ; 

void ccv_nnc_tensor_multiview_synchronize(ccv_nnc_tensor_multiview_t* const tensor_multiview)
{
	assert(tensor_multiview->it && !CCV_IS_TENSOR_MULTIVIEW(tensor_multiview->it));
	// Update the pointer on tv only if it is not a single tensor pointer.
	unsigned char* const data = tensor_multiview->it->data.u8 - tensor_multiview->offset;
	const ccv_nnc_tensor_multiview_t* c = tensor_multiview;
	int i;
	do {
		if (c->sp)
			for (i = 0; i < c->sp->rnum; i++)
			{
				ccv_nnc_tensor_t* const tensor = *(ccv_nnc_tensor_t**)ccv_array_get(c->sp, i);
				if (CCV_IS_TENSOR_VIEW(tensor))
				{
					ccv_nnc_tensor_view_t* const tensor_view = (ccv_nnc_tensor_view_t*)tensor;
					tensor_view->data.u8 = data + tensor_view->off;
				} else
					tensor->data.u8 = data;
			}
		c = c->p;
	} while (c);
}