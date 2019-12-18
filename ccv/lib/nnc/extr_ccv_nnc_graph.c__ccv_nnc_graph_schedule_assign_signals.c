#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ signal_set; } ;
typedef  TYPE_1__ ccv_nnc_stream_data_t ;
struct TYPE_14__ {scalar_t__ stream_size; int wait_size; int /*<<< orphan*/  waits; } ;
struct TYPE_12__ {TYPE_9__ schedule; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_info_t ;
struct TYPE_13__ {int rnum; } ;
typedef  TYPE_3__ ccv_array_t ;

/* Variables and functions */
 int* SCHEDULE_SIGNALS (TYPE_9__) ; 
 int const* SCHEDULE_STREAMS (TYPE_9__) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccmalloc (int) ; 
 int /*<<< orphan*/  ccrealloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ccv_array_find_int (scalar_t__,int) ; 
 scalar_t__ ccv_array_get (TYPE_3__* const,int const) ; 
 scalar_t__ ccv_array_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (scalar_t__,int*) ; 
 int ccv_max (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void _ccv_nnc_graph_schedule_assign_signals(ccv_array_t* const incoming, ccv_nnc_graph_exec_info_t* const node, ccv_array_t* const stream_data, int* const signal_size, ccv_nnc_graph_exec_info_t* const exec_info, const int exec_info_size)
{
	assert(incoming->rnum > 0);
	int i, j, k;
	int wait_size = 0, max_wait_size = 0;
	for (i = 0; i < incoming->rnum; i++)
	{
		const int incoming_idx = *(int*)ccv_array_get(incoming, i);
		ccv_nnc_graph_exec_info_t* const incoming_exec_info = exec_info + incoming_idx;
		assert(incoming_exec_info->schedule.stream_size > 0);
		max_wait_size += incoming_exec_info->schedule.stream_size;
	}
	int waits[ccv_max(1, max_wait_size)];
	assert(node->schedule.stream_size > 0);
	for (i = 0; i < incoming->rnum; i++)
	{
		const int incoming_idx = *(int*)ccv_array_get(incoming, i);
		assert(incoming_idx < exec_info_size);
		assert(incoming_idx >= 0);
		ccv_nnc_graph_exec_info_t* const incoming_exec_info = exec_info + incoming_idx;
		assert(incoming_exec_info->schedule.stream_size > 0);
		int stream_synced = 1;
		// If the current node's stream is a subset of the incoming node's stream, there
		// is no need to sync with signal, because we are already synced with the incoming.
		for (j = 0; stream_synced && j < node->schedule.stream_size; j++)
		{
			const int s = SCHEDULE_STREAMS(node->schedule)[j];
			assert(s >= 0);
			int flag = 0;
			for (k = 0; !flag && k < incoming_exec_info->schedule.stream_size; k++)
				flag = (SCHEDULE_STREAMS(incoming_exec_info->schedule)[k] == s);
			stream_synced = flag;
		}
		if (stream_synced)
			continue;
		// Otherwise, find the streams we need to sync with, and create signals for these.
		for (j = 0; j < incoming_exec_info->schedule.stream_size; j++)
		{
			const int s = SCHEDULE_STREAMS(incoming_exec_info->schedule)[j];
			assert(s >= 0);
			int flag = 0;
			for (k = 0; !flag && k < node->schedule.stream_size; k++)
				flag = (SCHEDULE_STREAMS(node->schedule)[k] == s);
			if (!flag) // Need to have a signal.
			{
				if (SCHEDULE_SIGNALS(incoming_exec_info->schedule)[j] < 0)
					SCHEDULE_SIGNALS(incoming_exec_info->schedule)[j] = (*signal_size)++;
				else {
					int flag = 0;
					// If any of the stream the current node has already seen this signal, we are good already.
					for (k = 0; !flag && k < node->schedule.stream_size; k++)
					{
						assert(SCHEDULE_STREAMS(node->schedule)[k] >= 0);
						ccv_nnc_stream_data_t* const data = (ccv_nnc_stream_data_t*)ccv_array_get(stream_data, SCHEDULE_STREAMS(node->schedule)[k]);
						flag = (data->signal_set && ccv_array_find_int(data->signal_set, SCHEDULE_SIGNALS(incoming_exec_info->schedule)[j]));
					}
					if (flag)
						continue;
				}
				// Otherwise, we need to wait for this. Currently, our granularity is about wait on all streams.
				waits[wait_size++] = SCHEDULE_SIGNALS(incoming_exec_info->schedule)[j];
				// All streams on this node have seen this signal.
				for (k = 0; k < node->schedule.stream_size; k++)
				{
					ccv_nnc_stream_data_t* const data = (ccv_nnc_stream_data_t*)ccv_array_get(stream_data, SCHEDULE_STREAMS(node->schedule)[k]);
					if (!data->signal_set)
						data->signal_set = ccv_array_new(sizeof(int), 0, 0);
					ccv_array_push(data->signal_set, &SCHEDULE_SIGNALS(incoming_exec_info->schedule)[j]);
				}
			}
		}
	}
	node->schedule.wait_size = wait_size;
	if (wait_size > 0)
	{
		node->schedule.waits = node->schedule.waits ? ccrealloc(node->schedule.waits, sizeof(int) * wait_size) : ccmalloc(sizeof(int) * wait_size);
		memcpy(node->schedule.waits, waits, sizeof(int) * wait_size);
	}
}