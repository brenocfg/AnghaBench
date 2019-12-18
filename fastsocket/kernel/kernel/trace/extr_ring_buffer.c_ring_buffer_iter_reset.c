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
struct ring_buffer_iter {struct ring_buffer_per_cpu* cpu_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_iter_reset (struct ring_buffer_iter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ring_buffer_iter_reset(struct ring_buffer_iter *iter)
{
	struct ring_buffer_per_cpu *cpu_buffer;
	unsigned long flags;

	if (!iter)
		return;

	cpu_buffer = iter->cpu_buffer;

	spin_lock_irqsave(&cpu_buffer->reader_lock, flags);
	rb_iter_reset(iter);
	spin_unlock_irqrestore(&cpu_buffer->reader_lock, flags);
}