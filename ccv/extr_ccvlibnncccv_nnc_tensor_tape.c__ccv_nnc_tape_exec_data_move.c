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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int ccv_max (int const,int const) ; 

__attribute__((used)) static void _ccv_nnc_tape_exec_data_move(uint64_t* const old_data, uint64_t* const new_data, const int offset, const uint64_t* const while_counts, const int graph_size, const int* const dim, const int dim_count)
{
	int i;
	if (offset == ccv_max(dim_count, graph_size) - 1)
	{
		const int data_dim = offset < dim_count ? dim[offset] - 1 : 0;
		const int graph_dim = offset < graph_size ? while_counts[offset] : 0;
		assert(old_data <= new_data);
		// Do the actual copy or set.
		if (!old_data)
			for (i = ccv_max(data_dim, graph_dim); i >= 0; i--)
				new_data[i] = 0;
		else {
			for (i = graph_dim; i > data_dim; i--)
				new_data[i] = 0;
			for (i = data_dim; i >= 0; i--)
				new_data[i] = old_data[i];
		}
	} else {
		int old_data_step = 1;
		for (i = offset + 1; i < dim_count; i++)
			old_data_step *= dim[i];
		const int new_dim_count = ccv_max(graph_size, dim_count);
		int new_data_step = 1;
		for (i = offset + 1; i < new_dim_count; i++)
		{
			int old_dim = (i < dim_count) ? dim[i] : 1;
			int graph_dim = (i < graph_size) ? (int)(while_counts[i] + 1) : 1;
			new_data_step *= ccv_max(old_dim, graph_dim);
		}
		const int data_dim = offset < dim_count ? dim[offset] - 1 : 0;
		const int graph_dim = offset < graph_size ? while_counts[offset] : 0;
		for (i = ccv_max(data_dim, graph_dim); i >= 0; i--)
			_ccv_nnc_tape_exec_data_move((old_data && offset < dim_count && i < dim[offset]) ? old_data + i * old_data_step : 0, new_data + i * new_data_step, offset + 1, while_counts, graph_size, dim, dim_count);
	}
}