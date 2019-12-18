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
struct usb_se401 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SE401_REQ_GET_EXT_FEATURE ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned short,unsigned char*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned short se401_get_feature(struct usb_se401 *se401,
					unsigned short selector)
{
	/* For 'set' the selecetor should be in index, not sure if the spec is
	   wrong here to....
	 */
	unsigned char cp[2];
	usb_control_msg(
		se401->dev,
		usb_rcvctrlpipe(se401->dev, 0),
		SE401_REQ_GET_EXT_FEATURE,
		USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		0,
		selector,
		cp,
		2,
		1000
	);
	return cp[0]+cp[1]*256;
}