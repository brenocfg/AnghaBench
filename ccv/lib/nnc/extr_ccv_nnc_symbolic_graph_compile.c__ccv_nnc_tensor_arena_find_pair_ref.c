#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
struct TYPE_3__ {intptr_t graph_ref; int const vt_tensor_size; int sub_arena_size; struct TYPE_3__** sub_arenas; int /*<<< orphan*/ ** vt_tensors; } ;
typedef  TYPE_1__ ccv_nnc_tensor_arena_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static ccv_nnc_tensor_t* _ccv_nnc_tensor_arena_find_pair_ref(const ccv_nnc_tensor_arena_t* const tensor_arena, const ccv_nnc_symbolic_graph_t* const graph, const int pair_ref)
{
	assert(graph);
	if ((intptr_t)graph == tensor_arena->graph_ref)
	{
		assert(pair_ref >= 0 && pair_ref < tensor_arena->vt_tensor_size);
		return tensor_arena->vt_tensors[pair_ref];
	}
	int i;
	for (i = 0; i < tensor_arena->sub_arena_size; i++)
		if (tensor_arena->sub_arenas[i])
		{
			ccv_nnc_tensor_t* const tensor = _ccv_nnc_tensor_arena_find_pair_ref(tensor_arena->sub_arenas[i], graph, pair_ref);
			if (tensor)
				return tensor;
		}
	return 0;
}