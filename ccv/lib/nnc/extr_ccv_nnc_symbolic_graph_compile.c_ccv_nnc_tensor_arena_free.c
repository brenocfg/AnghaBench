#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int buffer_size; TYPE_1__* buffers; } ;
typedef  TYPE_2__ ccv_nnc_tensor_arena_t ;
struct TYPE_5__ {int type; int /*<<< orphan*/  ptr; scalar_t__ pin_mem; } ;

/* Variables and functions */
 int const CCV_TENSOR_CPU_MEMORY ; 
 int CCV_TENSOR_GET_DEVICE_ID (int const) ; 
 int CCV_TENSOR_GET_MEMORY (int const) ; 
 int const CCV_TENSOR_GPU_MEMORY ; 
 int /*<<< orphan*/  _ccv_nnc_tensor_arena_free (TYPE_2__* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cufree (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cuhostfree (int /*<<< orphan*/ ) ; 

void ccv_nnc_tensor_arena_free(ccv_nnc_tensor_arena_t* const tensor_arena)
{
	int i;
	for (i = 0; i < tensor_arena->buffer_size; i++)
	{
		const int buffer_type = tensor_arena->buffers[i].type;;
		const int memory_type = CCV_TENSOR_GET_MEMORY(buffer_type);
#ifdef HAVE_CUDA
		const int device_id = CCV_TENSOR_GET_DEVICE_ID(buffer_type);
		if (memory_type == CCV_TENSOR_GPU_MEMORY)
			cufree(device_id, tensor_arena->buffers[i].ptr);
		else {
			assert(memory_type == CCV_TENSOR_CPU_MEMORY);
			if (tensor_arena->buffers[i].pin_mem)
				cuhostfree(tensor_arena->buffers[i].ptr);
			else
				ccfree(tensor_arena->buffers[i].ptr);
		}
#else
		assert(memory_type == CCV_TENSOR_CPU_MEMORY);
		ccfree(tensor_arena->buffers[i].ptr);
#endif
	}
	_ccv_nnc_tensor_arena_free(tensor_arena);
}