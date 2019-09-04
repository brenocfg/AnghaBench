#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ topsorted; TYPE_7__* exec_info; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;
struct TYPE_10__ {scalar_t__ d; TYPE_1__* const graph; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_t ;
struct TYPE_11__ {TYPE_7__* outgoings; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_info_t ;
struct TYPE_12__ {scalar_t__ rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_array_add_unique_int (TYPE_7__*,int) ; 
 scalar_t__ ccv_array_get (TYPE_7__*,int) ; 

int ccv_nnc_graph_exec_disjoin(ccv_nnc_graph_t* const graph, const ccv_nnc_graph_exec_t source, const ccv_nnc_graph_exec_t destination)
{
	assert(graph == source.graph);
	assert(graph == destination.graph);
	assert(source.d < graph->exec_info->rnum);
	assert(destination.d < graph->exec_info->rnum);
	ccv_nnc_graph_exec_info_t* src_info = (ccv_nnc_graph_exec_info_t*)ccv_array_get(graph->exec_info, source.d);
	if (!src_info->outgoings)
		return -1;
	int i, j = -1;
	// Check if this is already connected, if so, skip.
	for (i = 0; i < src_info->outgoings->rnum; i++)
		if (*(int*)ccv_array_get(src_info->outgoings, i) == destination.d)
		{
			j = i;
			break;
		}
	if (j < 0)
		return -1;
	if (j < src_info->outgoings->rnum - 1)
		*(int*)ccv_array_get(src_info->outgoings, j) = *(int*)ccv_array_get(src_info->outgoings, src_info->outgoings->rnum - 1);
	--src_info->outgoings->rnum;
	ccv_nnc_graph_exec_info_t* dest_info = (ccv_nnc_graph_exec_info_t*)ccv_array_get(graph->exec_info, destination.d);
	if (dest_info->outgoings)
		for (i = 0; i < dest_info->outgoings->rnum; i++)
			ccv_array_add_unique_int(src_info->outgoings, *(int*)ccv_array_get(dest_info->outgoings, i));
	graph->topsorted = 0;
	return 0;
}