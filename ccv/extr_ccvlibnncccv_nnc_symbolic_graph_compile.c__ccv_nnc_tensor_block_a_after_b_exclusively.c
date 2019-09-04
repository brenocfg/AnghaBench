#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_sparse_matrix_t ;
struct TYPE_8__ {scalar_t__* i32; } ;
typedef  TYPE_1__ ccv_numeric_data_t ;
struct TYPE_9__ {int rnum; } ;
typedef  TYPE_2__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__ const* const) ; 
 scalar_t__ ccv_array_get (TYPE_2__ const* const,int) ; 
 TYPE_1__ ccv_get_sparse_matrix_cell (int /*<<< orphan*/  const* const,int,int) ; 
 int ccv_max (scalar_t__,int) ; 

__attribute__((used)) static int _ccv_nnc_tensor_block_a_after_b_exclusively(const ccv_sparse_matrix_t* const exec_dep, const ccv_array_t* const a, const ccv_array_t* const b)
{
	assert(a);
	assert(b);
	int x, y, max_hop = 0;
	for (x = 0; x < a->rnum; x++)
		for (y = 0; y < b->rnum; y++)
		{
			ccv_numeric_data_t cell = ccv_get_sparse_matrix_cell(exec_dep, *(int*)ccv_array_get(a, x), *(int*)ccv_array_get(b, y));
			if (!cell.i32 || cell.i32[0] == 0)
				return 0;
			max_hop = ccv_max(cell.i32[0], max_hop);
		}
	// We've entered this nested-for loop, therefore, it must be verifiably, deterministically after b now.
	// The max hop also denotes if that is the case, how many hops, maximally speaking, we need to get from a to b.
	return max_hop;
}