#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
struct TYPE_5__ {int /*<<< orphan*/  graph; } ;
typedef  TYPE_1__ ccv_nnc_graph_exec_t ;
typedef  int /*<<< orphan*/  const ccv_nnc_graph_exec_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_arena_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NO_GRAPH_EXEC (TYPE_1__ const) ; 
 TYPE_1__ ccv_nnc_graph_exec_from_symbol (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ccv_nnc_graph_exec_set (int /*<<< orphan*/ ,TYPE_1__ const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const ccv_nnc_graph_exec_symbol_copy (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void _ccv_cnnp_model_graph_symbol_exec_set_for_graph_exec_arena(const ccv_nnc_graph_exec_arena_t* const graph_exec_arena, const int parallel_count, const ccv_nnc_graph_exec_symbol_t exec_symbol, const ccv_nnc_cmd_t cmd, ccv_nnc_symbolic_graph_t* const symbolic_graph)
{
	ccv_nnc_graph_exec_t const update_exec = ccv_nnc_graph_exec_from_symbol(graph_exec_arena, exec_symbol);
	if (!CCV_NO_GRAPH_EXEC(update_exec))
		ccv_nnc_graph_exec_set(update_exec.graph, update_exec, cmd);
	int i;
	for (i = 1; i < parallel_count; i++)
	{
		ccv_nnc_graph_exec_symbol_t copy_symbol = ccv_nnc_graph_exec_symbol_copy(symbolic_graph, exec_symbol, i);
		const ccv_nnc_graph_exec_t copy = ccv_nnc_graph_exec_from_symbol(graph_exec_arena, copy_symbol);
		if (!CCV_NO_GRAPH_EXEC(copy))
			ccv_nnc_graph_exec_set(copy.graph, copy, cmd);
	}
}