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
 int /*<<< orphan*/  active_fds ; 
 int /*<<< orphan*/  irq_lock ; 
 int /*<<< orphan*/  last_irq_ptr ; 
 int /*<<< orphan*/  os_free_irq_by_cb (int (*) (struct irq_fd*,void*),void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void free_irq_by_cb(int (*test)(struct irq_fd *, void *), void *arg)
{
	unsigned long flags;

	spin_lock_irqsave(&irq_lock, flags);
	os_free_irq_by_cb(test, arg, active_fds, &last_irq_ptr);
	spin_unlock_irqrestore(&irq_lock, flags);
}