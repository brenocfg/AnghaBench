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
struct TYPE_8__ {scalar_t__ alias_ref; } ;
typedef  TYPE_2__ const ccv_nnc_tensor_symbol_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_9__ {char* name; int const input_size; scalar_t__* inputs; int const output_size; scalar_t__* outputs; TYPE_1__ cmd; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_symbol_info_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int const CCV_NNC_LONG_DOT_GRAPH ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_dot_tensor_symbol (scalar_t__,TYPE_2__ const*,TYPE_2__ const*,int,int const,int /*<<< orphan*/ *) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/  const* const,scalar_t__) ; 
 char* ccv_nnc_cmd_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_dot_case_of_label(const ccv_nnc_graph_exec_symbol_info_t* const exec_symbol_info, const int index, const ccv_array_t* const tensor_symbol_info, const int flags, FILE* out)
{
	int i;
	if (flags == CCV_NNC_LONG_DOT_GRAPH)
		fputs("<table border=\"0\" cellborder=\"1\" cellspacing=\"0\"><tr><td colspan=\"3\" border=\"0\"><b>", out);
	else
		fputs("<table border=\"0\" cellborder=\"1\" cellspacing=\"0\"><tr><td colspan=\"2\" border=\"0\"><b>", out);
	if (exec_symbol_info->name)
		fputs(exec_symbol_info->name, out);
	else
		fprintf(out, "caseof%d", index);
	fputs(" </b>Command: ", out);
	fputs(ccv_nnc_cmd_name(exec_symbol_info->cmd.cmd), out);
	fputs("</td></tr>", out);
	if (exec_symbol_info->input_size > 0)
	{
		fprintf(out, "<tr><td rowspan=\"%d\">Input</td>", exec_symbol_info->input_size);
		for (i = 0; i < exec_symbol_info->input_size; i++)
		{
			if (i > 0)
				fputs("<tr>", out);
			if (exec_symbol_info->inputs[i] >= 0)
			{
				fputs("<td>", out);
				const ccv_nnc_tensor_symbol_info_t* const tensor_symbol = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(tensor_symbol_info, exec_symbol_info->inputs[i]);
				const ccv_nnc_tensor_symbol_info_t* const alias_symbol = tensor_symbol->alias_ref ? (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(tensor_symbol_info, tensor_symbol->alias_ref - 1) : 0;
				_ccv_nnc_symbolic_graph_dot_tensor_symbol(exec_symbol_info->inputs[i], tensor_symbol, alias_symbol, 1, flags, out);
				fputs("</td></tr>", out);
			} else {
				if (flags == CCV_NNC_LONG_DOT_GRAPH)
					fputs("<td colspan=\"2\">-</td></tr>", out);
				else
					fputs("<td colspan=\"1\">-</td></tr>", out);
			}
		}
	}
	if (exec_symbol_info->output_size > 0)
	{
		fprintf(out, "<tr><td rowspan=\"%d\">Output</td>", exec_symbol_info->output_size);
		for (i = 0; i < exec_symbol_info->output_size; i++)
		{
			if (i > 0)
				fputs("<tr>", out);
			if (exec_symbol_info->outputs[i] >= 0)
			{
				fputs("<td>", out);
				ccv_nnc_tensor_symbol_info_t* tensor_symbol = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(tensor_symbol_info, exec_symbol_info->outputs[i]);
				ccv_nnc_tensor_symbol_info_t* alias_symbol = tensor_symbol->alias_ref ? (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(tensor_symbol_info, tensor_symbol->alias_ref - 1) : 0;
				_ccv_nnc_symbolic_graph_dot_tensor_symbol(exec_symbol_info->outputs[i], tensor_symbol, alias_symbol, 1, flags, out);
				fputs("</td></tr>", out);
			} else {
				if (flags == CCV_NNC_LONG_DOT_GRAPH)
					fputs("<td colspan=\"2\">-</td></tr>", out);
				else
					fputs("<td colspan=\"1\">-</td></tr>", out);
			}
		}
	}
	fputs("</table>", out);
}