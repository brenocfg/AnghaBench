#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tensor_arena_t ;
struct TYPE_5__ {struct TYPE_5__* p; int /*<<< orphan*/  dup_tensor_block_ref; } ;
typedef  TYPE_1__ ccv_nnc_symbolic_graph_prep_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_nnc_tensor_multiview_down_find_pos (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,int const,int const,TYPE_1__ const**,TYPE_1__ const* const,int const,int*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int _ccv_nnc_tensor_multiview_gen(ccv_array_t* const tensor_metadata, const int preserve, const int assign_update, const ccv_nnc_tensor_param_t params, const ccv_nnc_symbolic_graph_prep_t* const graph_prep, const ccv_nnc_tensor_arena_t* const tensor_arena, const int block_ref)
{
	// Go to the root of the graph.
	const ccv_nnc_symbolic_graph_prep_t* prep = graph_prep;
	int i;
	for (i = 1; prep->p; i++)
		prep = prep->p;
	// Root graph should have no dup tensor blocks.
	assert(!prep->dup_tensor_block_ref);
	const int c = i;
	const ccv_nnc_symbolic_graph_prep_t* preps[c];
	prep = graph_prep;
	preps[c - 1] = prep;
	for (i = 0; prep->p; i++)
		preps[c - 2 - i] = prep = prep->p;
	int ch[c]; // Use dynamic allocation for array. This is an array to record our selections when recursive from top to bottom.
	memset(ch, 0, sizeof(int) * c);
	int pos = 0;
	_ccv_nnc_tensor_multiview_down_find_pos(tensor_metadata, params, preserve, assign_update, preps, graph_prep, block_ref, ch, 0, &pos);
	assert(ch[c - 1] == 0); // This shouldn't never be modified.
	assert(pos > 0);
	return pos;
}