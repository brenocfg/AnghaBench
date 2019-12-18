#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct urb {TYPE_1__* dev; int /*<<< orphan*/  use_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIDRM ; 
 int EINPROGRESS ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct usb_hcd* bus_to_hcd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct urb*,int) ; 
 int /*<<< orphan*/  hcd_urb_unlink_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int unlink1 (struct usb_hcd*,struct urb*,int) ; 
 int /*<<< orphan*/  usb_get_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_put_dev (TYPE_1__*) ; 

int usb_hcd_unlink_urb (struct urb *urb, int status)
{
	struct usb_hcd		*hcd;
	int			retval = -EIDRM;
	unsigned long		flags;

	/* Prevent the device and bus from going away while
	 * the unlink is carried out.  If they are already gone
	 * then urb->use_count must be 0, since disconnected
	 * devices can't have any active URBs.
	 */
	spin_lock_irqsave(&hcd_urb_unlink_lock, flags);
	if (atomic_read(&urb->use_count) > 0) {
		retval = 0;
		usb_get_dev(urb->dev);
	}
	spin_unlock_irqrestore(&hcd_urb_unlink_lock, flags);
	if (retval == 0) {
		hcd = bus_to_hcd(urb->dev->bus);
		retval = unlink1(hcd, urb, status);
		usb_put_dev(urb->dev);
	}

	if (retval == 0)
		retval = -EINPROGRESS;
	else if (retval != -EIDRM && retval != -EBUSY)
		dev_dbg(&urb->dev->dev, "hcd_unlink_urb %p fail %d\n",
				urb, retval);
	return retval;
}