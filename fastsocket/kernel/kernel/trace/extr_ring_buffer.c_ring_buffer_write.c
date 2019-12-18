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
struct ring_buffer_per_cpu {int /*<<< orphan*/  record_disabled; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  record_disabled; } ;

/* Variables and functions */
 unsigned long BUF_MAX_DATA_SIZE ; 
 int EBUSY ; 
 scalar_t__ RB_BUFFERS_ON ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int ftrace_preempt_disable () ; 
 int /*<<< orphan*/  ftrace_preempt_enable (int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,unsigned long) ; 
 int raw_smp_processor_id () ; 
 int /*<<< orphan*/  rb_commit (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 
 void* rb_event_data (struct ring_buffer_event*) ; 
 struct ring_buffer_event* rb_reserve_next_event (struct ring_buffer*,struct ring_buffer_per_cpu*,unsigned long) ; 
 scalar_t__ ring_buffer_flags ; 

int ring_buffer_write(struct ring_buffer *buffer,
			unsigned long length,
			void *data)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	struct ring_buffer_event *event;
	void *body;
	int ret = -EBUSY;
	int cpu, resched;

	if (ring_buffer_flags != RB_BUFFERS_ON)
		return -EBUSY;

	resched = ftrace_preempt_disable();

	if (atomic_read(&buffer->record_disabled))
		goto out;

	cpu = raw_smp_processor_id();

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		goto out;

	cpu_buffer = buffer->buffers[cpu];

	if (atomic_read(&cpu_buffer->record_disabled))
		goto out;

	if (length > BUF_MAX_DATA_SIZE)
		goto out;

	event = rb_reserve_next_event(buffer, cpu_buffer, length);
	if (!event)
		goto out;

	body = rb_event_data(event);

	memcpy(body, data, length);

	rb_commit(cpu_buffer, event);

	ret = 0;
 out:
	ftrace_preempt_enable(resched);

	return ret;
}