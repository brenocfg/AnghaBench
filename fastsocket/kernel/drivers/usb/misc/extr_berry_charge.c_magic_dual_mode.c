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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,char*,int,int) ; 
 int usb_driver_set_configuration (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int magic_dual_mode(struct usb_device *udev)
{
	char *dummy_buffer = kzalloc(2, GFP_KERNEL);
	int retval;

	if (!dummy_buffer)
		return -ENOMEM;

	/* send magic command so that the Blackberry Pearl device exposes
	 * two interfaces: both the USB mass-storage one and one which can
	 * be used for database access. */
	dbg(&udev->dev, "Sending magic pearl command\n");
	retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 0xa9, 0xc0, 1, 1, dummy_buffer, 2, 100);
	dbg(&udev->dev, "Magic pearl command returned %d\n", retval);

	dbg(&udev->dev, "Calling set_configuration\n");
	retval = usb_driver_set_configuration(udev, 1);
	if (retval)
		dev_err(&udev->dev, "Set Configuration failed :%d.\n", retval);

	kfree(dummy_buffer);
	return retval;
}