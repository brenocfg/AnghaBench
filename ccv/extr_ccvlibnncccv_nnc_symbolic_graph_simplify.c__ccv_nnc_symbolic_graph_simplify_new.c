#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_info_t ;
struct TYPE_10__ {TYPE_6__* exec_symbol_info; TYPE_1__* tensor_symbol_info; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_t ;
struct TYPE_11__ {int tensor_symbol_info_size; int exec_symbol_info_size; int* output_execs; scalar_t__ exec_dead; scalar_t__ tensor_dead; int /*<<< orphan*/ * exec_symbol_info; int /*<<< orphan*/ * tensor_symbol_info; int /*<<< orphan*/  visit; TYPE_2__* graph; } ;
typedef  TYPE_3__ ccv_nnc_symbolic_graph_simplify_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_12__ {int rnum; } ;
struct TYPE_9__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ cccalloc (int,int) ; 
 scalar_t__ ccmalloc (int) ; 
 scalar_t__ ccv_array_get (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_graph_visit_new (TYPE_2__* const,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_symbol_infer (TYPE_2__* const,int /*<<< orphan*/ ,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ccv_nnc_symbolic_graph_simplify_t* _ccv_nnc_symbolic_graph_simplify_new(ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_graph_exec_symbol_t* const sources, const int source_size, const ccv_nnc_graph_exec_symbol_t* const destinations, const int destination_size)
{
	ccv_nnc_symbolic_graph_simplify_t* const simplify = (ccv_nnc_symbolic_graph_simplify_t*)ccmalloc(sizeof(ccv_nnc_symbolic_graph_simplify_t));
	simplify->graph = graph;
	simplify->visit = ccv_nnc_graph_visit_new(graph, (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, 0), graph->exec_symbol_info->rnum, sources, source_size, destinations, destination_size, 0);
	simplify->tensor_symbol_info = (ccv_nnc_tensor_symbol_info_t*)ccmalloc(sizeof(ccv_nnc_tensor_symbol_info_t) * graph->tensor_symbol_info->rnum);
	simplify->exec_symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccmalloc(sizeof(ccv_nnc_graph_exec_symbol_info_t) * graph->exec_symbol_info->rnum);
	ccv_nnc_symbolic_graph_symbol_infer(graph, simplify->visit, sources, source_size, destinations, destination_size, 0, 0, simplify->tensor_symbol_info, simplify->exec_symbol_info);
	simplify->tensor_symbol_info_size = graph->tensor_symbol_info->rnum;
	simplify->exec_symbol_info_size = graph->exec_symbol_info->rnum;
	simplify->exec_dead = cccalloc(((simplify->exec_symbol_info_size + 31) >> 5) + ((simplify->tensor_symbol_info_size + 31) >> 5), sizeof(uint32_t));
	simplify->tensor_dead = simplify->exec_dead + ((simplify->exec_symbol_info_size + 31) >> 5);
	simplify->output_execs = (int*)ccmalloc(sizeof(int) * simplify->tensor_symbol_info_size);
	return simplify;
}