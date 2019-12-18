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
struct TYPE_2__ {unsigned long timer_expires; int /*<<< orphan*/  lock; } ;
struct device {TYPE_1__ power; } ;

/* Variables and functions */
 int /*<<< orphan*/  __pm_request_suspend (struct device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_after (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pm_suspend_timer_fn(unsigned long data)
{
	struct device *dev = (struct device *)data;
	unsigned long flags;
	unsigned long expires;

	spin_lock_irqsave(&dev->power.lock, flags);

	expires = dev->power.timer_expires;
	/* If 'expire' is after 'jiffies' we've been called too early. */
	if (expires > 0 && !time_after(expires, jiffies)) {
		dev->power.timer_expires = 0;
		__pm_request_suspend(dev);
	}

	spin_unlock_irqrestore(&dev->power.lock, flags);
}