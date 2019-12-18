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
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {int /*<<< orphan*/  ops_lock; TYPE_2__ dev; TYPE_1__* ops; scalar_t__ uie_irq_active; } ;
struct TYPE_3__ {int (* update_irq_enable ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rtc_dev_update_irq_enable_emul (struct rtc_device*,unsigned int) ; 
 int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

int rtc_update_irq_enable(struct rtc_device *rtc, unsigned int enabled)
{
	int err = mutex_lock_interruptible(&rtc->ops_lock);
	if (err)
		return err;

#ifdef CONFIG_RTC_INTF_DEV_UIE_EMUL
	if (enabled == 0 && rtc->uie_irq_active) {
		mutex_unlock(&rtc->ops_lock);
		return rtc_dev_update_irq_enable_emul(rtc, enabled);
	}
#endif

	if (!rtc->ops)
		err = -ENODEV;
	else if (!rtc->ops->update_irq_enable)
		err = -EINVAL;
	else
		err = rtc->ops->update_irq_enable(rtc->dev.parent, enabled);

	mutex_unlock(&rtc->ops_lock);

#ifdef CONFIG_RTC_INTF_DEV_UIE_EMUL
	/*
	 * Enable emulation if the driver did not provide
	 * the update_irq_enable function pointer or if returned
	 * -EINVAL to signal that it has been configured without
	 * interrupts or that are not available at the moment.
	 */
	if (err == -EINVAL)
		err = rtc_dev_update_irq_enable_emul(rtc, enabled);
#endif
	return err;
}