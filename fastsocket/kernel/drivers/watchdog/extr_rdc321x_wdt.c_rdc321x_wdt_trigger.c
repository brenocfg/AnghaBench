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
struct TYPE_2__ {int /*<<< orphan*/  stop; int /*<<< orphan*/  timer; scalar_t__ queue; int /*<<< orphan*/  lock; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDC3210_CFGREG_DATA ; 
 int RDC_WDT_EN ; 
 scalar_t__ RDC_WDT_INTERVAL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int inl (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  outl (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ rdc321x_wdt_device ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ticks ; 

__attribute__((used)) static void rdc321x_wdt_trigger(unsigned long unused)
{
	unsigned long flags;

	if (rdc321x_wdt_device.running)
		ticks--;

	/* keep watchdog alive */
	spin_lock_irqsave(&rdc321x_wdt_device.lock, flags);
	outl(RDC_WDT_EN | inl(RDC3210_CFGREG_DATA),
		RDC3210_CFGREG_DATA);
	spin_unlock_irqrestore(&rdc321x_wdt_device.lock, flags);

	/* requeue?? */
	if (rdc321x_wdt_device.queue && ticks)
		mod_timer(&rdc321x_wdt_device.timer,
				jiffies + RDC_WDT_INTERVAL);
	else {
		/* ticks doesn't matter anyway */
		complete(&rdc321x_wdt_device.stop);
	}

}