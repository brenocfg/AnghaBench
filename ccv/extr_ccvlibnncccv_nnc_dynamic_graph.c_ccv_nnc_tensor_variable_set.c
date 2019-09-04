#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_view_t ;
typedef  TYPE_1__* ccv_nnc_tensor_variable_t ;
struct TYPE_6__ {int /*<<< orphan*/  info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  ccv_nnc_dynamic_graph_t ;
struct TYPE_5__ {int /*<<< orphan*/ * tensor_view; int /*<<< orphan*/  info; int /*<<< orphan*/  alias_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void ccv_nnc_tensor_variable_set(ccv_nnc_dynamic_graph_t* const graph, const ccv_nnc_tensor_variable_t tensor_variable, ccv_nnc_tensor_t* const tensor)
{
	assert(!tensor_variable->tensor_view);
	assert(!tensor_variable->alias_ref);
	tensor_variable->info = tensor->info;
	tensor_variable->tensor_view = (ccv_nnc_tensor_view_t*)((uintptr_t)tensor | 1);
}