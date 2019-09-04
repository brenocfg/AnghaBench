#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int offset; int size; } ;
struct TYPE_6__ {TYPE_1__ argument; } ;
struct TYPE_7__ {int flags; int* outputs; int output_size; int* inputs; int input_size; TYPE_2__ case_of; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_symbol_info_t ;

/* Variables and functions */
 int CCV_NNC_GRAPH_EXEC_CASE_OF ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_backward_exec_io(const ccv_nnc_graph_exec_symbol_info_t* const node, int** const back_input_map, int** const back_output_map, int* const back_input_size, int* const back_output_size)
{
	int i;
	if (node->flags & CCV_NNC_GRAPH_EXEC_CASE_OF)
	{
		*back_input_map = node->outputs;
		*back_input_size = node->output_size;
		for (i = 0; i < node->case_of.argument.offset; i++)
			(*back_output_map)[i] = node->inputs[i];
		const int argument_offset = node->case_of.argument.offset;
		const int argument_size = node->case_of.argument.size;
		// Skip the argument range.
		for (i = argument_offset + argument_size; i < node->input_size; i++)
			(*back_output_map)[i - argument_size] = node->inputs[i];
		*back_output_size = node->input_size - node->case_of.argument.size;
	} else { // if (node->flags & CCV_NNC_GRAPH_EXEC_P_WHILE) {
		*back_input_map = node->outputs;
		*back_input_size = node->output_size;
		*back_output_map = node->inputs;
		*back_output_size = node->input_size;
	}
}