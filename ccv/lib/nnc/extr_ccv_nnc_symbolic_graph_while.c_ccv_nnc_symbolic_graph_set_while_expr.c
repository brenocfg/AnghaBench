#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
struct TYPE_10__ {int exec_idx; int breakpoint_size; int /*<<< orphan*/ * breakpoints; TYPE_1__* p; } ;
typedef  TYPE_3__ ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_while_f ;
typedef  int /*<<< orphan*/  ccv_nnc_graph_exec_symbol_t ;
struct TYPE_9__ {void* data; int* inputs; int input_size; int /*<<< orphan*/  expr; } ;
struct TYPE_11__ {TYPE_2__ p_while; } ;
typedef  TYPE_4__ ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_12__ {int const rnum; } ;
struct TYPE_8__ {TYPE_7__* exec_symbol_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccmalloc (int) ; 
 scalar_t__ ccv_array_get (TYPE_7__*,int const) ; 
 int ccv_nnc_tensor_symbol_map_raw (TYPE_3__* const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const* const,int) ; 

void ccv_nnc_symbolic_graph_set_while_expr(ccv_nnc_symbolic_graph_t* const while_graph, const ccv_nnc_graph_while_f while_expr, const void* const while_data, const ccv_nnc_tensor_symbol_t* const inputs, const int input_size, const ccv_nnc_graph_exec_symbol_t* const breakpoints, const int breakpoint_size)
{
	const int exec_idx = while_graph->exec_idx - 1;
	assert(exec_idx >= 0 && exec_idx < while_graph->p->exec_symbol_info->rnum);
	ccv_nnc_graph_exec_symbol_info_t* const exec_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(while_graph->p->exec_symbol_info, exec_idx);
	exec_info->p_while.data = while_data;
	exec_info->p_while.expr = while_expr;
	int i;
	if (input_size > 0)
	{
		assert(inputs);
		exec_info->p_while.inputs = (int*)ccmalloc(sizeof(int) * input_size);
		for (i = 0; i < input_size; i++)
			exec_info->p_while.inputs[i] = ccv_nnc_tensor_symbol_map_raw(while_graph, inputs[i]);
		exec_info->p_while.input_size = input_size;
	}
	if (breakpoint_size > 0)
	{
		assert(breakpoints);
		while_graph->breakpoint_size = breakpoint_size;
		while_graph->breakpoints = (ccv_nnc_graph_exec_symbol_t*)ccmalloc(sizeof(ccv_nnc_graph_exec_symbol_t) * breakpoint_size);
		memcpy(while_graph->breakpoints, breakpoints, sizeof(ccv_nnc_graph_exec_symbol_t) * breakpoint_size);
	}
}