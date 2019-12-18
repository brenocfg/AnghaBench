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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int adb_int_pending ; 
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_irq ; 
 scalar_t__ gpio_irq_enabled ; 
 scalar_t__ gpio_reg ; 
 int in_8 (scalar_t__) ; 
 int /*<<< orphan*/ * pmu_irq_stats ; 
 int /*<<< orphan*/  pmu_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  via_pmu_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t
gpio1_interrupt(int irq, void *arg)
{
	unsigned long flags;

	if ((in_8(gpio_reg + 0x9) & 0x02) == 0) {
		spin_lock_irqsave(&pmu_lock, flags);
		if (gpio_irq_enabled > 0) {
			disable_irq_nosync(gpio_irq);
			gpio_irq_enabled = 0;
		}
		pmu_irq_stats[1]++;
		adb_int_pending = 1;
		spin_unlock_irqrestore(&pmu_lock, flags);
		via_pmu_interrupt(0, NULL);
		return IRQ_HANDLED;
	}
	return IRQ_NONE;
}