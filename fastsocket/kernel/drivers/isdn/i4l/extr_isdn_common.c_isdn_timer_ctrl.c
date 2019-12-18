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
struct TYPE_2__ {int tflags; int /*<<< orphan*/  timerlock; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ ISDN_TIMER_RES ; 
 int ISDN_TIMER_SLOW ; 
 TYPE_1__* dev ; 
 scalar_t__ isdn_timer_cnt1 ; 
 scalar_t__ isdn_timer_cnt2 ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
isdn_timer_ctrl(int tf, int onoff)
{
	unsigned long flags;
	int old_tflags;

	spin_lock_irqsave(&dev->timerlock, flags);
	if ((tf & ISDN_TIMER_SLOW) && (!(dev->tflags & ISDN_TIMER_SLOW))) {
		/* If the slow-timer wasn't activated until now */
		isdn_timer_cnt1 = 0;
		isdn_timer_cnt2 = 0;
	}
	old_tflags = dev->tflags;
	if (onoff)
		dev->tflags |= tf;
	else
		dev->tflags &= ~tf;
	if (dev->tflags && !old_tflags)
		mod_timer(&dev->timer, jiffies+ISDN_TIMER_RES);
	spin_unlock_irqrestore(&dev->timerlock, flags);
}