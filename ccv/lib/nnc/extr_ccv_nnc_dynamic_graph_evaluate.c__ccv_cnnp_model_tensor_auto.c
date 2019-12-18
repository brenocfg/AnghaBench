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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_param_t ;
struct TYPE_4__ {scalar_t__ data; } ;
typedef  TYPE_1__ ccv_nnc_stateful_exec_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
struct TYPE_5__ {scalar_t__ data; } ;
typedef  TYPE_2__ ccv_nnc_cmd_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_cnnp_model_tensor_auto (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int const) ; 

__attribute__((used)) static void _ccv_cnnp_model_tensor_auto(const ccv_nnc_cmd_t cmd, const ccv_nnc_tensor_param_t* const inputs, const int input_size, const ccv_nnc_hint_t hint, ccv_nnc_tensor_param_t* const outputs, const int output_size)
{
	ccv_nnc_stateful_exec_t* const stateful_exec = (ccv_nnc_stateful_exec_t*)cmd.data;
	ccv_cnnp_model_t* const model = (ccv_cnnp_model_t*)stateful_exec->data;
	ccv_cnnp_model_tensor_auto(model, outputs, output_size);
}