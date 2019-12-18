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
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_dataframe_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_column_data_context_deinit_f ;
struct TYPE_4__ {int size; } ;
struct TYPE_5__ {int input_offset; int input_size; int flags; int /*<<< orphan*/  output_params; int /*<<< orphan*/  hint; int /*<<< orphan*/  cmd; TYPE_1__ tuple; } ;
typedef  TYPE_2__ ccv_cnnp_cmd_exec_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  COLUMN_ID_LIST (int const) ; 
 int /*<<< orphan*/  _ccv_cnnp_dataframe_cmd_exec ; 
 int /*<<< orphan*/  _ccv_cnnp_tensor_list_deinit ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccfree ; 
 scalar_t__ ccmalloc (int) ; 
 int ccv_cnnp_dataframe_map (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__* const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int) ; 

int ccv_cnnp_dataframe_cmd_exec(ccv_cnnp_dataframe_t* const dataframe, const int column_idx, const ccv_nnc_cmd_t cmd, const ccv_nnc_hint_t hint, const int flags, const int input_offset, const int input_size, const ccv_nnc_tensor_param_t* const output_params, const int output_size, const int stream_type)
{
	assert(input_size > 0);
	assert(output_size > 0);
	ccv_cnnp_cmd_exec_context_t* const cmd_exec_context = (ccv_cnnp_cmd_exec_context_t*)ccmalloc(sizeof(ccv_cnnp_cmd_exec_context_t) + sizeof(ccv_nnc_tensor_param_t) * (output_size - 1));
	cmd_exec_context->tuple.size = output_size;
	cmd_exec_context->input_offset = input_offset;
	cmd_exec_context->input_size = input_size;
	cmd_exec_context->cmd = cmd;
	cmd_exec_context->hint = hint;
	cmd_exec_context->flags = flags;
	memcpy(cmd_exec_context->output_params, output_params, sizeof(ccv_nnc_tensor_param_t) * output_size);
	return ccv_cnnp_dataframe_map(dataframe, _ccv_cnnp_dataframe_cmd_exec, stream_type, _ccv_cnnp_tensor_list_deinit, COLUMN_ID_LIST(column_idx), cmd_exec_context, (ccv_cnnp_column_data_context_deinit_f)ccfree);
	return 0;
}