#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int* dim; } ;
typedef  TYPE_2__ ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
struct TYPE_7__ {int count; size_t* axis; } ;
struct TYPE_9__ {TYPE_1__ bnorm; } ;
typedef  TYPE_3__ ccv_nnc_cmd_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void _ccv_nnc_batch_norm_tensor_auto_back(const ccv_nnc_cmd_param_t cmd, const ccv_nnc_tensor_param_t* const inputs, const int input_size, const ccv_nnc_hint_t hint, ccv_nnc_tensor_param_t* const outputs, const int output_size)
{
	assert(input_size == 15);
	assert(output_size == 5);
	outputs[0] = inputs[0];
	int i, j;
	for (i = 1; i < output_size; i++)
	{
		outputs[i] = inputs[0];
		for (j = 0; j < cmd.bnorm.count; j++)
			outputs[i].dim[cmd.bnorm.axis[j]] = 1; // Reduce the dimension to 1.
	}
}