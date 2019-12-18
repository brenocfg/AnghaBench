#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_EWSUM_FORWARD () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_new (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ * const,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_new (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_params (int /*<<< orphan*/ * const,int /*<<< orphan*/  const) ; 

__attribute__((used)) static void _ccv_cnnp_add_build(ccv_cnnp_model_t* const self, ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_tensor_symbol_t* const inputs, const int input_size, ccv_nnc_tensor_symbol_t* const outputs, const int output_size)
{
	assert(output_size == 1);
	outputs[0] = ccv_nnc_tensor_symbol_new(graph, ccv_nnc_tensor_symbol_params(graph, inputs[0]), 0);
	ccv_nnc_graph_exec_symbol_new(graph, CMD_EWSUM_FORWARD(), inputs, input_size, outputs, output_size, 0);
}