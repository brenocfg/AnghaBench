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

int ccv_nnc_tensor_pin_memory(ccv_nnc_tensor_t* const tensor)
{
#ifdef HAVE_CUDA
	if (!(tensor->type & CCV_PINNED_MEM))
	{
		const int success = curegister(tensor->data.u8, ccv_nnc_tensor_data_size(tensor->info));
		if (success)
			tensor->type |= CCV_PINNED_MEM;
		return success ? 0 : -1;
	}
#endif
	return 0;
}