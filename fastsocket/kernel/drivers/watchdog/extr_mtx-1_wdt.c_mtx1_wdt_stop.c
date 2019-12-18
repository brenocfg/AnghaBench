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
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  default_ticks; int /*<<< orphan*/  gpio; scalar_t__ queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ mtx1_wdt_device ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static int mtx1_wdt_stop(void)
{
	unsigned long flags;

	spin_lock_irqsave(&mtx1_wdt_device.lock, flags);
	if (mtx1_wdt_device.queue) {
		mtx1_wdt_device.queue = 0;
		gpio_set_value(mtx1_wdt_device.gpio, 0);
	}
	ticks = mtx1_wdt_device.default_ticks;
	spin_unlock_irqrestore(&mtx1_wdt_device.lock, flags);
	return 0;
}