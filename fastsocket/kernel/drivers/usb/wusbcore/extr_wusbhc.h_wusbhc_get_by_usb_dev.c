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
struct wusbhc {int dummy; } ;
struct usb_hcd {scalar_t__ wireless; } ;
struct usb_device {int devnum; int /*<<< orphan*/  wusb; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 struct usb_hcd* usb_hcd_get_by_usb_dev (struct usb_device*) ; 
 struct wusbhc* usb_hcd_to_wusbhc (struct usb_hcd*) ; 

__attribute__((used)) static inline struct wusbhc *wusbhc_get_by_usb_dev(struct usb_device *usb_dev)
{
	struct wusbhc *wusbhc = NULL;
	struct usb_hcd *usb_hcd;
	if (usb_dev->devnum > 1 && !usb_dev->wusb) {
		/* but root hubs */
		dev_err(&usb_dev->dev, "devnum %d wusb %d\n", usb_dev->devnum,
			usb_dev->wusb);
		BUG_ON(usb_dev->devnum > 1 && !usb_dev->wusb);
	}
	usb_hcd = usb_hcd_get_by_usb_dev(usb_dev);
	if (usb_hcd == NULL)
		return NULL;
	BUG_ON(usb_hcd->wireless == 0);
	return wusbhc = usb_hcd_to_wusbhc(usb_hcd);
}