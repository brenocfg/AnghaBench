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
typedef  int u32 ;
struct usb_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  USB_REG_OUT_PIPE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int*,int,int /*<<< orphan*/ ) ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath9k_hif_usb_reboot(struct usb_device *udev)
{
	u32 reboot_cmd = 0xffffffff;
	void *buf;
	int ret;

	buf = kmemdup(&reboot_cmd, 4, GFP_KERNEL);
	if (!buf)
		return;

	ret = usb_bulk_msg(udev, usb_sndbulkpipe(udev, USB_REG_OUT_PIPE),
			   buf, 4, NULL, HZ);
	if (ret)
		dev_err(&udev->dev, "ath9k_htc: USB reboot failed\n");

	kfree(buf);
}