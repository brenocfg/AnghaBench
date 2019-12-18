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

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  probe_sched_switch ; 
 int /*<<< orphan*/  probe_sched_wakeup ; 
 int register_trace_sched_switch (int /*<<< orphan*/ ) ; 
 int register_trace_sched_wakeup (int /*<<< orphan*/ ) ; 
 int register_trace_sched_wakeup_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_trace_sched_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_trace_sched_wakeup_new (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tracing_sched_register(void)
{
	int ret;

	ret = register_trace_sched_wakeup(probe_sched_wakeup);
	if (ret) {
		pr_info("wakeup trace: Couldn't activate tracepoint"
			" probe to kernel_sched_wakeup\n");
		return ret;
	}

	ret = register_trace_sched_wakeup_new(probe_sched_wakeup);
	if (ret) {
		pr_info("wakeup trace: Couldn't activate tracepoint"
			" probe to kernel_sched_wakeup_new\n");
		goto fail_deprobe;
	}

	ret = register_trace_sched_switch(probe_sched_switch);
	if (ret) {
		pr_info("sched trace: Couldn't activate tracepoint"
			" probe to kernel_sched_switch\n");
		goto fail_deprobe_wake_new;
	}

	return ret;
fail_deprobe_wake_new:
	unregister_trace_sched_wakeup_new(probe_sched_wakeup);
fail_deprobe:
	unregister_trace_sched_wakeup(probe_sched_wakeup);
	return ret;
}