#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ccv_iter_accessed ; 

__attribute__((used)) static void _ccv_iter_int(const int column_idx, const int* row_idxs, const int row_size, void** const data, void* const context, ccv_nnc_stream_context_t* const stream_context)
{
	int* const array = (int*)context;
	int i;
	for (i = 0; i < row_size; i++)
		data[i] = (void*)(intptr_t)array[row_idxs[i]];
	++_ccv_iter_accessed;
}