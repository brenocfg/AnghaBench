#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {TYPE_2__* compiled_data; } ;
typedef  TYPE_1__ ccv_cnnp_model_t ;
struct TYPE_5__ {int /*<<< orphan*/  tensor_arena; } ;
typedef  TYPE_2__ ccv_cnnp_compiled_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_nnc_tensor_arena_size (int /*<<< orphan*/ ) ; 

uint64_t ccv_cnnp_model_memory_size(const ccv_cnnp_model_t* const model)
{
	const ccv_cnnp_compiled_data_t* const compiled_data = model->compiled_data;
	if (!compiled_data || !compiled_data->tensor_arena)
		return 0;
	return ccv_nnc_tensor_arena_size(compiled_data->tensor_arena);
}