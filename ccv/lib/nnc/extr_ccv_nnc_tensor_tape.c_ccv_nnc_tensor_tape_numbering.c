#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_11__ {int /*<<< orphan*/  exec_data; } ;
typedef  TYPE_1__ ccv_nnc_tensor_tape_t ;
struct TYPE_12__ {int const dim_count; int* dim; int* data; } ;
typedef  TYPE_2__ ccv_nnc_tape_exec_data_array_t ;
struct TYPE_13__ {int while_count; struct TYPE_13__* p; int /*<<< orphan*/  exec_info; } ;
typedef  TYPE_3__ ccv_nnc_graph_t ;
struct TYPE_14__ {scalar_t__ d; TYPE_3__ const* const graph; } ;
typedef  TYPE_4__ ccv_nnc_graph_exec_t ;
struct TYPE_15__ {scalar_t__ alias_ref; scalar_t__ pair_ref; } ;
typedef  TYPE_5__ ccv_nnc_graph_exec_info_t ;

/* Variables and functions */
 TYPE_2__* _ccv_nnc_tape_exec_data_array_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__* ccv_array_get (int /*<<< orphan*/ ,scalar_t__) ; 

uint64_t ccv_nnc_tensor_tape_numbering(ccv_nnc_tensor_tape_t* const tape, const ccv_nnc_graph_t* const graph, const ccv_nnc_graph_exec_t exec)
{
	assert(exec.graph == graph);
	ccv_nnc_graph_exec_info_t* exec_info = ccv_array_get(graph->exec_info, exec.d);
	if (!exec_info->alias_ref && exec_info->pair_ref)
		exec_info = ccv_array_get(graph->exec_info, exec_info->pair_ref - 1);
	ccv_nnc_tape_exec_data_array_t* const data_array = _ccv_nnc_tape_exec_data_array_get(tape->exec_data, (int)exec_info->alias_ref);
	const ccv_nnc_graph_t* curr_graph = graph;
	int i;
	for (i = 0; curr_graph; i++)
		curr_graph = curr_graph->p;
	curr_graph = graph;
	const int graph_size = i;
	uint64_t while_counts[graph_size];
	for (i = graph_size - 1; curr_graph; i--, curr_graph = curr_graph->p)
		while_counts[i] = curr_graph->while_count;
	assert(graph_size <= data_array->dim_count);
	int idx = 0, step = 1;
	for (i = graph_size - 1; i >= 0; i--)
	{
		assert(while_counts[i] < data_array->dim[i]);
		idx += while_counts[i] * step;
		step *= data_array->dim[i];
	}
	return data_array->data[idx];
}