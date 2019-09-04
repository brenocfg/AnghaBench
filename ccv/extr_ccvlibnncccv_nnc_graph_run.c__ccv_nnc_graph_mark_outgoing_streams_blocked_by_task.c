#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_stream_task_t ;
struct TYPE_8__ {int /*<<< orphan*/ ** block_stream_tasks; } ;
typedef  TYPE_1__ ccv_nnc_graph_t ;
struct TYPE_11__ {int stream_size; } ;
struct TYPE_9__ {TYPE_7__ schedule; TYPE_3__* outgoings; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_info_t ;
struct TYPE_10__ {int rnum; } ;

/* Variables and functions */
 size_t* SCHEDULE_STREAMS (TYPE_7__) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int) ; 

__attribute__((used)) static void _ccv_nnc_graph_mark_outgoing_streams_blocked_by_task(ccv_nnc_graph_t* const graph, ccv_nnc_graph_exec_info_t* const exec_info, ccv_nnc_graph_exec_info_t* const node, ccv_nnc_stream_task_t* const task)
{
	int i, j;
	if (node->outgoings)
		for (i = 0; i < node->outgoings->rnum; i++)
		{
			const int outgoing_idx = *(int*)ccv_array_get(node->outgoings, i);
			ccv_nnc_graph_exec_info_t* const outgoing_node = exec_info + outgoing_idx;
			// An outgoing stream can be blocked by multiple other tasks from other streams. But it is OK,
			// because on next round of execution, that one will be marked as blocked again.
			for (j = 0; j < outgoing_node->schedule.stream_size; j++)
				graph->block_stream_tasks[SCHEDULE_STREAMS(outgoing_node->schedule)[j]] = task;
		}
}