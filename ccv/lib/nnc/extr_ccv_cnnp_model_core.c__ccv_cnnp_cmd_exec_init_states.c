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
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_state_initializer_f ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_6__ {int input_size; TYPE_2__* inputs; int /*<<< orphan*/ * input_symbols; } ;
typedef  TYPE_3__ ccv_cnnp_model_cmd_exec_t ;
struct TYPE_4__ {int /*<<< orphan*/  context; int /*<<< orphan*/  (* init ) (int /*<<< orphan*/ ,int /*<<< orphan*/  const,void* const,int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ init_state; } ;

/* Variables and functions */
 scalar_t__ CCV_CNNP_INIT_SHARED_TENSOR ; 
 scalar_t__ CCV_CNNP_INIT_SHARED_TENSOR_AS_TRAINABLE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/  const,void* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_cnnp_cmd_exec_init_states(ccv_cnnp_model_t* const super, ccv_nnc_symbolic_graph_t* const graph, const ccv_cnnp_state_initializer_f initializer, void* const context)
{
	ccv_cnnp_model_cmd_exec_t* const self = (ccv_cnnp_model_cmd_exec_t*)super;
	int i;
	for (i = 0; i < self->input_size; i++)
		if (self->inputs[i].type == CCV_CNNP_INIT_SHARED_TENSOR || self->inputs[i].type == CCV_CNNP_INIT_SHARED_TENSOR_AS_TRAINABLE)
			self->inputs[i].init_state.init(self->input_symbols[i], initializer, context, self->inputs[i].init_state.context);
}