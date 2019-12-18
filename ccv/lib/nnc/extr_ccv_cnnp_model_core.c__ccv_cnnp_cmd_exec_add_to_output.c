#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_4__ {int input_size; int /*<<< orphan*/ * input_symbols; TYPE_1__* inputs; } ;
typedef  TYPE_2__ ccv_cnnp_model_cmd_exec_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_add_to_array_f ) (void* const,int /*<<< orphan*/ ) ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ CCV_CNNP_INIT_SHARED_TENSOR ; 

__attribute__((used)) static void _ccv_cnnp_cmd_exec_add_to_output(ccv_cnnp_model_t* const super, const ccv_cnnp_add_to_array_f add_to_array, void* const outputs)
{
	ccv_cnnp_model_cmd_exec_t* const self = (ccv_cnnp_model_cmd_exec_t*)super;
	int i;
	for (i = 0; i < self->input_size; i++)
		if (self->inputs[i].type == CCV_CNNP_INIT_SHARED_TENSOR)
			add_to_array(outputs, self->input_symbols[i]); // Push this as retainable because it need to be init.
}