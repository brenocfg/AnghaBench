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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ khiter_t ;
typedef  scalar_t__ ccv_nnc_tensor_variable_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_variable_graph_bind_t ;
struct TYPE_8__ {int /*<<< orphan*/  stateful_execs; TYPE_4__* ws; int /*<<< orphan*/  tape; TYPE_4__* binds; TYPE_4__* vars; } ;
typedef  TYPE_1__ ccv_nnc_dynamic_graph_t ;
struct TYPE_9__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_tensor_variable_free (TYPE_1__* const,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ccv_nnc_tensor_variable_graph_bind_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccfree (TYPE_1__* const) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_4__*) ; 
 scalar_t__ ccv_array_get (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ccv_nnc_symbolic_graph_free (int /*<<< orphan*/ ) ; 
 scalar_t__ kh_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ kh_end (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kh_exist (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* const kh_val (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stateful_exec ; 

void ccv_nnc_dynamic_graph_free(ccv_nnc_dynamic_graph_t* const graph)
{
	int i;
	for (i = 0; i < graph->vars->rnum; i++)
	{
		ccv_nnc_tensor_variable_t tensor_variable = *(ccv_nnc_tensor_variable_t*)ccv_array_get(graph->vars, i);
		if (tensor_variable)
			_ccv_nnc_tensor_variable_free(graph, tensor_variable, 0);
	}
	ccv_array_free(graph->vars);
	for (i = 0; i < graph->binds->rnum; i++)
		_ccv_nnc_tensor_variable_graph_bind_free((ccv_nnc_tensor_variable_graph_bind_t*)ccv_array_get(graph->binds, i), 0);
	ccv_array_free(graph->binds);
	ccv_nnc_symbolic_graph_free(graph->tape);
	if (graph->ws)
		ccv_array_free(graph->ws);
	khiter_t k;
	for (k = kh_begin(graph->stateful_execs); k != kh_end(graph->stateful_execs); ++k)
	{
		if (!kh_exist(graph->stateful_execs, k))
			continue;
		ccfree(kh_val(graph->stateful_execs, k));
	}
	kh_destroy(stateful_exec, graph->stateful_execs);
	ccfree(graph);
}