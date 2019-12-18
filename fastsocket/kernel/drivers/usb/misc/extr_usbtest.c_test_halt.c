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
struct usbtest_dev {int dummy; } ;
struct urb {int /*<<< orphan*/  pipe; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct usbtest_dev*,char*,int,int) ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  USB_ENDPOINT_HALT ; 
 int /*<<< orphan*/  USB_RECIP_ENDPOINT ; 
 int /*<<< orphan*/  USB_REQ_SET_FEATURE ; 
 int usb_clear_halt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verify_halted (struct usbtest_dev*,int,struct urb*) ; 
 int verify_not_halted (struct usbtest_dev*,int,struct urb*) ; 

__attribute__((used)) static int test_halt(struct usbtest_dev *tdev, int ep, struct urb *urb)
{
	int	retval;

	/* shouldn't look or act halted now */
	retval = verify_not_halted(tdev, ep, urb);
	if (retval < 0)
		return retval;

	/* set halt (protocol test only), verify it worked */
	retval = usb_control_msg (urb->dev, usb_sndctrlpipe (urb->dev, 0),
			USB_REQ_SET_FEATURE, USB_RECIP_ENDPOINT,
			USB_ENDPOINT_HALT, ep,
			NULL, 0, USB_CTRL_SET_TIMEOUT);
	if (retval < 0) {
		ERROR(tdev, "ep %02x couldn't set halt, %d\n", ep, retval);
		return retval;
	}
	retval = verify_halted(tdev, ep, urb);
	if (retval < 0)
		return retval;

	/* clear halt (tests API + protocol), verify it worked */
	retval = usb_clear_halt (urb->dev, urb->pipe);
	if (retval < 0) {
		ERROR(tdev, "ep %02x couldn't clear halt, %d\n", ep, retval);
		return retval;
	}
	retval = verify_not_halted(tdev, ep, urb);
	if (retval < 0)
		return retval;

	/* NOTE:  could also verify SET_INTERFACE clear halts ... */

	return 0;
}