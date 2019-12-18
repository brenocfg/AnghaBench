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
struct ftrace_event_call {int (* profile_enable ) (struct ftrace_event_call*) ;int /*<<< orphan*/  profile_count; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ alloc_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_trace_t ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct ftrace_event_call*) ; 
 int /*<<< orphan*/  total_profile_count ; 
 int /*<<< orphan*/ * trace_profile_buf ; 
 int /*<<< orphan*/ * trace_profile_buf_nmi ; 

__attribute__((used)) static int ftrace_profile_enable_event(struct ftrace_event_call *event)
{
	char *buf;
	int ret = -ENOMEM;

	if (atomic_inc_return(&event->profile_count))
		return 0;

	if (!total_profile_count) {
		buf = (char *)alloc_percpu(perf_trace_t);
		if (!buf)
			goto fail_buf;

		rcu_assign_pointer(trace_profile_buf, buf);

		buf = (char *)alloc_percpu(perf_trace_t);
		if (!buf)
			goto fail_buf_nmi;

		rcu_assign_pointer(trace_profile_buf_nmi, buf);
	}

	ret = event->profile_enable(event);
	if (!ret) {
		total_profile_count++;
		return 0;
	}

fail_buf_nmi:
	if (!total_profile_count) {
		free_percpu(trace_profile_buf_nmi);
		free_percpu(trace_profile_buf);
		trace_profile_buf_nmi = NULL;
		trace_profile_buf = NULL;
	}
fail_buf:
	atomic_dec(&event->profile_count);

	return ret;
}