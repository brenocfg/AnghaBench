#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ccv_nnc_tensor_variable_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_param_t ;
struct TYPE_9__ {int reuse_var; TYPE_3__* vars; } ;
typedef  TYPE_2__ ccv_nnc_dynamic_graph_t ;
struct TYPE_10__ {int const rnum; } ;
struct TYPE_8__ {int index; scalar_t__ tensor_view; int /*<<< orphan*/  symbol; int /*<<< orphan*/  info; scalar_t__ alias_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  NO_TENSOR_SYMBOL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int const) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_3__*,TYPE_1__**) ; 

__attribute__((used)) inline static void _ccv_nnc_tensor_variable_init(ccv_nnc_dynamic_graph_t* const graph, ccv_nnc_tensor_variable_t tensor_variable, const ccv_nnc_tensor_param_t info)
{
	tensor_variable->alias_ref = 0;
	tensor_variable->info = info;
	tensor_variable->symbol = NO_TENSOR_SYMBOL;
	tensor_variable->tensor_view = 0;
	if (graph->reuse_var >= 0)
	{
		const int reuse_var = graph->reuse_var;
		assert(reuse_var < graph->vars->rnum);
		tensor_variable->index = reuse_var;
		*(ccv_nnc_tensor_variable_t*)ccv_array_get(graph->vars, reuse_var) = tensor_variable;
		int i;
		graph->reuse_var = -1;
		for (i = reuse_var + 1; i < graph->vars->rnum && graph->reuse_var < 0; i++)
			if (*(ccv_nnc_tensor_variable_t*)ccv_array_get(graph->vars, i) == 0)
				graph->reuse_var = i;
	} else {
		tensor_variable->index = graph->vars->rnum;
		ccv_array_push(graph->vars, &tensor_variable);
	}
}