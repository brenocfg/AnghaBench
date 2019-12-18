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
struct rc_dev {TYPE_1__* raw; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

void ir_raw_event_handle(struct rc_dev *dev)
{
	unsigned long flags;

	if (!dev->raw)
		return;

	spin_lock_irqsave(&dev->raw->lock, flags);
	wake_up_process(dev->raw->thread);
	spin_unlock_irqrestore(&dev->raw->lock, flags);
}