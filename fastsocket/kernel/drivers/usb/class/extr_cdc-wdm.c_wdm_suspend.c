#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wdm_device {int /*<<< orphan*/  plock; int /*<<< orphan*/  rxwork; int /*<<< orphan*/  flags; TYPE_1__* intf; } ;
struct usb_interface {int /*<<< orphan*/  minor; } ;
struct TYPE_5__ {int event; } ;
typedef  TYPE_2__ pm_message_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int PM_EVENT_AUTO ; 
 int /*<<< orphan*/  WDM_IN_USE ; 
 int /*<<< orphan*/  WDM_RESPONDING ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_urbs (struct wdm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct wdm_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int wdm_suspend(struct usb_interface *intf, pm_message_t message)
{
	struct wdm_device *desc = usb_get_intfdata(intf);
	int rv = 0;

	dev_dbg(&desc->intf->dev, "wdm%d_suspend\n", intf->minor);

	mutex_lock(&desc->plock);
#ifdef CONFIG_PM
	if ((message.event & PM_EVENT_AUTO) &&
			(test_bit(WDM_IN_USE, &desc->flags)
			|| test_bit(WDM_RESPONDING, &desc->flags))) {
		rv = -EBUSY;
	} else {
#endif
		cancel_work_sync(&desc->rxwork);
		kill_urbs(desc);
#ifdef CONFIG_PM
	}
#endif
	mutex_unlock(&desc->plock);

	return rv;
}