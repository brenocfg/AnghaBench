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
struct input_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MK712_CONTROL ; 
 int MK712_ENABLE_INT ; 
 int MK712_ENABLE_PERIODIC_CONVERSIONS ; 
 int MK712_INT_ON_CHANGE_IN_TOUCH_STATUS ; 
 int MK712_INT_ON_CONVERSION_COMPLETE ; 
 int MK712_POWERUP ; 
 scalar_t__ MK712_RATE ; 
 scalar_t__ mk712_io ; 
 int /*<<< orphan*/  mk712_lock ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mk712_open(struct input_dev *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&mk712_lock, flags);

	outb(0, mk712_io + MK712_CONTROL); /* Reset */

	outb(MK712_ENABLE_INT | MK712_INT_ON_CONVERSION_COMPLETE |
		MK712_INT_ON_CHANGE_IN_TOUCH_STATUS |
		MK712_ENABLE_PERIODIC_CONVERSIONS |
		MK712_POWERUP, mk712_io + MK712_CONTROL);

	outb(10, mk712_io + MK712_RATE); /* 187 points per second */

	spin_unlock_irqrestore(&mk712_lock, flags);

	return 0;
}