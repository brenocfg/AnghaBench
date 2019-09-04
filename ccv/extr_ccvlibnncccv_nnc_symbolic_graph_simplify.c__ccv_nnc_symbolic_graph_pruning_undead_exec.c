#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  unsigned int uint32_t ;
struct TYPE_7__ {unsigned int* exec_dead; unsigned int* tensor_dead; TYPE_1__* graph; TYPE_3__* exec_symbol_info; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_simplify_t ;
struct TYPE_9__ {scalar_t__ cmd; } ;
struct TYPE_8__ {int input_size; int* inputs; int output_size; int* outputs; TYPE_4__ cmd; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_symbol_info_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;
struct TYPE_6__ {int /*<<< orphan*/  exec_symbol_info; } ;

/* Variables and functions */
 scalar_t__ CCV_NNC_CUSTOM_BACKWARD ; 
 scalar_t__ CCV_NNC_CUSTOM_FORWARD ; 
 scalar_t__ CCV_NNC_GRAPH_BACKWARD ; 
 scalar_t__ CCV_NNC_GRAPH_FORWARD ; 
 void* CCV_NNC_NO_TENSOR_SYMBOL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ccv_array_push (int /*<<< orphan*/ * const,int const*) ; 
 int ccv_max (int,int const) ; 
 int ccv_nnc_cmd_bitmask (TYPE_4__,int,int,int*,int const,int*,int const) ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_pruning_undead_exec(ccv_nnc_symbolic_graph_simplify_t* const simplify, const int exec_idx, uint32_t* const tensor_visited, ccv_array_t* const next)
{
	assert(exec_idx >= 0);
	uint32_t* const exec_dead = simplify->exec_dead;
	uint32_t* const tensor_dead = simplify->tensor_dead;
	exec_dead[exec_idx >> 5] &= ~(1u << (exec_idx & 0x1f)); // Undead the exec.
	ccv_nnc_graph_exec_symbol_info_t* const exec_symbol_info = simplify->exec_symbol_info + exec_idx;
	int i;
	if (exec_symbol_info->cmd.cmd == CCV_NNC_GRAPH_FORWARD ||
		exec_symbol_info->cmd.cmd == CCV_NNC_GRAPH_BACKWARD ||
		exec_symbol_info->cmd.cmd == CCV_NNC_CUSTOM_FORWARD ||
		exec_symbol_info->cmd.cmd == CCV_NNC_CUSTOM_BACKWARD)
	{
		// All of its inputs / outputs need to be undead for these commands.
		for (i = 0; i < exec_symbol_info->input_size; i++)
		{
			const int d = exec_symbol_info->inputs[i];
			if (d >= 0 && !(tensor_visited[d >> 5] & (1u << (d & 0x1f))))
			{
				ccv_array_push(next, &d); // Push to the next round to be undead.
				tensor_visited[d >> 5] |= (1u << (d & 0x1f));
			}
		}
		for (i = 0; i < exec_symbol_info->output_size; i++)
		{
			const int d = exec_symbol_info->outputs[i];
			if (d >= 0 && !(tensor_visited[d >> 5] & (1u << (d & 0x1f))))
			{
				ccv_array_push(next, &d); // Push to the next round to be undead.
				tensor_visited[d >> 5] |= (1u << (d & 0x1f));
			}
		}
		return;
	}
	// Go through the input / output, to make sure that all of them can be available.
	const int input_bitmask_size = (exec_symbol_info->input_size + 63) >> 6;
	const int output_bitmask_size = (exec_symbol_info->output_size + 63) >> 6;
	uint64_t input_bitmasks[ccv_max(1, input_bitmask_size)];
	for (i = 0; i < input_bitmask_size; i++)
		input_bitmasks[i] = 0;
	uint64_t output_bitmasks[ccv_max(1, output_bitmask_size)];
	for (i = 0; i < output_bitmask_size; i++)
		output_bitmasks[i] = 0;
	for (i = 0; i < exec_symbol_info->input_size; i++)
		if (exec_symbol_info->inputs[i] >= 0)
			input_bitmasks[i >> 6] |= ((uint64_t)1 << (i & 63));
	for (i = 0; i < exec_symbol_info->output_size; i++)
		if (exec_symbol_info->outputs[i] >= 0)
			output_bitmasks[i >> 6] |= ((uint64_t)1 << (i & 63));
	// First, mark everything with bitmasks, and verify it works.
	assert(ccv_nnc_cmd_bitmask(exec_symbol_info->cmd, exec_symbol_info->input_size, exec_symbol_info->output_size, input_bitmasks, input_bitmask_size, output_bitmasks, output_bitmask_size));
	int flag;
	do {
		flag = 0;
		// Try to eliminate one at a time. Go over output first.
		for (i = 0; i < exec_symbol_info->output_size; i++)
		{
			const int d = exec_symbol_info->outputs[i];
			// If this tensor currently is marked as dead, try to see whether it works when we don't have this tensor at all.
			if (d >= 0 && (tensor_dead[d >> 5] & (1u << (d & 0x1f))) &&
				(output_bitmasks[i >> 6] & ((uint64_t)1 << (i & 63))))
			{
				output_bitmasks[i >> 6] &= ~((uint64_t)1 << (i & 63));
				if (ccv_nnc_cmd_bitmask(exec_symbol_info->cmd, exec_symbol_info->input_size, exec_symbol_info->output_size, input_bitmasks, input_bitmask_size, output_bitmasks, output_bitmask_size))
					flag = 1;
				else // Reset the bitmask.
					output_bitmasks[i >> 6] |= ((uint64_t)1 << (i & 63));
			}
		}
		// For inputs, no matter if it s dead or not, we try to limit our input to the smallest number.
		for (i = 0; i < exec_symbol_info->input_size; i++)
		{
			const int d = exec_symbol_info->inputs[i];
			// If this tensor currently is marked as dead, try to see whether it works when we don't have this tensor at all.
			if (d >= 0 && (input_bitmasks[i >> 6] & ((uint64_t)1 << (i & 63))))
			{
				input_bitmasks[i >> 6] &= ~((uint64_t)1 << (i & 63));
				if (ccv_nnc_cmd_bitmask(exec_symbol_info->cmd, exec_symbol_info->input_size, exec_symbol_info->output_size, input_bitmasks, input_bitmask_size, output_bitmasks, output_bitmask_size))
					flag = 1;
				else // Reset the bitmask.
					input_bitmasks[i >> 6] |= ((uint64_t)1 << (i & 63));
			}
		}
	} while (flag);
	// Now we know which one to keep, which one to undead.
	for (i = 0; i < exec_symbol_info->input_size; i++)
		if (input_bitmasks[i >> 6] & ((uint64_t)1 << (i & 63)))
		{
			const int d = exec_symbol_info->inputs[i];
			if (d >= 0 && !(tensor_visited[d >> 5] & (1u << (d & 0x1f))))
			{
				ccv_array_push(next, &d); // Push to the next round to be undead.
				tensor_visited[d >> 5] |= (1u << (d & 0x1f));
			}
		} else {
			// Clean up the inputs.
			exec_symbol_info->inputs[i] = CCV_NNC_NO_TENSOR_SYMBOL;
			assert(((ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(simplify->graph->exec_symbol_info, exec_idx))->inputs == exec_symbol_info->inputs);
		}
	for (i = 0; i < exec_symbol_info->output_size; i++)
		if (output_bitmasks[i >> 6] & ((uint64_t)1 << (i & 63)))
		{
			const int d = exec_symbol_info->outputs[i];
			if (d >= 0 && !(tensor_visited[d >> 5] & (1u << (d & 0x1f))))
			{
				ccv_array_push(next, &d); // Push to the next round to be undead.
				tensor_visited[d >> 5] |= (1u << (d & 0x1f));
			}
		} else {
			// Clean up the outputs.
			exec_symbol_info->outputs[i] = CCV_NNC_NO_TENSOR_SYMBOL;
			assert(((ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(simplify->graph->exec_symbol_info, exec_idx))->outputs == exec_symbol_info->outputs);
		}
}