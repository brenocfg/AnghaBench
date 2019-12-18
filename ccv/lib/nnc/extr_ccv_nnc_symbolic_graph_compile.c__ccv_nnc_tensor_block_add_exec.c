#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_sparse_matrix_t ;
struct TYPE_9__ {scalar_t__* i32; } ;
typedef  TYPE_1__ ccv_numeric_data_t ;
struct TYPE_10__ {TYPE_3__* tail; TYPE_3__* head; } ;
typedef  TYPE_2__ ccv_nnc_tensor_block_t ;
struct TYPE_11__ {int rnum; } ;
typedef  TYPE_3__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_3__*,int const*) ; 
 TYPE_1__ ccv_get_sparse_matrix_cell (int /*<<< orphan*/  const* const,int const,int const) ; 

__attribute__((used)) static void _ccv_nnc_tensor_block_add_exec(const ccv_sparse_matrix_t* const exec_dep, const int idx, ccv_nnc_tensor_block_t tensor_blocks)
{
	int i, found = 0;
	// Try to insert head.
	ccv_array_t* head = tensor_blocks.head;
	assert(head);
	for (i = 0; i < head->rnum;)
	{
		const int head_idx = *(int*)ccv_array_get(head, i);
		if (head_idx == idx)
		{
			found = 1;
			break;
		}
		ccv_numeric_data_t cell = ccv_get_sparse_matrix_cell(exec_dep, head_idx, idx);
		if (cell.i32 && cell.i32[0] > 0)
		{
			/* If the current node is the parent of the head node, check if we found it or not. */
			/* If not found, replace the current one. */
			if (!found)
			{
				found = 1;
				*(int*)ccv_array_get(head, i) = idx;
			} else {
				/* Remove the current one, change the rnum. */
				if (i < head->rnum - 1)
					*(int*)ccv_array_get(head, i) = *(int*)ccv_array_get(head, head->rnum - 1);
				--head->rnum;
				continue;
			}
		} else {
			// If the head is the parent of the idx, we cannot add it to the array (it is deterministically later than head).
			cell = ccv_get_sparse_matrix_cell(exec_dep, idx, head_idx);
			if (cell.i32 && cell.i32[0] > 0)
			{
				found = 1;
				break;
			}
		}
		/* Advancing i. */
		++i;
	}
	/* If not found, push this idx to the end of the array. */
	if (!found)
		ccv_array_push(head, &idx);
	// Try to insert tail.
	found = 0;
	ccv_array_t* tail = tensor_blocks.tail;
	assert(tail);
	for (i = 0; i < tail->rnum;)
	{
		const int tail_idx = *(int*)ccv_array_get(tail, i);
		if (tail_idx == idx)
		{
			found = 1;
			break;
		}
		ccv_numeric_data_t cell = ccv_get_sparse_matrix_cell(exec_dep, idx, tail_idx);
		if (cell.i32 && cell.i32[0] > 0)
		{
			/* If the current node is the child of the tail node, check if we found it or not. */
			/* If not found, replace the current one. */
			if (!found)
			{
				found = 1;
				*(int*)ccv_array_get(tail, i) = idx;
			} else {
				/* Remove the current one, change the rnum. */
				*(int*)ccv_array_get(tail, i) = *(int*)ccv_array_get(tail, tail->rnum - 1);
				--tail->rnum;
				continue;
			}
		} else {
			// If the tail is the child of the idx, we cannot add it to the array (it is deterministically earlier than tail).
			cell = ccv_get_sparse_matrix_cell(exec_dep, tail_idx, idx);
			if (cell.i32 && cell.i32[0] > 0)
			{
				found = 1;
				break;
			}
		}
		/* Advancing i. */
		++i;
	}
	/* If not found, push this idx to the end of the array. */
	if (!found)
		ccv_array_push(tail, &idx);
}