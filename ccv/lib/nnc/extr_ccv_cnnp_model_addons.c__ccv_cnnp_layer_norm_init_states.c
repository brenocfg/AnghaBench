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
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_state_initializer_f ) (void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_4__ {scalar_t__ graph; } ;
struct TYPE_5__ {TYPE_1__ scale; TYPE_1__ bias; } ;
typedef  TYPE_2__ ccv_cnnp_model_batch_norm_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RANDOM_UNIFORM_FORWARD (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CMD_SET_FORWARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 

__attribute__((used)) static void _ccv_cnnp_layer_norm_init_states(ccv_cnnp_model_t* const super, ccv_nnc_symbolic_graph_t* const graph, const ccv_cnnp_state_initializer_f initializer, void* const context)
{
	ccv_cnnp_model_batch_norm_t* const self = (ccv_cnnp_model_batch_norm_t*)super;
	if (self->bias.graph)
		initializer(context, CMD_SET_FORWARD(0), ccv_nnc_no_hint, 0, 0, self->bias);
	if (self->scale.graph)
		initializer(context, CMD_RANDOM_UNIFORM_FORWARD(0, 1), ccv_nnc_no_hint, 0, 0, self->scale);
}