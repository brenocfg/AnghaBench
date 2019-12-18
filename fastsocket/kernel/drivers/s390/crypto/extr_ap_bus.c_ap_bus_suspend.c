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
struct device {int dummy; } ;
struct ap_device {int unregistered; int /*<<< orphan*/  lock; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  __ap_poll_device (struct ap_device*,unsigned long*) ; 
 int /*<<< orphan*/  ap_config_timer ; 
 int ap_suspend_flag ; 
 int /*<<< orphan*/  ap_tasklet ; 
 int /*<<< orphan*/ * ap_work_queue ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 struct ap_device* to_ap_dev (struct device*) ; 

__attribute__((used)) static int ap_bus_suspend(struct device *dev, pm_message_t state)
{
	struct ap_device *ap_dev = to_ap_dev(dev);
	unsigned long flags;

	if (!ap_suspend_flag) {
		ap_suspend_flag = 1;

		/* Disable scanning for devices, thus we do not want to scan
		 * for them after removing.
		 */
		del_timer_sync(&ap_config_timer);
		if (ap_work_queue != NULL) {
			destroy_workqueue(ap_work_queue);
			ap_work_queue = NULL;
		}

		tasklet_disable(&ap_tasklet);
	}
	/* Poll on the device until all requests are finished. */
	do {
		flags = 0;
		spin_lock_bh(&ap_dev->lock);
		__ap_poll_device(ap_dev, &flags);
		spin_unlock_bh(&ap_dev->lock);
	} while ((flags & 1) || (flags & 2));

	spin_lock_bh(&ap_dev->lock);
	ap_dev->unregistered = 1;
	spin_unlock_bh(&ap_dev->lock);

	return 0;
}