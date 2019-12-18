#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ graph; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_state_initializer_f ) (void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_7__ {TYPE_4__* zero_inits; TYPE_1__ scale; TYPE_1__ bias; } ;
typedef  TYPE_3__ ccv_cnnp_model_batch_norm_t ;
struct TYPE_8__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RANDOM_UNIFORM_FORWARD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMD_SET_FORWARD (int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_array_get (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 

__attribute__((used)) static void _ccv_cnnp_batch_norm_init_states(ccv_cnnp_model_t* const super, ccv_nnc_symbolic_graph_t* const graph, const ccv_cnnp_state_initializer_f initializer, void* const context)
{
	ccv_cnnp_model_batch_norm_t* const self = (ccv_cnnp_model_batch_norm_t*)super;
	if (self->bias.graph)
		initializer(context, CMD_SET_FORWARD(0), ccv_nnc_no_hint, 0, 0, self->bias);
	if (self->scale.graph)
		initializer(context, CMD_RANDOM_UNIFORM_FORWARD(0, 1), ccv_nnc_no_hint, 0, 0, self->scale);
	int i;
	if (self->zero_inits)
		for (i = 0; i < self->zero_inits->rnum; i++)
			initializer(context, CMD_SET_FORWARD(0), ccv_nnc_no_hint, 0, 0, *(ccv_nnc_tensor_symbol_t*)ccv_array_get(self->zero_inits, i));
}