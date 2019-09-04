#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  type; } ;
struct TYPE_11__ {TYPE_3__ info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_t ;
typedef  TYPE_3__ ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;
struct TYPE_10__ {int size; } ;
struct TYPE_13__ {int tensor_offset; TYPE_1__ tuple; int /*<<< orphan*/  device_id; } ;
typedef  TYPE_4__ ccv_cnnp_copy_to_gpu_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_TENSOR_CPU_MEMORY ; 
 int /*<<< orphan*/  CCV_TENSOR_GPU_MEMORY ; 
 int /*<<< orphan*/  CCV_TENSOR_SET_DEVICE_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_DATA_TRANSFER_FORWARD () ; 
 void* ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_nnc_cmd_exec (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int,TYPE_2__**,int,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 
 TYPE_2__* ccv_nnc_tensor_new (int /*<<< orphan*/ ,TYPE_3__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_pin_memory (TYPE_2__*) ; 

__attribute__((used)) static void _ccv_cnnp_copy_to_gpu(void*** const column_data, const int column_size, const int batch_size, void** const data, void* const context, ccv_nnc_stream_context_t* const stream_context)
{
	const ccv_cnnp_copy_to_gpu_context_t* const copy_to_gpu_context = (ccv_cnnp_copy_to_gpu_context_t*)context;
	int i, j;
	for (i = 0; i < batch_size; i++)
	{
		ccv_nnc_tensor_t** inputs = (ccv_nnc_tensor_t**)column_data[0][i] + copy_to_gpu_context->tensor_offset;
		ccv_nnc_tensor_t** outputs = (ccv_nnc_tensor_t**)data[i];
		if (!outputs)
		{
			outputs = (ccv_nnc_tensor_t**)(data[i] = ccmalloc(sizeof(ccv_nnc_tensor_t*) * copy_to_gpu_context->tuple.size));
			for (j = 0; j < copy_to_gpu_context->tuple.size; j++)
			{
				ccv_nnc_tensor_param_t params = inputs[j]->info;
				params.type &= ~CCV_TENSOR_CPU_MEMORY;
				params.type |= CCV_TENSOR_GPU_MEMORY; // Change to GPU memory.
				CCV_TENSOR_SET_DEVICE_ID(params.type, copy_to_gpu_context->device_id);
				outputs[j] = ccv_nnc_tensor_new(0, params, 0);
			}
		}
		for (j = 0; j < copy_to_gpu_context->tuple.size; j++)
			ccv_nnc_tensor_pin_memory(inputs[j]);
		ccv_nnc_cmd_exec(CMD_DATA_TRANSFER_FORWARD(), ccv_nnc_no_hint, 0, inputs, copy_to_gpu_context->tuple.size, outputs, copy_to_gpu_context->tuple.size, stream_context);
	}
}