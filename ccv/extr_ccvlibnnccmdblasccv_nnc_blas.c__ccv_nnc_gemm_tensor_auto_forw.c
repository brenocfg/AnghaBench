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
struct TYPE_8__ {scalar_t__* dim; int /*<<< orphan*/  datatype; int /*<<< orphan*/  format; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
struct TYPE_7__ {scalar_t__ count; } ;
struct TYPE_9__ {TYPE_1__ blas; } ;
typedef  TYPE_3__ ccv_nnc_cmd_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void _ccv_nnc_gemm_tensor_auto_forw(const ccv_nnc_cmd_param_t cmd, const ccv_nnc_tensor_param_t* const inputs, const int input_size, const ccv_nnc_hint_t hint, ccv_nnc_tensor_param_t* const outputs, const int output_size)
{
	assert(output_size == 1);
	outputs[0].type = inputs[0].type;
	outputs[0].format = inputs[0].format;
	outputs[0].datatype = inputs[0].datatype;
	outputs[0].dim[0] = inputs[0].dim[0]; // batch size.
	outputs[0].dim[1] = inputs[1].dim[0]; // from the weight matrix.
	assert(inputs[1].dim[0] == cmd.blas.count);
}