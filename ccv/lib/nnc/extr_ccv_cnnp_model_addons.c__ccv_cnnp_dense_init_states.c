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
struct TYPE_7__ {int* dim; } ;
typedef  TYPE_1__ ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_state_initializer_f ) (void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__) ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_8__ {scalar_t__ graph; } ;
struct TYPE_9__ {TYPE_2__ scale; TYPE_2__ bias; TYPE_2__ weights; } ;
typedef  TYPE_3__ ccv_cnnp_model_dense_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RANDOM_UNIFORM_FORWARD (float const,float const) ; 
 int /*<<< orphan*/  CMD_SET_FORWARD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 
 TYPE_1__ ccv_nnc_tensor_symbol_params (int /*<<< orphan*/ * const,TYPE_2__) ; 
 float const sqrtf (int const) ; 

__attribute__((used)) static void _ccv_cnnp_dense_init_states(ccv_cnnp_model_t* const super, ccv_nnc_symbolic_graph_t* const graph, const ccv_cnnp_state_initializer_f initializer, void* const context)
{
	ccv_cnnp_model_dense_t* const self = (ccv_cnnp_model_dense_t*)super;
	const ccv_nnc_tensor_param_t weight_params = ccv_nnc_tensor_symbol_params(graph, self->weights);
	const int c = weight_params.dim[1];
	const float std = sqrtf(2) / sqrtf(c);
	const float bound = sqrtf(3) * std;
	initializer(context, CMD_RANDOM_UNIFORM_FORWARD(-bound, bound), ccv_nnc_no_hint, 0, 0, self->weights);
	if (self->bias.graph)
		initializer(context, CMD_SET_FORWARD(0), ccv_nnc_no_hint, 0, 0, self->bias);
	if (self->scale.graph)
		initializer(context, CMD_RANDOM_UNIFORM_FORWARD(0, 1), ccv_nnc_no_hint, 0, 0, self->scale);
}