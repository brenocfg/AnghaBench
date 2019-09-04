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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;

/* Variables and functions */
 void* ccv_nnc_tensor_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_cnnp_tensor_new(const int column_idx, const int* const row_idxs, const int row_size, void** const data, void* const context, ccv_nnc_stream_context_t* const stream_context)
{
	ccv_nnc_tensor_param_t params = *(ccv_nnc_tensor_param_t*)context;
	int i;
	for (i = 0; i < row_size; i++)
		if (!data[i])
			data[i] = ccv_nnc_tensor_new(0, params, 0);
}