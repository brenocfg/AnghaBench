#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (int /*<<< orphan*/ * const) ; 

void ccv_nnc_tensor_free(ccv_nnc_tensor_t* const tensor)
{
#ifdef HAVE_CUDA
	if (CCV_TENSOR_GET_MEMORY(tensor->info.type) == CCV_TENSOR_GPU_MEMORY)
		cufree(CCV_TENSOR_GET_DEVICE_ID(tensor->info.type), tensor->data.u8);
	if (tensor->type & CCV_PINNED_MEM)
		cuunregister(tensor->data.u8);
#endif
	ccfree(tensor);
}