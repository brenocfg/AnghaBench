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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct fwentry {int /*<<< orphan*/  intfw_size; int /*<<< orphan*/  intfw; int /*<<< orphan*/  board_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_DEVSTART ; 
 int HZ ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  at76_is_505a (int /*<<< orphan*/ ) ; 
 int at76_remap (struct usb_device*) ; 
 int at76_usbdfu_download (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 
 int /*<<< orphan*/  usb_reset_device (struct usb_device*) ; 

__attribute__((used)) static int at76_load_internal_fw(struct usb_device *udev, struct fwentry *fwe)
{
	int ret;
	int need_remap = !at76_is_505a(fwe->board_type);

	ret = at76_usbdfu_download(udev, fwe->intfw, fwe->intfw_size,
				   need_remap ? 0 : 2 * HZ);

	if (ret < 0) {
		dev_printk(KERN_ERR, &udev->dev,
			   "downloading internal fw failed with %d\n", ret);
		goto exit;
	}

	at76_dbg(DBG_DEVSTART, "sending REMAP");

	/* no REMAP for 505A (see SF driver) */
	if (need_remap) {
		ret = at76_remap(udev);
		if (ret < 0) {
			dev_printk(KERN_ERR, &udev->dev,
				   "sending REMAP failed with %d\n", ret);
			goto exit;
		}
	}

	at76_dbg(DBG_DEVSTART, "sleeping for 2 seconds");
	schedule_timeout_interruptible(2 * HZ + 1);
	usb_reset_device(udev);

exit:
	return ret;
}