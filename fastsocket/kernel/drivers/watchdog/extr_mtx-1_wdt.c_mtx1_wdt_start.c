#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int queue; int /*<<< orphan*/  lock; int /*<<< orphan*/  running; int /*<<< orphan*/  timer; int /*<<< orphan*/  gpio; } ;

/* Variables and functions */
 scalar_t__ MTX1_WDT_INTERVAL ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_1__ mtx1_wdt_device ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mtx1_wdt_start(void)
{
	unsigned long flags;

	spin_lock_irqsave(&mtx1_wdt_device.lock, flags);
	if (!mtx1_wdt_device.queue) {
		mtx1_wdt_device.queue = 1;
		gpio_set_value(mtx1_wdt_device.gpio, 1);
		mod_timer(&mtx1_wdt_device.timer, jiffies + MTX1_WDT_INTERVAL);
	}
	mtx1_wdt_device.running++;
	spin_unlock_irqrestore(&mtx1_wdt_device.lock, flags);
}