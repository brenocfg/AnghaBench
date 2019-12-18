#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_6__ {int input_size; TYPE_2__* inputs; } ;
typedef  TYPE_3__ ccv_cnnp_model_cmd_exec_t ;
struct TYPE_4__ {void* context; int /*<<< orphan*/  (* deinit ) (void* const) ;scalar_t__ init; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ init_state; } ;

/* Variables and functions */
 scalar_t__ CCV_CNNP_INIT_SHARED_TENSOR ; 
 scalar_t__ CCV_CNNP_INIT_SHARED_TENSOR_AS_TRAINABLE ; 
 int /*<<< orphan*/  stub1 (void* const) ; 

__attribute__((used)) static void _ccv_cnnp_cmd_exec_deinit(ccv_cnnp_model_t* const super)
{
	ccv_cnnp_model_cmd_exec_t* const self = (ccv_cnnp_model_cmd_exec_t*)super;
	int i, j;
	for (i = 0; i < self->input_size; i++)
		if ((self->inputs[i].type == CCV_CNNP_INIT_SHARED_TENSOR || self->inputs[i].type == CCV_CNNP_INIT_SHARED_TENSOR_AS_TRAINABLE) &&
			self->inputs[i].init_state.context)
		{
			void* const context = self->inputs[i].init_state.context;
			if (self->inputs[i].init_state.deinit)
				self->inputs[i].init_state.deinit(context);
			self->inputs[i].init_state.init = 0;
			self->inputs[i].init_state.deinit = 0;
			self->inputs[i].init_state.context = 0;
			for (j = i + 1; j < self->input_size; j++)
				if (self->inputs[j].init_state.context == context)
				{
					self->inputs[j].init_state.init = 0;
					self->inputs[j].init_state.deinit = 0;
					self->inputs[j].init_state.context = 0;
				}
		}
}