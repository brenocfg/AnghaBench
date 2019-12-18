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
struct ring_buffer_per_cpu {int /*<<< orphan*/  reader_lock; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int rb_ok_to_lock () ; 
 int rb_per_cpu_empty (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int ring_buffer_empty_cpu(struct ring_buffer *buffer, int cpu)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	unsigned long flags;
	int dolock;
	int ret;

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		return 1;

	dolock = rb_ok_to_lock();

	cpu_buffer = buffer->buffers[cpu];
	local_irq_save(flags);
	if (dolock)
		spin_lock(&cpu_buffer->reader_lock);
	ret = rb_per_cpu_empty(cpu_buffer);
	if (dolock)
		spin_unlock(&cpu_buffer->reader_lock);
	local_irq_restore(flags);

	return ret;
}