#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ d; } ;
struct ccv_nnc_tensor_variable_s {scalar_t__ alias_ref; int index; TYPE_1__ symbol; int /*<<< orphan*/  info; int /*<<< orphan*/  inc; int /*<<< orphan*/  ofs; } ;
typedef  struct ccv_nnc_tensor_variable_s* ccv_nnc_tensor_variable_t ;
struct TYPE_8__ {int index; } ;
typedef  TYPE_2__ ccv_nnc_tensor_variable_graph_bind_t ;
struct TYPE_9__ {int /*<<< orphan*/  binds; int /*<<< orphan*/  vars; } ;
typedef  TYPE_3__ ccv_nnc_dynamic_graph_t ;

/* Variables and functions */
 scalar_t__ CCV_NNC_NO_TENSOR_SYMBOL ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ccv_nnc_tensor_variable_s* ccv_nnc_tensor_variable_alias_new (TYPE_3__* const,struct ccv_nnc_tensor_variable_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ccv_nnc_tensor_variable_s* ccv_nnc_tensor_variable_new (TYPE_3__* const,int /*<<< orphan*/ ) ; 

ccv_nnc_tensor_variable_t ccv_nnc_tensor_variable_exchange_new(ccv_nnc_dynamic_graph_t* const graph, ccv_nnc_tensor_variable_t tensor_variable)
{
	struct ccv_nnc_tensor_variable_s x = *tensor_variable;
	ccv_nnc_tensor_variable_t new_variable;
	// Need to handle alias.
	if (x.alias_ref)
		new_variable = ccv_nnc_tensor_variable_alias_new(graph, *(ccv_nnc_tensor_variable_t*)ccv_array_get(graph->vars, x.alias_ref - 1), x.ofs, x.inc, x.info);
	else
		new_variable = ccv_nnc_tensor_variable_new(graph, x.info);
	*tensor_variable = *new_variable;
	*new_variable = x;
	// The index should be the same though.
	const int index = new_variable->index;
	new_variable->index = tensor_variable->index;
	if (new_variable->symbol.d != CCV_NNC_NO_TENSOR_SYMBOL)
	{
		ccv_nnc_tensor_variable_graph_bind_t* const bind = (ccv_nnc_tensor_variable_graph_bind_t*)ccv_array_get(graph->binds, new_variable->symbol.d);
		bind->index = new_variable->index;
	}
	tensor_variable->index = index;
	return new_variable;
}