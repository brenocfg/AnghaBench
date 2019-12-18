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
struct ftrace_event_call {int /*<<< orphan*/  (* profile_disable ) (struct ftrace_event_call*) ;int /*<<< orphan*/  profile_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_add_negative (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_percpu (char*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ftrace_event_call*) ; 
 int /*<<< orphan*/  synchronize_sched () ; 
 int /*<<< orphan*/  total_profile_count ; 
 char* trace_profile_buf ; 
 char* trace_profile_buf_nmi ; 

__attribute__((used)) static void ftrace_profile_disable_event(struct ftrace_event_call *event)
{
	char *buf, *nmi_buf;

	if (!atomic_add_negative(-1, &event->profile_count))
		return;

	event->profile_disable(event);

	if (!--total_profile_count) {
		buf = trace_profile_buf;
		rcu_assign_pointer(trace_profile_buf, NULL);

		nmi_buf = trace_profile_buf_nmi;
		rcu_assign_pointer(trace_profile_buf_nmi, NULL);

		/*
		 * Ensure every events in profiling have finished before
		 * releasing the buffers
		 */
		synchronize_sched();

		free_percpu(buf);
		free_percpu(nmi_buf);
	}
}