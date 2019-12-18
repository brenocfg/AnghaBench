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
struct cm109_dev {int ctl_urb_pending; int buzzer_pending; int /*<<< orphan*/  ctl_submit_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cm109_submit_buzz_toggle (struct cm109_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void cm109_toggle_buzzer_async(struct cm109_dev *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->ctl_submit_lock, flags);

	if (dev->ctl_urb_pending) {
		/* URB completion will resubmit */
		dev->buzzer_pending = 1;
	} else {
		dev->ctl_urb_pending = 1;
		cm109_submit_buzz_toggle(dev);
	}

	spin_unlock_irqrestore(&dev->ctl_submit_lock, flags);
}