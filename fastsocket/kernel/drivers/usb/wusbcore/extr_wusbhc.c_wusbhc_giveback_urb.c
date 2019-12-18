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
struct wusbhc {int /*<<< orphan*/  usb_hcd; } ;
struct wusb_dev {int /*<<< orphan*/  devconnect_acked_work; int /*<<< orphan*/  cack_node; int /*<<< orphan*/  entry_ts; } ;
struct urb {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct wusb_dev* __wusb_dev_get_by_usb_dev (struct wusbhc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_hcd_giveback_urb (int /*<<< orphan*/ *,struct urb*,int) ; 
 int /*<<< orphan*/  wusb_dev_put (struct wusb_dev*) ; 
 int /*<<< orphan*/  wusbd ; 

void wusbhc_giveback_urb(struct wusbhc *wusbhc, struct urb *urb, int status)
{
	struct wusb_dev *wusb_dev = __wusb_dev_get_by_usb_dev(wusbhc, urb->dev);

	if (status == 0 && wusb_dev) {
		wusb_dev->entry_ts = jiffies;

		/* wusbhc_devconnect_acked() can't be called from
		   atomic context so defer it to a work queue. */
		if (!list_empty(&wusb_dev->cack_node))
			queue_work(wusbd, &wusb_dev->devconnect_acked_work);
		else
			wusb_dev_put(wusb_dev);
	}

	usb_hcd_giveback_urb(&wusbhc->usb_hcd, urb, status);
}