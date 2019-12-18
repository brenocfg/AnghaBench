#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rtc_task {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {TYPE_1__ dev; TYPE_2__* ops; int /*<<< orphan*/  irq_task_lock; struct rtc_task* irq_task; } ;
struct TYPE_4__ {int (* irq_set_state ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EACCES ; 
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int rtc_irq_set_state(struct rtc_device *rtc, struct rtc_task *task, int enabled)
{
	int err = 0;
	unsigned long flags;

	if (rtc->ops->irq_set_state == NULL)
		return -ENXIO;

	spin_lock_irqsave(&rtc->irq_task_lock, flags);
	if (rtc->irq_task != NULL && task == NULL)
		err = -EBUSY;
	if (rtc->irq_task != task)
		err = -EACCES;
	spin_unlock_irqrestore(&rtc->irq_task_lock, flags);

	if (err == 0)
		err = rtc->ops->irq_set_state(rtc->dev.parent, enabled);

	return err;
}