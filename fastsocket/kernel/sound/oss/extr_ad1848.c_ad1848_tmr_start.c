#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ model; int timer_running; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ ad1848_info ;
struct TYPE_6__ {scalar_t__ devc; } ;

/* Variables and functions */
 scalar_t__ MD_1845 ; 
 scalar_t__ MD_1845_SSCAPE ; 
 int ad_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ad_write (TYPE_1__*,int,int) ; 
 TYPE_2__** audio_devs ; 
 unsigned int current_interval ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int ad1848_tmr_start(int dev, unsigned int usecs)
{
	unsigned long   flags;
	ad1848_info    *devc = (ad1848_info *) audio_devs[dev]->devc;
	unsigned long   xtal_nsecs;	/* nanoseconds per xtal oscillator tick */
	unsigned long   divider;

	spin_lock_irqsave(&devc->lock,flags);

	/*
	 * Length of the timer interval (in nanoseconds) depends on the
	 * selected crystal oscillator. Check this from bit 0x01 of I8.
	 *
	 * AD1845 has just one oscillator which has cycle time of 10.050 us
	 * (when a 24.576 MHz xtal oscillator is used).
	 *
	 * Convert requested interval to nanoseconds before computing
	 * the timer divider.
	 */

	if (devc->model == MD_1845 || devc->model == MD_1845_SSCAPE)
		xtal_nsecs = 10050;
	else if (ad_read(devc, 8) & 0x01)
		xtal_nsecs = 9920;
	else
		xtal_nsecs = 9969;

	divider = (usecs * 1000 + xtal_nsecs / 2) / xtal_nsecs;

	if (divider < 100)	/* Don't allow shorter intervals than about 1ms */
		divider = 100;

	if (divider > 65535)	/* Overflow check */
		divider = 65535;

	ad_write(devc, 21, (divider >> 8) & 0xff);	/* Set upper bits */
	ad_write(devc, 20, divider & 0xff);	/* Set lower bits */
	ad_write(devc, 16, ad_read(devc, 16) | 0x40);	/* Start the timer */
	devc->timer_running = 1;
	spin_unlock_irqrestore(&devc->lock,flags);

	return current_interval = (divider * xtal_nsecs + 500) / 1000;
}