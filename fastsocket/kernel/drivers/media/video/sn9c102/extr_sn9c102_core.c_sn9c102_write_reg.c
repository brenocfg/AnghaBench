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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct usb_device {int dummy; } ;
struct sn9c102_device {int /*<<< orphan*/ * reg; int /*<<< orphan*/ * control_buffer; struct usb_device* usbdev; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  SN9C102_CTRL_TIMEOUT ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int sn9c102_write_reg(struct sn9c102_device* cam, u8 value, u16 index)
{
	struct usb_device* udev = cam->usbdev;
	u8* buff = cam->control_buffer;
	int res;

	if (index >= ARRAY_SIZE(cam->reg))
		return -1;

	*buff = value;

	res = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x08, 0x41,
			      index, 0, buff, 1, SN9C102_CTRL_TIMEOUT);
	if (res < 0) {
		DBG(3, "Failed to write a register (value 0x%02X, index "
		       "0x%02X, error %d)", value, index, res);
		return -1;
	}

	cam->reg[index] = value;

	return 0;
}