#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
struct TYPE_16__ {int /*<<< orphan*/  destination; int /*<<< orphan*/  source; } ;
typedef  TYPE_3__ ccv_nnc_tensor_symbol_map_t ;
struct TYPE_17__ {int /*<<< orphan*/  exec_symbol_info; } ;
typedef  TYPE_4__ ccv_nnc_symbolic_graph_t ;
struct TYPE_18__ {int /*<<< orphan*/  d; } ;
typedef  TYPE_5__ const ccv_nnc_graph_exec_symbol_t ;
struct TYPE_14__ {int offset; int size; } ;
struct TYPE_15__ {TYPE_1__ argument; } ;
struct TYPE_19__ {TYPE_2__ case_of; int /*<<< orphan*/  flags; } ;
typedef  TYPE_6__ ccv_nnc_graph_exec_symbol_info_t ;

/* Variables and functions */
 scalar_t__ const CCV_NNC_GRAPH_BACKWARD ; 
 int /*<<< orphan*/  CCV_NNC_GRAPH_EXEC_CASE_OF ; 
 scalar_t__ const CCV_NNC_GRAPH_FORWARD ; 
 int /*<<< orphan*/  CMD_GENERIC () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_cmd (scalar_t__ const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_5__ const ccv_nnc_graph_exec_symbol_new (TYPE_4__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int const,int /*<<< orphan*/ * const,int const,char const* const) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_set_bypasses (TYPE_4__* const,TYPE_3__ const* const,int const) ; 

ccv_nnc_graph_exec_symbol_t ccv_nnc_symbolic_graph_case_of_new(ccv_nnc_symbolic_graph_t* const graph, const uint32_t cmd, const ccv_nnc_tensor_symbol_t* const inputs, const int input_size, const ccv_nnc_tensor_symbol_map_t* const symbol_map, const int symbol_map_size, const char* const name)
{
	assert(cmd == CCV_NNC_GRAPH_FORWARD || cmd == CCV_NNC_GRAPH_BACKWARD);
	// A case_if statement must have meaningful outputs / inputs.
	assert(symbol_map_size > 0);
	ccv_nnc_tensor_symbol_t all_inputs[symbol_map_size * 2 + input_size];
	ccv_nnc_tensor_symbol_t* const outputs = all_inputs + (symbol_map_size + input_size);
	int i;
	for (i = 0; i < symbol_map_size; i++)
		all_inputs[i] = symbol_map[i].source, outputs[i] = symbol_map[i].destination;
	for (i = symbol_map_size; i < symbol_map_size + input_size; i++)
		all_inputs[i] = inputs[i - symbol_map_size];
	// Added one more symbol.
	const ccv_nnc_graph_exec_symbol_t symbol = ccv_nnc_graph_exec_symbol_new(graph, ccv_nnc_cmd(cmd, 0, CMD_GENERIC(), 0), all_inputs, symbol_map_size + input_size, outputs, symbol_map_size, name);
	ccv_nnc_tensor_symbol_set_bypasses(graph, symbol_map, symbol_map_size);
	ccv_nnc_graph_exec_symbol_info_t* const symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, symbol.d);
	symbol_info->flags |= CCV_NNC_GRAPH_EXEC_CASE_OF;
	// We are still free to add more inputs to this graph, it is OK, we are covered by the argument.offset / size.
	symbol_info->case_of.argument.offset = symbol_map_size;
	symbol_info->case_of.argument.size = input_size;
	return symbol;
}