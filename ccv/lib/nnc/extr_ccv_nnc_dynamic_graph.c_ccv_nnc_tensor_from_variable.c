#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ u8; } ;
struct TYPE_16__ {scalar_t__ off; TYPE_1__ data; } ;
typedef  TYPE_3__ ccv_nnc_tensor_view_t ;
typedef  TYPE_4__* ccv_nnc_tensor_variable_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
struct TYPE_18__ {int /*<<< orphan*/  vars; } ;
typedef  TYPE_5__ ccv_nnc_dynamic_graph_t ;
struct TYPE_19__ {scalar_t__* dim; } ;
struct TYPE_17__ {int alias_ref; scalar_t__* ofs; scalar_t__* inc; TYPE_3__* tensor_view; TYPE_7__ info; } ;
struct TYPE_15__ {scalar_t__ u8; } ;
struct TYPE_13__ {TYPE_2__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NNC_IS_EXTERN_TENSOR_VIEW (TYPE_3__* const) ; 
 int CCV_NNC_MAX_DIM_ALLOC ; 
 TYPE_10__* CCV_NNC_TENSOR_VIEW (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ ,int const) ; 
 scalar_t__ ccv_nnc_tensor_new (scalar_t__,TYPE_7__,int /*<<< orphan*/ ) ; 
 TYPE_3__* ccv_nnc_tensor_view_new (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ memcmp (scalar_t__*,scalar_t__*,int) ; 

ccv_nnc_tensor_t* ccv_nnc_tensor_from_variable(ccv_nnc_dynamic_graph_t* const graph, const ccv_nnc_tensor_variable_t tensor_variable)
{
	if (tensor_variable->tensor_view)
	{
		if (tensor_variable->alias_ref)
		{
			const int alias_ref = tensor_variable->alias_ref - 1;
			assert(alias_ref >= 0);
			ccv_nnc_tensor_variable_t variable_to = *(ccv_nnc_tensor_variable_t*)ccv_array_get(graph->vars, alias_ref);
			ccv_nnc_tensor_view_t* const tv = tensor_variable->tensor_view; // We cannot have an alias with custom set tensor, otherwise the pointer update is invalid.
			assert(!CCV_NNC_IS_EXTERN_TENSOR_VIEW(tv));
			// Update the tensor_view pointer every time access it, because the underlying variable it alias to have changed.
			tv->data.u8 = CCV_NNC_TENSOR_VIEW(variable_to->tensor_view)->data.u8 + tv->off;
		}
		return (ccv_nnc_tensor_t*)CCV_NNC_TENSOR_VIEW(tensor_variable->tensor_view);
	}
	if (!tensor_variable->alias_ref)
	{
		tensor_variable->tensor_view = (ccv_nnc_tensor_view_t*)ccv_nnc_tensor_new(0, tensor_variable->info, 0);
		return (ccv_nnc_tensor_t*)tensor_variable->tensor_view;
	}
	const int alias_ref = tensor_variable->alias_ref - 1;
	assert(alias_ref >= 0);
	ccv_nnc_tensor_variable_t variable_to = *(ccv_nnc_tensor_variable_t*)ccv_array_get(graph->vars, alias_ref);
	assert(!variable_to->alias_ref);
	if (!variable_to->tensor_view)
		variable_to->tensor_view = (ccv_nnc_tensor_view_t*)ccv_nnc_tensor_new(0, variable_to->info, 0);
	int no_ofs = 1;
	int i;
	for (i = 0; no_ofs && i < CCV_NNC_MAX_DIM_ALLOC; i++)
		no_ofs = (tensor_variable->ofs[i] == 0);
	int no_inc = 1;
	for (i = 0; no_inc && i < CCV_NNC_MAX_DIM_ALLOC; i++)
		no_inc = (tensor_variable->inc[i] == 0);
	if (!no_inc)
		no_inc = (memcmp(tensor_variable->inc, tensor_variable->info.dim, sizeof(int) * CCV_NNC_MAX_DIM_ALLOC) == 0);
	if (no_ofs && no_inc)
		tensor_variable->tensor_view = (ccv_nnc_tensor_view_t*)ccv_nnc_tensor_new(CCV_NNC_TENSOR_VIEW(variable_to->tensor_view)->data.u8, tensor_variable->info, 0);
	else
		tensor_variable->tensor_view = ccv_nnc_tensor_view_new((ccv_nnc_tensor_t*)CCV_NNC_TENSOR_VIEW(variable_to->tensor_view), tensor_variable->info.dim, tensor_variable->ofs, no_inc ? tensor_variable->info.dim : tensor_variable->inc);
	return (ccv_nnc_tensor_t*)tensor_variable->tensor_view;
}