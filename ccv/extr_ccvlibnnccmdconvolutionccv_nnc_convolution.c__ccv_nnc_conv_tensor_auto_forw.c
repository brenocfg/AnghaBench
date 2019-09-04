#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  dim; int /*<<< orphan*/  datatype; int /*<<< orphan*/  format; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
struct TYPE_13__ {int const count; } ;
struct TYPE_15__ {TYPE_1__ convolution; } ;
typedef  TYPE_3__ ccv_nnc_cmd_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_nnc_hint_tensor_forward (TYPE_3__ const,TYPE_2__ const,int /*<<< orphan*/  const,TYPE_2__*) ; 
 int ccv_nnc_tensor_get_n (TYPE_2__ const) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_nd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_set_c (TYPE_2__*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_set_n (TYPE_2__*,int) ; 

__attribute__((used)) static void _ccv_nnc_conv_tensor_auto_forw(const ccv_nnc_cmd_param_t cmd, const ccv_nnc_tensor_param_t* inputs, const int input_size, const ccv_nnc_hint_t hint, ccv_nnc_tensor_param_t* outputs, const int output_size)
{
	assert(output_size == 1);
	outputs[0].type = inputs[0].type;
	outputs[0].format = inputs[0].format;
	outputs[0].datatype = inputs[0].datatype;
	// Get the channel output from the weight matrix.
	const int count = ccv_nnc_tensor_get_n(inputs[1]);
	assert(count == cmd.convolution.count);
	ccv_nnc_tensor_set_c(outputs, ccv_nnc_tensor_nd(inputs[0].dim), count);
	ccv_nnc_tensor_set_n(outputs, ccv_nnc_tensor_get_n(inputs[0]));
	ccv_nnc_hint_tensor_forward(cmd, inputs[0], hint, outputs);
}