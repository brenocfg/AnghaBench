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
struct usb_device {int dummy; } ;
struct TYPE_2__ {scalar_t__* usb_buf; struct usb_device* dev; } ;
struct sd {scalar_t__ bridge; TYPE_1__ gspca_dev; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 scalar_t__ BRIDGE_STV610 ; 
 int /*<<< orphan*/  STV06XX_URB_MSG_TIMEOUT ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stv06xx_write_sensor_finish(struct sd *sd)
{
	int err = 0;

	if (sd->bridge == BRIDGE_STV610) {
		struct usb_device *udev = sd->gspca_dev.dev;
		__u8 *buf = sd->gspca_dev.usb_buf;

		buf[0] = 0;
		err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				      0x04, 0x40, 0x1704, 0, buf, 1,
				      STV06XX_URB_MSG_TIMEOUT);
	}

	return (err < 0) ? err : 0;
}