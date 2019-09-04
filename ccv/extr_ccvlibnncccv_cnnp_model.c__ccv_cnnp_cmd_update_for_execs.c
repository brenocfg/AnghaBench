#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
struct TYPE_7__ {int parallel_count; int /*<<< orphan*/ * graph; int /*<<< orphan*/ * graph_exec_arena; } ;
typedef  TYPE_1__ ccv_nnc_graph_exec_update_t ;
struct TYPE_8__ {int /*<<< orphan*/  graph; } ;
typedef  TYPE_2__ const ccv_nnc_graph_exec_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_arena_t ;
typedef  int /*<<< orphan*/  ccv_nnc_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NO_GRAPH_EXEC (TYPE_2__ const) ; 
 TYPE_2__ const ccv_nnc_graph_exec_from_symbol (int /*<<< orphan*/ * const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ccv_nnc_graph_exec_set (int /*<<< orphan*/ ,TYPE_2__ const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ccv_nnc_graph_exec_set_hint (int /*<<< orphan*/ ,TYPE_2__ const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  const ccv_nnc_graph_exec_symbol_copy (int /*<<< orphan*/  const* const,int /*<<< orphan*/  const,int) ; 

__attribute__((used)) static void _ccv_cnnp_cmd_update_for_execs(void* const context, const ccv_nnc_graph_exec_symbol_t symbol, const ccv_nnc_cmd_t cmd, const ccv_nnc_hint_t hint)
{
	ccv_nnc_graph_exec_update_t* const graph_exec_update = (ccv_nnc_graph_exec_update_t*)context;
	ccv_nnc_graph_exec_arena_t* const graph_exec_arena = graph_exec_update->graph_exec_arena;
	ccv_nnc_graph_exec_t graph_exec = ccv_nnc_graph_exec_from_symbol(graph_exec_arena, symbol);
	ccv_nnc_graph_exec_set(graph_exec.graph, graph_exec, cmd);
	ccv_nnc_graph_exec_set_hint(graph_exec.graph, graph_exec, hint);
	const ccv_nnc_symbolic_graph_t* const graph = graph_exec_update->graph;
	const int parallel_count = graph_exec_update->parallel_count;
	int i;
	for (i = 1; i < parallel_count; i++)
	{
		const ccv_nnc_graph_exec_t copy = ccv_nnc_graph_exec_from_symbol(graph_exec_arena, ccv_nnc_graph_exec_symbol_copy(graph, symbol, i));
		if (!CCV_NO_GRAPH_EXEC(copy))
		{
			ccv_nnc_graph_exec_set(copy.graph, copy, cmd);
			ccv_nnc_graph_exec_set_hint(copy.graph, copy, hint);
		}
	}
}