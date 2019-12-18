#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ccv_nnc_tensor_variable_t ;
struct TYPE_11__ {scalar_t__ tensor_view; scalar_t__ destinations; scalar_t__ sources; int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_nnc_tensor_variable_graph_bind_t ;
struct TYPE_12__ {int d; } ;
typedef  TYPE_3__ ccv_nnc_tensor_symbol_t ;
struct TYPE_13__ {TYPE_5__* binds; } ;
typedef  TYPE_4__ ccv_nnc_dynamic_graph_t ;
struct TYPE_14__ {int rnum; } ;
struct TYPE_10__ {int /*<<< orphan*/  index; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NNC_TENSOR_NO_VARIABLE ; 
 int /*<<< orphan*/  ccv_array_free (scalar_t__) ; 
 scalar_t__ ccv_array_get (TYPE_5__*,int) ; 
 int /*<<< orphan*/  ccv_array_resize (TYPE_5__*,int) ; 

__attribute__((used)) static void _ccv_nnc_tensor_symbol_extra_new(ccv_nnc_dynamic_graph_t* const graph, const ccv_nnc_tensor_variable_t tensor_variable, const ccv_nnc_tensor_symbol_t symbol)
{
	if (symbol.d >= graph->binds->rnum)
	{
		const int rnum = graph->binds->rnum;
		ccv_array_resize(graph->binds, symbol.d + 1);
		int i;
		for (i = rnum; i < graph->binds->rnum; i++)
			((ccv_nnc_tensor_variable_graph_bind_t*)ccv_array_get(graph->binds, i))->index = CCV_NNC_TENSOR_NO_VARIABLE;
	}
	ccv_nnc_tensor_variable_graph_bind_t* const bind = (ccv_nnc_tensor_variable_graph_bind_t*)ccv_array_get(graph->binds, symbol.d);
	bind->type = tensor_variable->type;
	bind->index = tensor_variable->index;
	if (bind->sources)
		ccv_array_free(bind->sources);
	bind->sources = 0;
	if (bind->destinations)
		ccv_array_free(bind->destinations);
	bind->destinations = 0;
	bind->tensor_view = 0;
}