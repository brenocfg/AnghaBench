#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  ccv_sparse_matrix_t ;
struct TYPE_9__ {int const type; scalar_t__ const size; TYPE_2__ const* const dup_p_refs; } ;
typedef  TYPE_1__ ccv_nnc_tensor_block_t ;
struct TYPE_10__ {scalar_t__ rnum; } ;
typedef  TYPE_2__ ccv_array_t ;

/* Variables and functions */
 int _ccv_nnc_tensor_block_a_after_b_inclusively (int /*<<< orphan*/  const* const,TYPE_2__ const*,TYPE_2__ const* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_2__ const* const,int) ; 
 scalar_t__ llabs (scalar_t__) ; 

__attribute__((used)) static int _ccv_nnc_anonymous_tensor_block_from_free_list(const ccv_nnc_tensor_block_t* const tensor_blocks, const int tensor_block_size, const ccv_array_t* const anonymous_block_free_list, const int anonymous_block_free_list_cap, const int type, const uint64_t size, const ccv_sparse_matrix_t* const exec_dep, const ccv_array_t* const dup_p_refs)
{
	if (!anonymous_block_free_list || !anonymous_block_free_list_cap)
		return tensor_block_size;
	int i;
	const int no_dup_p_refs = (!dup_p_refs || !dup_p_refs->rnum);
	int found_idx = tensor_block_size;
	for (i = 0; i < anonymous_block_free_list_cap; i++)
	{
		const int idx = *(int*)ccv_array_get(anonymous_block_free_list, i);
		assert(idx < tensor_block_size);
		// If the type doesn't match, ignore.
		if (tensor_blocks[idx].type != type)
			continue;
		// Heuristic about how to select the best tensor block to move forward.
		// If the size is larger, and no dup_p_refs, found, I cannot do better than this, just return directly.
		if (tensor_blocks[idx].size >= size)
		{
			if (no_dup_p_refs)
				return idx;
			// Otherwise, only if the current tensor block's dup_p_refs is after (or at) the dup_p_refs,
			// then we cannot do better than this, if that is the case, just return.
			if (tensor_blocks[idx].dup_p_refs && tensor_blocks[idx].dup_p_refs->rnum &&
				_ccv_nnc_tensor_block_a_after_b_inclusively(exec_dep, tensor_blocks[idx].dup_p_refs, dup_p_refs))
				return idx;
		}
		int64_t found_idx_size_diff;
		int64_t idx_size_diff;
		if (found_idx == tensor_block_size || // If no found_idx yet, set the current one to be the found one, and continue.
			// Now, compare whether this one or the found_idx one is better.
			// At this point, there is no point of comparing the dup_p_refs, we only care about which one
			// is closer to the size we request. Only on a tie, dup_p_refs or not is important again.
			(found_idx_size_diff = llabs((int64_t)tensor_blocks[found_idx].size - (int64_t)size)) < (idx_size_diff = llabs((int64_t)tensor_blocks[idx].size - (int64_t)size)))
		{
			found_idx = idx;
			continue;
		}
		// No need to update if found_idx is better than idx.
		if (found_idx_size_diff > idx_size_diff)
			continue;
		// We bias towards the bigger one in case of similar.
		if (found_idx_size_diff == idx_size_diff && tensor_blocks[idx].size > tensor_blocks[found_idx].size)
		{
			found_idx = idx;
			continue;
		}
		assert(tensor_blocks[idx].size == tensor_blocks[found_idx].size);
		// On a tie, check which one has tighter life-cycle.
		if (tensor_blocks[idx].size >= size) // If this block size covers the size we request, we prefer longer life-cycle ones.
		{
			// Check whether the current tensor blocks life-cycle is longer than the previous one.
			if (tensor_blocks[idx].dup_p_refs && tensor_blocks[idx].dup_p_refs->rnum > 0 &&
				(!tensor_blocks[found_idx].dup_p_refs || !tensor_blocks[found_idx].dup_p_refs->rnum ||
				 _ccv_nnc_tensor_block_a_after_b_inclusively(exec_dep, tensor_blocks[idx].dup_p_refs, tensor_blocks[found_idx].dup_p_refs)))
				found_idx = idx;
			continue;
		}
		// Now both our size is smaller than requested size, in this case, we need to increase the tensor block size.
		// We prefer to choose the one that has life-cycle closer to the expected ones.
		if (no_dup_p_refs)
		{
			// Whoever is shorter wins.
			if (tensor_blocks[found_idx].dup_p_refs && tensor_blocks[found_idx].dup_p_refs->rnum > 0 &&
				(!tensor_blocks[idx].dup_p_refs || !tensor_blocks[idx].dup_p_refs->rnum ||
				 _ccv_nnc_tensor_block_a_after_b_inclusively(exec_dep, tensor_blocks[found_idx].dup_p_refs, tensor_blocks[idx].dup_p_refs)))
				found_idx = idx;
			continue;
		}
		if (!tensor_blocks[idx].dup_p_refs || !tensor_blocks[idx].dup_p_refs->rnum)
			continue;
		if (!tensor_blocks[found_idx].dup_p_refs || !tensor_blocks[found_idx].dup_p_refs->rnum)
		{
			found_idx = idx;
			continue;
		}
		// If both covers the request dup_p_refs, we prefer the shorter one, otherwise we prefer the longer one.
		const int idx_after_request = _ccv_nnc_tensor_block_a_after_b_inclusively(exec_dep, tensor_blocks[idx].dup_p_refs, dup_p_refs);
		const int found_idx_after_request = _ccv_nnc_tensor_block_a_after_b_inclusively(exec_dep, tensor_blocks[found_idx].dup_p_refs, dup_p_refs);
		if (idx_after_request && found_idx_after_request)
		{
			if (_ccv_nnc_tensor_block_a_after_b_inclusively(exec_dep, tensor_blocks[found_idx].dup_p_refs, tensor_blocks[idx].dup_p_refs))
				found_idx = idx;
			continue;
		} else {
			// We entered this branch must be either idx_after_request is false or found_idx_after_request is false or both.
			// If found_idx_after_request is not false, we are currently doing fine, no need to proceed.
			// Otherwise, if idx_after_request is true, it is preferred. If both are false, then prefer the longer one.
			if (!found_idx_after_request && (idx_after_request ||
				_ccv_nnc_tensor_block_a_after_b_inclusively(exec_dep, tensor_blocks[idx].dup_p_refs, tensor_blocks[found_idx].dup_p_refs)))
				found_idx = idx;
			continue;
		}
	}
	return found_idx;
}