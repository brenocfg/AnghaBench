#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_multiview_t ;
struct TYPE_7__ {int sub_arena_size; TYPE_2__* m_tensor_idx; TYPE_2__* tensor_metadata; struct TYPE_7__** sub_arenas; } ;
typedef  TYPE_1__ ccv_nnc_tensor_arena_t ;
struct TYPE_8__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ CCV_IS_TENSOR_MULTIVIEW (int /*<<< orphan*/ * const) ; 
 scalar_t__ _ccv_nnc_tensor_metadata_get (TYPE_2__*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree (TYPE_1__* const) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_2__*) ; 
 scalar_t__ ccv_array_get (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_multiview_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_nnc_tensor_arena_free(ccv_nnc_tensor_arena_t* const tensor_arena)
{
	// Buffers are inherited from above, no need to dealloc.
	int i;
	for (i = 0; i < tensor_arena->sub_arena_size; i++)
		if (tensor_arena->sub_arenas[i])
			_ccv_nnc_tensor_arena_free(tensor_arena->sub_arenas[i]);
	for (i = 0; i < tensor_arena->m_tensor_idx->rnum; i++)
	{
		ccv_nnc_tensor_multiview_t* const mv = (ccv_nnc_tensor_multiview_t*)_ccv_nnc_tensor_metadata_get(tensor_arena->tensor_metadata, *(int*)ccv_array_get(tensor_arena->m_tensor_idx, i));;
		assert(mv && CCV_IS_TENSOR_MULTIVIEW(mv));
		ccv_nnc_tensor_multiview_free(*mv);
	}
	ccv_array_free(tensor_arena->tensor_metadata);
	ccv_array_free(tensor_arena->m_tensor_idx);
	ccfree(tensor_arena);
}