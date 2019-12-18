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
typedef  int u8 ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  info (char*,int,int) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int,int*,int,int) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lme2510_return_status(struct usb_device *dev)
{
	int ret = 0;
	u8 data[10] = {0};

	ret |= usb_control_msg(dev, usb_rcvctrlpipe(dev, 0),
			0x06, 0x80, 0x0302, 0x00, data, 0x0006, 200);
	info("Firmware Status: %x (%x)", ret , data[2]);

	return (ret < 0) ? -ENODEV : data[2];
}