#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int exec; } ;
struct TYPE_11__ {TYPE_1__ reuse; TYPE_7__* exec_symbol_info; TYPE_7__* destinations; TYPE_7__* sources; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_t ;
struct TYPE_12__ {int d; TYPE_2__* const graph; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_symbol_t ;
struct TYPE_13__ {int /*<<< orphan*/  flags; TYPE_7__* outgoings; } ;
typedef  TYPE_4__ ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_14__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NNC_GRAPH_EXEC_DEAD ; 
 int /*<<< orphan*/  CCV_NNC_GRAPH_EXEC_IS_DEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_exec_symbol_free (TYPE_4__* const,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_array_add_unique_int (TYPE_7__*,int) ; 
 scalar_t__ ccv_array_get (TYPE_7__*,int) ; 

void ccv_nnc_graph_exec_symbol_free(ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_graph_exec_symbol_t symbol)
{
	assert(graph == symbol.graph);
	assert(symbol.d < graph->exec_symbol_info->rnum);
	// If any of the exec symbol have reference to it, has to remove that.
	int i, j, k;
	ccv_nnc_graph_exec_symbol_info_t* const free_symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, symbol.d);
	for (i = 0; i < graph->exec_symbol_info->rnum; i++)
		if (i != symbol.d)
		{
			ccv_nnc_graph_exec_symbol_info_t* const symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, i);
			if (symbol_info->outgoings)
				for (j = 0; j < symbol_info->outgoings->rnum; j++)
					if (*(int*)ccv_array_get(symbol_info->outgoings, j) == symbol.d)
					{
						if (j < symbol_info->outgoings->rnum - 1)
							*(int*)ccv_array_get(symbol_info->outgoings, j) = *(int*)ccv_array_get(symbol_info->outgoings, symbol_info->outgoings->rnum - 1);
						--symbol_info->outgoings->rnum;
						if (free_symbol_info->outgoings)
							for (k = 0; k < free_symbol_info->outgoings->rnum; k++)
								ccv_array_add_unique_int(symbol_info->outgoings, *(int*)ccv_array_get(free_symbol_info->outgoings, k));
						break;
					}
		}
	// Deallocate any memory for exec symbol.
	_ccv_nnc_graph_exec_symbol_free(free_symbol_info, 1);
	free_symbol_info->flags = CCV_NNC_GRAPH_EXEC_DEAD; // Mark this as dead.
	// If everything from symbol.d to the end of the graph is dead, we can reclaim this memory.
	for (i = graph->exec_symbol_info->rnum - 1; i >= 0; i--)
		if (!CCV_NNC_GRAPH_EXEC_IS_DEAD(((ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, i))->flags))
		{
			graph->exec_symbol_info->rnum = i + 1;
			break;
		}
	// Loop over sources and destinations to remove this.
	if (graph->sources)
		for (i = 0; i < graph->sources->rnum; i++)
			if (*(int*)ccv_array_get(graph->sources, i) == symbol.d)
			{
				if (i < graph->sources->rnum - 1)
					*(int*)ccv_array_get(graph->sources, i) = *(int*)ccv_array_get(graph->sources, graph->sources->rnum - 1);
				--graph->sources->rnum;
				break;
			}
	if (graph->destinations)
		for (i = 0; i < graph->destinations->rnum; i++)
			if (*(int*)ccv_array_get(graph->destinations, i) == symbol.d)
			{
				if (i < graph->destinations->rnum - 1)
					*(int*)ccv_array_get(graph->destinations, i) = *(int*)ccv_array_get(graph->destinations, graph->destinations->rnum - 1);
				--graph->destinations->rnum;
				break;
			}
	if (symbol.d < graph->exec_symbol_info->rnum &&
		(symbol.d < graph->reuse.exec || graph->reuse.exec < 0))
		graph->reuse.exec = symbol.d;
	else if (graph->reuse.exec >= graph->exec_symbol_info->rnum)
		graph->reuse.exec = -1;
}