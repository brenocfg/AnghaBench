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
typedef  int u64 ;
struct perf_sample_data {int type; int /*<<< orphan*/  cpu_entry; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  id; int /*<<< orphan*/  time; int /*<<< orphan*/  tid_entry; } ;
struct perf_output_handle {int dummy; } ;

/* Variables and functions */
 int PERF_SAMPLE_CPU ; 
 int PERF_SAMPLE_ID ; 
 int PERF_SAMPLE_STREAM_ID ; 
 int PERF_SAMPLE_TID ; 
 int PERF_SAMPLE_TIME ; 
 int /*<<< orphan*/  perf_output_put (struct perf_output_handle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __perf_event__output_id_sample(struct perf_output_handle *handle,
					   struct perf_sample_data *data)
{
	u64 sample_type = data->type;

	if (sample_type & PERF_SAMPLE_TID)
		perf_output_put(handle, data->tid_entry);

	if (sample_type & PERF_SAMPLE_TIME)
		perf_output_put(handle, data->time);

	if (sample_type & PERF_SAMPLE_ID)
		perf_output_put(handle, data->id);

	if (sample_type & PERF_SAMPLE_STREAM_ID)
		perf_output_put(handle, data->stream_id);

	if (sample_type & PERF_SAMPLE_CPU)
		perf_output_put(handle, data->cpu_entry);
}