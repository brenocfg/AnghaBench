#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_4__ {int size; } ;
struct TYPE_3__ {TYPE_2__ header; void* ptid; void* tid; void* ppid; void* pid; } ;
struct perf_task_event {TYPE_1__ event_id; struct task_struct* task; } ;
struct perf_sample_data {int dummy; } ;
struct perf_output_handle {int dummy; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 struct task_struct* current ; 
 int /*<<< orphan*/  perf_event__output_id_sample (struct perf_event*,struct perf_output_handle*,struct perf_sample_data*) ; 
 int /*<<< orphan*/  perf_event_header__init_id (TYPE_2__*,struct perf_sample_data*,struct perf_event*) ; 
 void* perf_event_pid (struct perf_event*,struct task_struct*) ; 
 void* perf_event_tid (struct perf_event*,struct task_struct*) ; 
 int perf_output_begin (struct perf_output_handle*,struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_output_end (struct perf_output_handle*) ; 
 int /*<<< orphan*/  perf_output_put (struct perf_output_handle*,TYPE_1__) ; 

__attribute__((used)) static void perf_event_task_output(struct perf_event *event,
				     struct perf_task_event *task_event)
{
	struct perf_output_handle handle;
	struct perf_sample_data	sample;
	struct task_struct *task = task_event->task;
	int ret, size = task_event->event_id.header.size;

	perf_event_header__init_id(&task_event->event_id.header, &sample, event);

	ret = perf_output_begin(&handle, event,
				task_event->event_id.header.size);
	if (ret)
		goto out;

	task_event->event_id.pid = perf_event_pid(event, task);
	task_event->event_id.ppid = perf_event_pid(event, current);

	task_event->event_id.tid = perf_event_tid(event, task);
	task_event->event_id.ptid = perf_event_tid(event, current);

	perf_output_put(&handle, task_event->event_id);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
out:
	task_event->event_id.header.size = size;
}