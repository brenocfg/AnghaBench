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
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ qlen; } ;
struct usbnet {int /*<<< orphan*/  net; TYPE_1__ txq; int /*<<< orphan*/  flags; int /*<<< orphan*/  suspend_count; } ;
struct usb_interface {int dummy; } ;
struct TYPE_5__ {int event; } ;
typedef  TYPE_2__ pm_message_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EVENT_DEV_ASLEEP ; 
 int PM_EVENT_AUTO ; 
 int /*<<< orphan*/  __usbnet_status_stop_force (struct usbnet*) ; 
 int /*<<< orphan*/  netif_device_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct usbnet* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usbnet_terminate_urbs (struct usbnet*) ; 

int usbnet_suspend (struct usb_interface *intf, pm_message_t message)
{
	struct usbnet		*dev = usb_get_intfdata(intf);

	if (!dev->suspend_count++) {
		spin_lock_irq(&dev->txq.lock);
		/* don't autosuspend while transmitting */
		if (dev->txq.qlen && (message.event & PM_EVENT_AUTO)) {
			spin_unlock_irq(&dev->txq.lock);
			return -EBUSY;
		} else {
			set_bit(EVENT_DEV_ASLEEP, &dev->flags);
			spin_unlock_irq(&dev->txq.lock);
		}
		/*
		 * accelerate emptying of the rx and queues, to avoid
		 * having everything error out.
		 */
		netif_device_detach (dev->net);
		usbnet_terminate_urbs(dev);
		__usbnet_status_stop_force(dev);

		/*
		 * reattach so runtime management can use and
		 * wake the device
		 */
		netif_device_attach (dev->net);
	}
	return 0;
}