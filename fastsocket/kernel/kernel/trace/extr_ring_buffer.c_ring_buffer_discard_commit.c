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
struct ring_buffer_per_cpu {int /*<<< orphan*/  committing; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_WARN_ON (struct ring_buffer*,int) ; 
 int /*<<< orphan*/  ftrace_preempt_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  per_cpu (int /*<<< orphan*/ ,int) ; 
 int preempt_count () ; 
 int /*<<< orphan*/  preempt_enable_no_resched_notrace () ; 
 int /*<<< orphan*/  rb_decrement_entry (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  rb_end_commit (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_event_discard (struct ring_buffer_event*) ; 
 int /*<<< orphan*/  rb_need_resched ; 
 scalar_t__ rb_try_to_discard (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 
 int /*<<< orphan*/  rb_update_write_stamp (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  trace_recursive_unlock () ; 

void ring_buffer_discard_commit(struct ring_buffer *buffer,
				struct ring_buffer_event *event)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	int cpu;

	/* The event is discarded regardless */
	rb_event_discard(event);

	cpu = smp_processor_id();
	cpu_buffer = buffer->buffers[cpu];

	/*
	 * This must only be called if the event has not been
	 * committed yet. Thus we can assume that preemption
	 * is still disabled.
	 */
	RB_WARN_ON(buffer, !local_read(&cpu_buffer->committing));

	rb_decrement_entry(cpu_buffer, event);
	if (rb_try_to_discard(cpu_buffer, event))
		goto out;

	/*
	 * The commit is still visible by the reader, so we
	 * must still update the timestamp.
	 */
	rb_update_write_stamp(cpu_buffer, event);
 out:
	rb_end_commit(cpu_buffer);

	trace_recursive_unlock();

	/*
	 * Only the last preempt count needs to restore preemption.
	 */
	if (preempt_count() == 1)
		ftrace_preempt_enable(per_cpu(rb_need_resched, cpu));
	else
		preempt_enable_no_resched_notrace();

}