#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int input_size; int const* inputs; int output_size; int const* outputs; } ;
typedef  TYPE_1__ ccv_nnc_graph_exec_symbol_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const* const) ; 

__attribute__((used)) static int _ccv_nnc_is_symbolic_graph_exec_input_or_output(const int p_ref, const ccv_nnc_graph_exec_symbol_info_t *const node)
{
	int i;
	int is_input = 0;
	assert(node);
	for (i = 0; i < node->input_size && !is_input; i++)
		if (p_ref == node->inputs[i])
			is_input = 1;
	int is_output = 0;
	for (i = 0; i < node->output_size && !is_output; i++)
		if (p_ref == node->outputs[i])
			is_output = 1;
	// Prefer it is an output if it is both the input and the output.
	if (is_output)
		return 1;
	if (is_input)
		return -1;
	return 0;
}