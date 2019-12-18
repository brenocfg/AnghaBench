#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  (* ccv_cnnp_state_initializer_f ) (void* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__) ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;
struct TYPE_5__ {scalar_t__ graph; } ;
struct TYPE_6__ {TYPE_1__ scale; TYPE_1__ bias; TYPE_1__ weights; } ;
typedef  TYPE_2__ ccv_cnnp_model_convolution_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RANDOM_UNIFORM_FORWARD (float const,float const) ; 
 int /*<<< orphan*/  CMD_SET_FORWARD (int /*<<< orphan*/ ) ; 
 int ccv_max (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ccv_nnc_no_hint ; 
 int ccv_nnc_tensor_count (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_get_n (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_params (int /*<<< orphan*/ * const,TYPE_1__) ; 
 float const sqrtf (int const) ; 

__attribute__((used)) static void _ccv_cnnp_convolution_init_states(ccv_cnnp_model_t* const super, ccv_nnc_symbolic_graph_t* const graph, const ccv_cnnp_state_initializer_f initializer, void* const context)
{
	ccv_cnnp_model_convolution_t* const self = (ccv_cnnp_model_convolution_t*)super;
	const ccv_nnc_tensor_param_t weight_params = ccv_nnc_tensor_symbol_params(graph, self->weights);
	const int n = ccv_max(ccv_nnc_tensor_get_n(weight_params), 1);
	const int count = ccv_nnc_tensor_count(weight_params);
	const float std = sqrtf(2) / sqrtf(count / n);
	const float bound = sqrtf(3) * std;
	initializer(context, CMD_RANDOM_UNIFORM_FORWARD(-bound, bound), ccv_nnc_no_hint, 0, 0, self->weights);
	if (self->bias.graph)
		initializer(context, CMD_SET_FORWARD(0), ccv_nnc_no_hint, 0, 0, self->bias);
	if (self->scale.graph)
		initializer(context, CMD_RANDOM_UNIFORM_FORWARD(0, 1), ccv_nnc_no_hint, 0, 0, self->scale);
}