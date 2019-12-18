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
struct TYPE_7__ {int /*<<< orphan*/  u8; } ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int type; TYPE_2__ data; TYPE_1__ info; } ;
typedef  TYPE_3__ ccv_nnc_tensor_t ;

/* Variables and functions */
 int CCV_NO_DATA_ALLOC ; 
 int CCV_PINNED_MEM ; 
 int /*<<< orphan*/  CCV_TENSOR_GET_DEVICE_ID (int /*<<< orphan*/ ) ; 
 scalar_t__ CCV_TENSOR_GET_MEMORY (int /*<<< orphan*/ ) ; 
 scalar_t__ CCV_TENSOR_GPU_MEMORY ; 
 int /*<<< orphan*/  ccfree (TYPE_3__* const) ; 
 int /*<<< orphan*/  cufree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuunregister (int /*<<< orphan*/ ) ; 

void ccv_nnc_tensor_free(ccv_nnc_tensor_t* const tensor)
{
#ifdef HAVE_CUDA
	if (CCV_TENSOR_GET_MEMORY(tensor->info.type) == CCV_TENSOR_GPU_MEMORY &&
		!(tensor->type & CCV_NO_DATA_ALLOC)) // If this is GPU memory and it is allocated, free.
		cufree(CCV_TENSOR_GET_DEVICE_ID(tensor->info.type), tensor->data.u8);
	if (tensor->type & CCV_PINNED_MEM)
		cuunregister(tensor->data.u8);
#endif
	ccfree(tensor);
}