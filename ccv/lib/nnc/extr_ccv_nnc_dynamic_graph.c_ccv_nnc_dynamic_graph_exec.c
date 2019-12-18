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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_variable_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
typedef  int /*<<< orphan*/  ccv_nnc_dynamic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_t ;

/* Variables and functions */
 int CCV_NNC_EXEC_SUCCESS ; 
 int /*<<< orphan*/  ccv_nnc_dynamic_graph_exec_ret (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ * const,int const,int const,int /*<<< orphan*/ * const) ; 

int ccv_nnc_dynamic_graph_exec(ccv_nnc_dynamic_graph_t* const graph, const ccv_nnc_cmd_t cmd, const ccv_nnc_hint_t hint, const int flags, const ccv_nnc_tensor_variable_t* const inputs, const int input_size, ccv_nnc_tensor_variable_t* const outputs, const int output_size, const int parallel, ccv_nnc_stream_context_t* const stream_context)
{
	ccv_nnc_dynamic_graph_exec_ret(graph, cmd, hint, flags, inputs, input_size, outputs, output_size, parallel, stream_context);
	return CCV_NNC_EXEC_SUCCESS;
}