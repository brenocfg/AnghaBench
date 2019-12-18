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
struct ring_buffer_per_cpu {int /*<<< orphan*/  reader_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  record_disabled; } ;
struct ring_buffer_iter {struct ring_buffer_per_cpu* cpu_buffer; } ;
struct ring_buffer {struct ring_buffer_per_cpu** buffers; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 struct ring_buffer_iter* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_iter_reset (struct ring_buffer_iter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  synchronize_sched () ; 

struct ring_buffer_iter *
ring_buffer_read_start(struct ring_buffer *buffer, int cpu)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	struct ring_buffer_iter *iter;
	unsigned long flags;

	if (!cpumask_test_cpu(cpu, buffer->cpumask))
		return NULL;

	iter = kmalloc(sizeof(*iter), GFP_KERNEL);
	if (!iter)
		return NULL;

	cpu_buffer = buffer->buffers[cpu];

	iter->cpu_buffer = cpu_buffer;

	atomic_inc(&cpu_buffer->record_disabled);
	synchronize_sched();

	spin_lock_irqsave(&cpu_buffer->reader_lock, flags);
	__raw_spin_lock(&cpu_buffer->lock);
	rb_iter_reset(iter);
	__raw_spin_unlock(&cpu_buffer->lock);
	spin_unlock_irqrestore(&cpu_buffer->reader_lock, flags);

	return iter;
}