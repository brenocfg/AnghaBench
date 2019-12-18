#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ u8; } ;
typedef  TYPE_2__ ccv_numeric_data_t ;
struct TYPE_15__ {TYPE_2__ data; } ;
typedef  TYPE_3__ ccv_nnc_tensor_t ;
struct TYPE_16__ {size_t d; scalar_t__ graph; } ;
typedef  TYPE_4__ ccv_nnc_tensor_symbol_t ;
struct TYPE_17__ {intptr_t graph_ref; size_t vt_tensor_size; int* vt_alias_refs; scalar_t__* vt_alias_offs; TYPE_1__** vt_tensors; TYPE_6__** vt_alias_tos; TYPE_2__* pb_vt_tensors; } ;
typedef  TYPE_5__ ccv_nnc_tensor_arena_t ;
struct TYPE_18__ {int rnum; } ;
typedef  TYPE_6__ ccv_array_t ;
struct TYPE_13__ {TYPE_2__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cccalloc (size_t,int) ; 
 scalar_t__ ccv_array_get (TYPE_6__*,int) ; 
 TYPE_6__* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_6__*,int*) ; 

void ccv_nnc_tensor_bind_symbol(ccv_nnc_tensor_arena_t* const tensor_arena, const ccv_nnc_tensor_symbol_t symbol, const ccv_nnc_tensor_t* const tensor)
{
	assert(tensor_arena->graph_ref == (intptr_t)symbol.graph);
	assert(symbol.d < tensor_arena->vt_tensor_size);
	// Only allocate this on-demand because not everyone uses this ccv_nnc_tensor_bind_symbol method.
	int i;
	if (!tensor_arena->pb_vt_tensors)
	{
		tensor_arena->pb_vt_tensors = (ccv_numeric_data_t*)cccalloc(tensor_arena->vt_tensor_size, sizeof(ccv_numeric_data_t));
		for (i = 0; i < tensor_arena->vt_tensor_size; i++)
			if (tensor_arena->vt_tensors[i])
				tensor_arena->pb_vt_tensors[i] = tensor_arena->vt_tensors[i]->data;
	}
	if (!tensor_arena->vt_alias_tos)
	{
		tensor_arena->vt_alias_tos = (ccv_array_t**)cccalloc(tensor_arena->vt_tensor_size, sizeof(ccv_array_t*));
		for (i = 0; i < tensor_arena->vt_tensor_size; i++)
			if (tensor_arena->vt_alias_refs[i])
			{
				const int alias_ref = tensor_arena->vt_alias_refs[i] - 1;
				if (!tensor_arena->vt_alias_tos[alias_ref])
					tensor_arena->vt_alias_tos[alias_ref] = ccv_array_new(sizeof(int), 1, 0);
				ccv_array_push(tensor_arena->vt_alias_tos[alias_ref], &i);
			}
	}
	tensor_arena->vt_tensors[symbol.d]->data = tensor->data;
	if (tensor_arena->vt_alias_tos[symbol.d])
		for (i = 0; i < tensor_arena->vt_alias_tos[symbol.d]->rnum; i++)
		{
			const int d = *(int*)ccv_array_get(tensor_arena->vt_alias_tos[symbol.d], i);
			tensor_arena->vt_tensors[d]->data.u8 = tensor->data.u8 + tensor_arena->vt_alias_offs[d];
		}
}