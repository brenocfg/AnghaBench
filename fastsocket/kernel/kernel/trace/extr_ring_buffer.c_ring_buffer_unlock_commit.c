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
struct ring_buffer_per_cpu {int dummy; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_preempt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int) ; 
 int preempt_count () ; 
 int /*<<< orphan*/  preempt_enable_no_resched_notrace () ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  rb_commit (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  rb_need_resched ; 
 int /*<<< orphan*/  trace_recursive_unlock () ; 

int ring_buffer_unlock_commit(struct ring_buffer *buffer,
			      struct ring_buffer_event *event)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	int cpu = raw_smp_processor_id();

	cpu_buffer = buffer->buffers[cpu];

	rb_commit(cpu_buffer, event);

	trace_recursive_unlock();

	/*
	 * Only the last preempt count needs to restore preemption.
	 */
	if (preempt_count() == 1)
		ftrace_preempt_enable(per_cpu(rb_need_resched, cpu));
	else
		preempt_enable_no_resched_notrace();

	return 0;
}