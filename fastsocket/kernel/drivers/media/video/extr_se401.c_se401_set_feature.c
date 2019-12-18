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
 int /*<<< orphan*/  SE401_REQ_SET_EXT_FEATURE ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned short,unsigned short,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int se401_set_feature(struct usb_se401 *se401, unsigned short selector,
			     unsigned short param)
{
	/* specs say that the selector (address) should go in the value field
	   and the param in index, but in the logs of the windows driver they do
	   this the other way around...
	 */
	return usb_control_msg(
		se401->dev,
		usb_sndctrlpipe(se401->dev, 0),
		SE401_REQ_SET_EXT_FEATURE,
		USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
		param,
		selector,
		NULL,
		0,
		1000
	);
}