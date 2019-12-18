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
struct pt_regs {int dummy; } ;
struct perf_sample_data {int dummy; } ;
struct perf_output_handle {int dummy; } ;
struct perf_event_header {int /*<<< orphan*/  size; } ;
struct perf_event {int dummy; } ;

/* Variables and functions */
 scalar_t__ perf_output_begin (struct perf_output_handle*,struct perf_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_output_end (struct perf_output_handle*) ; 
 int /*<<< orphan*/  perf_output_sample (struct perf_output_handle*,struct perf_event_header*,struct perf_sample_data*,struct perf_event*) ; 
 int /*<<< orphan*/  perf_prepare_sample (struct perf_event_header*,struct perf_sample_data*,struct perf_event*,struct pt_regs*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void perf_event_output(struct perf_event *event,
				struct perf_sample_data *data,
				struct pt_regs *regs)
{
	struct perf_output_handle handle;
	struct perf_event_header header;

	/* protect the callchain buffers */
	rcu_read_lock();

	perf_prepare_sample(&header, data, event, regs);

	if (perf_output_begin(&handle, event, header.size))
		goto exit;

	perf_output_sample(&handle, &header, data, event);

	perf_output_end(&handle);

exit:
	rcu_read_unlock();
}