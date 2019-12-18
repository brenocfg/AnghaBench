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
struct orinoco_private {struct ezusb_priv* card; } ;
struct ezusb_priv {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_TIMEOUT ; 
 int /*<<< orphan*/  EZUSB_REQUEST_TRIGER ; 
 int /*<<< orphan*/  EZUSB_REQUEST_TRIG_AC ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int ezusb_8051_cpucs (struct ezusb_priv*,int) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ezusb_hard_reset(struct orinoco_private *priv)
{
	struct ezusb_priv *upriv = priv->card;
	int retval = ezusb_8051_cpucs(upriv, 1);

	if (retval < 0) {
		err("Failed to reset");
		return retval;
	}

	retval = ezusb_8051_cpucs(upriv, 0);
	if (retval < 0) {
		err("Failed to unreset");
		return retval;
	}

	dbg("sending control message");
	retval = usb_control_msg(upriv->udev,
				 usb_sndctrlpipe(upriv->udev, 0),
				 EZUSB_REQUEST_TRIGER,
				 USB_TYPE_VENDOR | USB_RECIP_DEVICE |
				 USB_DIR_OUT, 0x0, 0x0, NULL, 0,
				 DEF_TIMEOUT);
	if (retval < 0) {
		err("EZUSB_REQUEST_TRIGER failed retval %d", retval);
		return retval;
	}
#if 0
	dbg("Sending EZUSB_REQUEST_TRIG_AC");
	retval = usb_control_msg(upriv->udev,
				 usb_sndctrlpipe(upriv->udev, 0),
				 EZUSB_REQUEST_TRIG_AC,
				 USB_TYPE_VENDOR | USB_RECIP_DEVICE |
				 USB_DIR_OUT, 0x00FA, 0x0, NULL, 0,
				 DEF_TIMEOUT);
	if (retval < 0) {
		err("EZUSB_REQUEST_TRIG_AC failed retval %d", retval);
		return retval;
	}
#endif

	return 0;
}