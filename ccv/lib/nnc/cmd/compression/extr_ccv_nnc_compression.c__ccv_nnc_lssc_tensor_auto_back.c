#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ datatype; int* dim; } ;
typedef  TYPE_1__ ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_param_t ;

/* Variables and functions */
 scalar_t__ CCV_16F ; 
 int CCV_NNC_MAX_DIM ; 
 int /*<<< orphan*/  assert (int) ; 
 int ccv_nnc_tensor_hw (TYPE_1__ const,int const) ; 
 int ccv_nnc_tensor_nd (int*) ; 

__attribute__((used)) static void _ccv_nnc_lssc_tensor_auto_back(const ccv_nnc_cmd_param_t cmd, const ccv_nnc_tensor_param_t* inputs, const int input_size, const ccv_nnc_hint_t hint, ccv_nnc_tensor_param_t* outputs, const int output_size)
{
	int i, j;
	assert(output_size <= input_size);
	for (i = 0; i < output_size; i++)
	{
		assert(inputs[i].datatype == CCV_16F);
		const int nd = ccv_nnc_tensor_nd(inputs[i].dim);
		const int hw = ccv_nnc_tensor_hw(inputs[i], nd);
		outputs[i] = inputs[i];
		for (j = 0; j < CCV_NNC_MAX_DIM - 1; j++)
			outputs[i].dim[j + hw] = inputs[i].dim[j + hw] * 4;
		assert(outputs[i].dim[CCV_NNC_MAX_DIM - 1 + hw] % 4 == 0);
	}
}