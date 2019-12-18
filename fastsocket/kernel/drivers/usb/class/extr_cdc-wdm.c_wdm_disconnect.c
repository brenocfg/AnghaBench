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
struct wdm_device {int /*<<< orphan*/  count; int /*<<< orphan*/  wait; int /*<<< orphan*/  rxwork; int /*<<< orphan*/  iuspin; int /*<<< orphan*/  flags; } ;
struct usb_interface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WDM_DISCONNECTING ; 
 int /*<<< orphan*/  WDM_IN_USE ; 
 int /*<<< orphan*/  WDM_READ ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cleanup (struct wdm_device*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_urbs (struct wdm_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usb_deregister_dev (struct usb_interface*,int /*<<< orphan*/ *) ; 
 struct wdm_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdm_class ; 
 int /*<<< orphan*/  wdm_mutex ; 

__attribute__((used)) static void wdm_disconnect(struct usb_interface *intf)
{
	struct wdm_device *desc;
	unsigned long flags;

	usb_deregister_dev(intf, &wdm_class);
	mutex_lock(&wdm_mutex);
	desc = usb_get_intfdata(intf);

	/* the spinlock makes sure no new urbs are generated in the callbacks */
	spin_lock_irqsave(&desc->iuspin, flags);
	set_bit(WDM_DISCONNECTING, &desc->flags);
	set_bit(WDM_READ, &desc->flags);
	/* to terminate pending flushes */
	clear_bit(WDM_IN_USE, &desc->flags);
	spin_unlock_irqrestore(&desc->iuspin, flags);
	cancel_work_sync(&desc->rxwork);
	kill_urbs(desc);
	wake_up_all(&desc->wait);
	if (!desc->count)
		cleanup(desc);
	mutex_unlock(&wdm_mutex);
}