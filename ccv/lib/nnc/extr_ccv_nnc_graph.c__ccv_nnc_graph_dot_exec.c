#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_nnc_stream_context_t ;
struct TYPE_11__ {scalar_t__ stream_size; int wait_size; int* waits; } ;
struct TYPE_8__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_10__ {TYPE_6__ schedule; TYPE_1__ cmd; } ;
typedef  TYPE_3__ ccv_nnc_graph_exec_info_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int const CCV_NNC_LONG_DOT_GRAPH ; 
 int CCV_TENSOR_GET_DEVICE_ID (int /*<<< orphan*/ ) ; 
 int* SCHEDULE_SIGNALS (TYPE_6__) ; 
 int* SCHEDULE_STREAMS (TYPE_6__) ; 
 char* ccv_nnc_cmd_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int const,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_nnc_graph_dot_exec(const int index, const ccv_nnc_graph_exec_info_t* const exec_info, ccv_nnc_stream_context_t** const streams, const int flags, FILE* out)
{
	if (flags == CCV_NNC_LONG_DOT_GRAPH)
		fputc('{', out);
	fprintf(out, "node%d", index);
	if (flags == CCV_NNC_LONG_DOT_GRAPH)
	{
		fputs("|Command: ", out);
		fputs(ccv_nnc_cmd_name(exec_info->cmd.cmd), out);
		if (exec_info->schedule.stream_size > 0)
		{
			int i, flag = 0;
			fputs("|Stream: ", out);
			for (i = 0; i < exec_info->schedule.stream_size; i++)
			{
				const int device_id = streams ? CCV_TENSOR_GET_DEVICE_ID(streams[SCHEDULE_STREAMS(exec_info->schedule)[i]]->type) : 0;
				if (i == 0)
					fprintf(out, "%d (d%d)", SCHEDULE_STREAMS(exec_info->schedule)[i], device_id);
				else
					fprintf(out, ", %d (d%d)", SCHEDULE_STREAMS(exec_info->schedule)[i], device_id);
			}
			for (i = 0; i < exec_info->schedule.stream_size; i++)
				if (SCHEDULE_SIGNALS(exec_info->schedule)[i] >= 0)
				{
					if (!flag)
					{
						flag = 1;
						fprintf(out, "|Signal: %d", SCHEDULE_SIGNALS(exec_info->schedule)[i]);
					} else
						fprintf(out, ", %d", SCHEDULE_SIGNALS(exec_info->schedule)[i]);
				}
		}
		if (exec_info->schedule.wait_size > 0)
		{
			fputs("|Wait: ", out);
			int i;
			for (i = 0; i < exec_info->schedule.wait_size - 1; i++)
				fprintf(out, "%d, ", exec_info->schedule.waits[i]);
			fprintf(out, "%d", exec_info->schedule.waits[exec_info->schedule.wait_size - 1]);
		}
		fputc('}', out);
	}
}