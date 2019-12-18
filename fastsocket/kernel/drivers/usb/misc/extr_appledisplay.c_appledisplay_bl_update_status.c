#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
struct appledisplay {int* msgdata; int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACD_USB_BRIGHTNESS ; 
 int /*<<< orphan*/  ACD_USB_TIMEOUT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_INTERFACE ; 
 int /*<<< orphan*/  USB_REQ_SET_REPORT ; 
 int USB_TYPE_CLASS ; 
 struct appledisplay* bl_get_data (struct backlight_device*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int appledisplay_bl_update_status(struct backlight_device *bd)
{
	struct appledisplay *pdata = bl_get_data(bd);
	int retval;

	pdata->msgdata[0] = 0x10;
	pdata->msgdata[1] = bd->props.brightness;

	retval = usb_control_msg(
		pdata->udev,
		usb_sndctrlpipe(pdata->udev, 0),
		USB_REQ_SET_REPORT,
		USB_DIR_OUT | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
		ACD_USB_BRIGHTNESS,
		0,
		pdata->msgdata, 2,
		ACD_USB_TIMEOUT);

	return retval;
}