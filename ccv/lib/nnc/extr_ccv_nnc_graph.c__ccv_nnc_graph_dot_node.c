#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_multiview_t ;
struct TYPE_8__ {size_t index; size_t zone; } ;
typedef  TYPE_1__ ccv_nnc_tensor_dot_t ;
struct TYPE_9__ {int* remap; int /*<<< orphan*/ * rename_zone; int /*<<< orphan*/ * rename_index; TYPE_1__* dots; } ;
typedef  TYPE_2__ ccv_nnc_tensor_dot_recovery_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;
struct TYPE_10__ {int input_size; int output_size; scalar_t__* outputs; scalar_t__* inputs; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_info_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CCV_IS_TENSOR_MULTIVIEW (scalar_t__) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_dot_exec (int const,TYPE_3__ const* const,int /*<<< orphan*/ ** const,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_dot_tensor (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int const,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_dot_tensor_multiview (int /*<<< orphan*/ *,TYPE_2__ const,int const,int const,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_nnc_graph_dot_node(const ccv_nnc_graph_exec_info_t* const exec_info, const int exec_index, ccv_nnc_stream_context_t** const streams, const ccv_nnc_tensor_dot_recovery_t recovery, const int flags, const int depth, FILE* out, int* const tensor_index)
{
	fprintf(out, "node%d [shape=record,label=\"", exec_index);
	_ccv_nnc_graph_dot_exec(exec_index, exec_info, streams, flags, out);
	int i;
	int k = *tensor_index;
	if (exec_info->input_size > 0)
	{
		fputs("|{Input", out);
		for (i = 0; i < exec_info->input_size; i++)
			if (exec_info->inputs[i])
			{
				fputc('|', out);
				if (CCV_IS_TENSOR_MULTIVIEW(exec_info->inputs[i]))
					_ccv_nnc_graph_dot_tensor_multiview((ccv_nnc_tensor_multiview_t*)exec_info->inputs[i], recovery, flags, depth, &k, out);
				else {
					const ccv_nnc_tensor_dot_t* const tensor_dot = recovery.dots + recovery.remap[k];
					_ccv_nnc_graph_dot_tensor(recovery.rename_index[tensor_dot->index], exec_info->inputs[i], recovery.rename_zone[tensor_dot->zone], flags, depth, out);
					++k;
				}
			} else
				fputs("|-", out);
		fputc('}', out);
	}
	if (exec_info->output_size > 0)
	{
		fputs("|{Output", out);
		for (i = 0; i < exec_info->output_size; i++)
			if (exec_info->outputs[i])
			{
				fputc('|', out);
				if (CCV_IS_TENSOR_MULTIVIEW(exec_info->outputs[i]))
					_ccv_nnc_graph_dot_tensor_multiview((ccv_nnc_tensor_multiview_t*)exec_info->outputs[i], recovery, flags, depth, &k, out);
				else {
					const ccv_nnc_tensor_dot_t* const tensor_dot = recovery.dots + recovery.remap[k];
					_ccv_nnc_graph_dot_tensor(recovery.rename_index[tensor_dot->index], exec_info->outputs[i], recovery.rename_zone[tensor_dot->zone], flags, depth, out);
					++k;
				}
			} else
				fputs("|-", out);
		fputc('}', out);
	}
	fputs("\"];\n", out);
	*tensor_index = k;
}