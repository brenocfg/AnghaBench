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
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,char*,int,int) ; 
 int usb_driver_set_configuration (struct usb_device*,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int magic_charge(struct usb_device *udev)
{
	char *dummy_buffer = kzalloc(2, GFP_KERNEL);
	int retval;

	if (!dummy_buffer)
		return -ENOMEM;

	/* send two magic commands and then set the configuration.  The device
	 * will then reset itself with the new power usage and should start
	 * charging. */

	/* Note, with testing, it only seems that the first message is really
	 * needed (at least for the 8700c), but to be safe, we emulate what
	 * other operating systems seem to be sending to their device.  We
	 * really need to get some specs for this device to be sure about what
	 * is going on here.
	 */
	dbg(&udev->dev, "Sending first magic command\n");
	retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 0xa5, 0xc0, 0, 1, dummy_buffer, 2, 100);
	if (retval != 2) {
		dev_err(&udev->dev, "First magic command failed: %d.\n",
			retval);
		goto exit;
	}

	dbg(&udev->dev, "Sending second magic command\n");
	retval = usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
				 0xa2, 0x40, 0, 1, dummy_buffer, 0, 100);
	if (retval != 0) {
		dev_err(&udev->dev, "Second magic command failed: %d.\n",
			retval);
		goto exit;
	}

	dbg(&udev->dev, "Calling set_configuration\n");
	retval = usb_driver_set_configuration(udev, 1);
	if (retval)
		dev_err(&udev->dev, "Set Configuration failed :%d.\n", retval);

exit:
	kfree(dummy_buffer);
	return retval;
}