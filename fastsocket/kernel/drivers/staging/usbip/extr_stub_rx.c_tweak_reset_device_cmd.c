#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct usb_ctrlrequest {int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
struct urb {TYPE_1__* dev; scalar_t__ setup_packet; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_lock_device_for_reset (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int usb_reset_device (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_unlock_device (TYPE_1__*) ; 
 int /*<<< orphan*/  usbip_uinfo (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tweak_reset_device_cmd(struct urb *urb)
{
	struct usb_ctrlrequest *req;
	__u16 value;
	__u16 index;
	int ret;

	req = (struct usb_ctrlrequest *) urb->setup_packet;
	value = le16_to_cpu(req->wValue);
	index = le16_to_cpu(req->wIndex);

	usbip_uinfo("reset_device (port %d) to %s\n", index,
						dev_name(&urb->dev->dev));

	/* all interfaces should be owned by usbip driver, so just reset it.  */
	ret = usb_lock_device_for_reset(urb->dev, NULL);
	if (ret < 0) {
		dev_err(&urb->dev->dev, "lock for reset\n");
		return ret;
	}

	/* try to reset the device */
	ret = usb_reset_device(urb->dev);
	if (ret < 0)
		dev_err(&urb->dev->dev, "device reset\n");

	usb_unlock_device(urb->dev);

	return ret;
}