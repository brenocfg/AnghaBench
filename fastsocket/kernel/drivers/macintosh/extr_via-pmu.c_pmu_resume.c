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
 int CB1_INT ; 
 size_t IER ; 
 int IER_SET ; 
 int adb_int_pending ; 
 int /*<<< orphan*/  enable_irq (scalar_t__) ; 
 scalar_t__ gpio_irq ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmu_lock ; 
 int /*<<< orphan*/  pmu_poll () ; 
 int pmu_suspended ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * via ; 

void
pmu_resume(void)
{
	unsigned long flags;

	if (!via || (pmu_suspended < 1))
		return;

	spin_lock_irqsave(&pmu_lock, flags);
	pmu_suspended--;
	if (pmu_suspended > 0) {
		spin_unlock_irqrestore(&pmu_lock, flags);
		return;
	}
	adb_int_pending = 1;
	if (gpio_irq >= 0)
		enable_irq(gpio_irq);
	out_8(&via[IER], CB1_INT | IER_SET);
	spin_unlock_irqrestore(&pmu_lock, flags);
	pmu_poll();
}