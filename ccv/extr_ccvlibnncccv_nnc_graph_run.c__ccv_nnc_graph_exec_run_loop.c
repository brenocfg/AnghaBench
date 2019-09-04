#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_20__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_tape_t ;
struct TYPE_23__ {int /*<<< orphan*/  done; int /*<<< orphan*/  super; } ;
typedef  TYPE_2__ ccv_nnc_stream_task_t ;
struct TYPE_24__ {TYPE_2__** block_stream_tasks; TYPE_1__* sub_graphs; } ;
typedef  TYPE_3__ ccv_nnc_graph_t ;
struct TYPE_22__ {int stream_size; } ;
struct TYPE_25__ {TYPE_20__ schedule; } ;
typedef  TYPE_4__ ccv_nnc_graph_exec_info_t ;
struct TYPE_21__ {int rnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_SWAP (int,int,int) ; 
 size_t* SCHEDULE_STREAMS (TYPE_20__) ; 
 TYPE_2__* _ccv_nnc_graph_exec_run_task (TYPE_3__* const,TYPE_4__* const,int const,int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_mark_outgoing_streams_blocked_by_task (TYPE_3__* const,TYPE_4__* const,TYPE_4__* const,TYPE_2__* const) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_wait_any_sub_tasks (TYPE_2__* const,TYPE_3__* const,TYPE_2__** const,int,TYPE_4__* const,int*,int) ; 
 scalar_t__ ccv_nnc_graph_buffer (TYPE_3__* const,int) ; 

__attribute__((used)) static void _ccv_nnc_graph_exec_run_loop(ccv_nnc_stream_task_t* const self, ccv_nnc_graph_t* const graph, ccv_nnc_graph_exec_info_t* const exec_info, const int start_index, const int exec_info_size, ccv_nnc_tensor_tape_t* const tensor_tape, const int flags)
{
	int i, j;
	int sub_task_size = 0;
	ccv_nnc_stream_task_t** const sub_tasks = (ccv_nnc_stream_task_t**)ccv_nnc_graph_buffer(graph, sizeof(ccv_nnc_stream_task_t*) * (graph->sub_graphs ? graph->sub_graphs->rnum : 0) + sizeof(int) * exec_info_size * 2);
	int* pending_nodes[2];
	pending_nodes[0] = (int*)(sub_tasks + (graph->sub_graphs ? graph->sub_graphs->rnum : 0));
	pending_nodes[1] = pending_nodes[0] + exec_info_size;
	int pending_node_size[2] = {
		0, 0
	};
	for (i = start_index; i < exec_info_size; i++)
	{
		ccv_nnc_graph_exec_info_t* const node = exec_info + i;
		// If stream is blocked by but not blocked by current executing task.
		int blocked = 0;
		for (j = 0; j < node->schedule.stream_size; j++)
			if (graph->block_stream_tasks[SCHEDULE_STREAMS(node->schedule)[j]])
			{
				pending_nodes[0][pending_node_size[0]++] = i;
				_ccv_nnc_graph_mark_outgoing_streams_blocked_by_task(graph, exec_info, node, graph->block_stream_tasks[SCHEDULE_STREAMS(node->schedule)[j]]);
				blocked = 1;
			}
		if (blocked)
			continue;
		ccv_nnc_stream_task_t* const task = _ccv_nnc_graph_exec_run_task(graph, node, i, tensor_tape, self->super, flags);
		if (task && !task->done)
		{
			sub_tasks[sub_task_size++] = task;
			for (j = 0; j < node->schedule.stream_size; j++)
				graph->block_stream_tasks[SCHEDULE_STREAMS(node->schedule)[j]] = task;
			_ccv_nnc_graph_mark_outgoing_streams_blocked_by_task(graph, exec_info, node, task);
		}
	}
	_ccv_nnc_graph_wait_any_sub_tasks(self, graph, sub_tasks, sub_task_size, exec_info, pending_nodes[0], pending_node_size[0]);
	int p = 0, q = 1;
	while (pending_node_size[p] > 0)
	{
		pending_node_size[q] = 0;
		sub_task_size = 0;
		for (i = 0; i < pending_node_size[p]; i++)
		{
			const int idx = pending_nodes[p][i];
			ccv_nnc_graph_exec_info_t* const node = exec_info + idx;
			int blocked = 0;
			for (j = 0; j < node->schedule.stream_size; j++)
				if (graph->block_stream_tasks[SCHEDULE_STREAMS(node->schedule)[j]])
				{
					_ccv_nnc_graph_mark_outgoing_streams_blocked_by_task(graph, exec_info, node, graph->block_stream_tasks[SCHEDULE_STREAMS(node->schedule)[j]]);
					pending_nodes[q][pending_node_size[q]++] = idx;
					blocked = 1;
				}
			if (blocked)
				continue;
			ccv_nnc_stream_task_t* const task = _ccv_nnc_graph_exec_run_task(graph, node, idx, tensor_tape, self->super, flags);
			if (task && !task->done)
			{
				sub_tasks[sub_task_size++] = task;
				for (j = 0; j < node->schedule.stream_size; j++)
					graph->block_stream_tasks[SCHEDULE_STREAMS(node->schedule)[j]] = task;
				_ccv_nnc_graph_mark_outgoing_streams_blocked_by_task(graph, exec_info, node, task);
			}
		}
		int t;
		CCV_SWAP(p, q, t);
		_ccv_nnc_graph_wait_any_sub_tasks(self, graph, sub_tasks, sub_task_size, exec_info, pending_nodes[p], pending_node_size[p]);
	}
}