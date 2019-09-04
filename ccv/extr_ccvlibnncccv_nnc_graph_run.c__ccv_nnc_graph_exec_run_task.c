#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_22__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_tape_t ;
struct TYPE_26__ {int /*<<< orphan*/  u8; } ;
struct TYPE_28__ {TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_task_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_scheduler_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;
struct TYPE_29__ {int const exec_idx; int const flags; int /*<<< orphan*/ * const stream_context; int /*<<< orphan*/ * const tensor_tape; TYPE_6__* const exec; TYPE_4__* graph; TYPE_2__** inputs; } ;
typedef  TYPE_3__ ccv_nnc_graph_topsorted_run_coro_t ;
struct TYPE_30__ {int /*<<< orphan*/ * signals; int /*<<< orphan*/ ** streams; int /*<<< orphan*/  sub_graphs; } ;
typedef  TYPE_4__ ccv_nnc_graph_t ;
struct TYPE_31__ {int /*<<< orphan*/ * const stream; TYPE_6__* const node; TYPE_4__* const graph; } ;
typedef  TYPE_5__ ccv_nnc_graph_neighbor_context_discovery_t ;
struct TYPE_27__ {int stream_size; int wait_size; size_t* waits; } ;
struct TYPE_25__ {scalar_t__ cmd; } ;
struct TYPE_32__ {int input_size; int output_size; int flags; TYPE_22__ schedule; int /*<<< orphan*/  hint; TYPE_13__ cmd; int /*<<< orphan*/  output_flags; int /*<<< orphan*/  input_flags; TYPE_2__** inputs; } ;
typedef  TYPE_6__ ccv_nnc_graph_exec_info_t ;
typedef  TYPE_3__ ccv_nnc_graph_exec_cases_of_coro_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_CLI_VERBOSE ; 
 scalar_t__ CCV_NNC_GRAPH_BACKWARD ; 
 int CCV_NNC_GRAPH_EXEC_CASE_OF ; 
 int CCV_NNC_GRAPH_EXEC_P_WHILE ; 
 scalar_t__ CCV_NNC_GRAPH_FORWARD ; 
 scalar_t__* CCV_NNC_GRAPH_REF (TYPE_6__* const) ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,int,...) ; 
 size_t* SCHEDULE_SIGNALS (TYPE_22__) ; 
 size_t* SCHEDULE_STREAMS (TYPE_22__) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_exec_begin_synchronize_multiviews (TYPE_4__* const,TYPE_6__* const) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_exec_cases_of_coro ; 
 int /*<<< orphan*/  _ccv_nnc_graph_exec_unwrap_io (TYPE_4__* const,TYPE_6__* const) ; 
 int /*<<< orphan*/  _ccv_nnc_graph_neighbor_context_discovery ; 
 int /*<<< orphan*/  _ccv_nnc_graph_topsorted_run_coro ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ccv_nnc_cmd_exec (TYPE_13__,int /*<<< orphan*/ ,int const,TYPE_2__**,int,TYPE_2__**,int,int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ccv_nnc_cmd_name (scalar_t__) ; 
 int /*<<< orphan*/  ccv_nnc_stream_context_emit_signal (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_stream_context_set_neighbor_discovery (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ccv_nnc_stream_context_wait_signal (int /*<<< orphan*/ * const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ccv_nnc_stream_task_new (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_stream_task_resume (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_tape_io (int /*<<< orphan*/ * const,TYPE_4__* const,int /*<<< orphan*/ ,TYPE_2__**,int,int /*<<< orphan*/ ,TYPE_2__**,int) ; 

__attribute__((used)) static inline ccv_nnc_stream_task_t* _ccv_nnc_graph_exec_run_task(ccv_nnc_graph_t* const graph, ccv_nnc_graph_exec_info_t* const node, const int idx, ccv_nnc_tensor_tape_t* const tensor_tape, ccv_nnc_stream_scheduler_t* const scheduler, const int flags)
{
	_ccv_nnc_graph_exec_unwrap_io(graph, node);
	ccv_nnc_tensor_t** inputs = node->inputs;
	ccv_nnc_tensor_t** outputs = inputs + node->input_size;
	if (tensor_tape)
		ccv_nnc_tensor_tape_io(tensor_tape, graph, node->input_flags, inputs, node->input_size, node->output_flags, outputs, node->output_size);
	/* Broadcast the updates to all subscribed references for input / output, even though at th
	 * time output is not written yet, propagate pointer change is still valid. */
	_ccv_nnc_graph_exec_begin_synchronize_multiviews(graph, node);
	if (node->cmd.cmd == CCV_NNC_GRAPH_FORWARD || node->cmd.cmd == CCV_NNC_GRAPH_BACKWARD)
	{
		if (node->flags & CCV_NNC_GRAPH_EXEC_CASE_OF)
		{
			ccv_nnc_stream_context_t* const node_stream = graph->streams[SCHEDULE_STREAMS(node->schedule)[0]];
			ccv_nnc_graph_exec_cases_of_coro_t params = {
				.graph = graph,
				.exec_idx = idx,
				.exec = node,
				.inputs = inputs,
				.tensor_tape = tensor_tape,
				.stream_context = node_stream,
				.flags = flags,
			};
			ccv_nnc_stream_task_t* const task = ccv_nnc_stream_task_new(scheduler, _ccv_nnc_graph_exec_cases_of_coro, &params, 0);
			ccv_nnc_stream_task_resume(task);
			return task;
		} else if (node->flags & CCV_NNC_GRAPH_EXEC_P_WHILE) {
			ccv_nnc_graph_t* sub_graph = *(ccv_nnc_graph_t**)ccv_array_get(graph->sub_graphs, CCV_NNC_GRAPH_REF(node)[0] - 1);
			assert(graph->streams[SCHEDULE_STREAMS(node->schedule)[0]] == sub_graph->streams[0]);
			ccv_nnc_graph_topsorted_run_coro_t params = {
				.graph = sub_graph,
				.exec_idx = idx,
				.exec = node,
				.tensor_tape = tensor_tape,
				.stream_context = graph->streams[SCHEDULE_STREAMS(node->schedule)[0]],
				.flags = flags
			};
			ccv_nnc_stream_task_t* const task = ccv_nnc_stream_task_new(scheduler, _ccv_nnc_graph_topsorted_run_coro, &params, 0);
			ccv_nnc_stream_task_resume(task);
			return task;
		}
	} else {
		int i, j;
		for (i = 0; i < node->schedule.stream_size; i++)
		{
			ccv_nnc_stream_context_t* const stream = graph->streams[SCHEDULE_STREAMS(node->schedule)[i]];
			for (j = 0; j < node->schedule.wait_size; j++)
				ccv_nnc_stream_context_wait_signal(stream, graph->signals[node->schedule.waits[j]]);
		}
		PRINT(CCV_CLI_VERBOSE, "%s [%d]: [%d] -> [%d]\n", ccv_nnc_cmd_name(node->cmd.cmd), idx, node->input_size, node->output_size);
		for (i = 0; i < node->input_size; i++)
			PRINT(CCV_CLI_VERBOSE, "|-> %d. %p (%p)\n", i + 1, inputs[i], (inputs[i] ? inputs[i]->data.u8 : 0));
		ccv_nnc_stream_context_t* const node_stream = graph->streams[SCHEDULE_STREAMS(node->schedule)[0]];
		ccv_nnc_graph_neighbor_context_discovery_t discovery_context = {
			.graph = graph,
			.node = node,
			.stream = node_stream
		};
		ccv_nnc_stream_context_set_neighbor_discovery(node_stream, _ccv_nnc_graph_neighbor_context_discovery, &discovery_context);
		ccv_nnc_cmd_exec(node->cmd, node->hint, flags, inputs, node->input_size, outputs, node->output_size, node_stream);
		for (i = 0; i < node->output_size; i++)
			PRINT(CCV_CLI_VERBOSE, "|<- %d. %p (%p)\n", i + 1, outputs[i], (outputs[i] ? outputs[i]->data.u8 : 0));
		for (i = 0; i < node->schedule.stream_size; i++)
			if (SCHEDULE_SIGNALS(node->schedule)[i] >= 0)
			{
				ccv_nnc_stream_context_t* const stream = graph->streams[SCHEDULE_STREAMS(node->schedule)[i]];
				ccv_nnc_stream_context_emit_signal(stream, graph->signals[SCHEDULE_SIGNALS(node->schedule)[i]]);
			}
	}
	return 0;
}