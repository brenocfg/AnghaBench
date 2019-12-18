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
struct perf_sample_data {int dummy; } ;
struct perf_output_handle {int dummy; } ;
struct TYPE_4__ {int size; } ;
struct TYPE_3__ {TYPE_2__ header; int /*<<< orphan*/  tid; int /*<<< orphan*/  pid; } ;
struct perf_mmap_event {TYPE_1__ event_id; int /*<<< orphan*/  file_size; int /*<<< orphan*/  file_name; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __output_copy (struct perf_output_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  perf_event__output_id_sample (struct perf_event*,struct perf_output_handle*,struct perf_sample_data*) ; 
 int /*<<< orphan*/  perf_event_header__init_id (TYPE_2__*,struct perf_sample_data*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_event_pid (struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_event_tid (struct perf_event*,int /*<<< orphan*/ ) ; 
 int perf_output_begin (struct perf_output_handle*,struct perf_event*,int) ; 
 int /*<<< orphan*/  perf_output_end (struct perf_output_handle*) ; 
 int /*<<< orphan*/  perf_output_put (struct perf_output_handle*,TYPE_1__) ; 

__attribute__((used)) static void perf_event_mmap_output(struct perf_event *event,
				     struct perf_mmap_event *mmap_event)
{
	struct perf_output_handle handle;
	struct perf_sample_data sample;
	int size = mmap_event->event_id.header.size;
	int ret;

	perf_event_header__init_id(&mmap_event->event_id.header, &sample, event);
	ret = perf_output_begin(&handle, event,
				mmap_event->event_id.header.size);
	if (ret)
		goto out;

	mmap_event->event_id.pid = perf_event_pid(event, current);
	mmap_event->event_id.tid = perf_event_tid(event, current);

	perf_output_put(&handle, mmap_event->event_id);
	__output_copy(&handle, mmap_event->file_name,
				   mmap_event->file_size);

	perf_event__output_id_sample(event, &handle, &sample);

	perf_output_end(&handle);
out:
	mmap_event->event_id.header.size = size;
}