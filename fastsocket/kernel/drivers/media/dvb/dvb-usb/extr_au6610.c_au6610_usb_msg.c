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
typedef  int /*<<< orphan*/  usb_buf ;
typedef  int u8 ;
typedef  int u16 ;
struct dvb_usb_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
#define  AU6610_REQ_I2C_READ 129 
#define  AU6610_REQ_USB_READ 128 
 int /*<<< orphan*/  AU6610_USB_TIMEOUT ; 
 int EINVAL ; 
 int USB_DIR_IN ; 
 int USB_TYPE_VENDOR ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,int) ; 

__attribute__((used)) static int au6610_usb_msg(struct dvb_usb_device *d, u8 operation, u8 addr,
			  u8 *wbuf, u16 wlen, u8 *rbuf, u16 rlen)
{
	int ret;
	u16 index;
	u8 usb_buf[6]; /* enough for all known requests,
			  read returns 5 and write 6 bytes */
	switch (wlen) {
	case 1:
		index = wbuf[0] << 8;
		break;
	case 2:
		index = wbuf[0] << 8;
		index += wbuf[1];
		break;
	default:
		warn("wlen = %x, aborting.", wlen);
		return -EINVAL;
	}

	ret = usb_control_msg(d->udev, usb_rcvctrlpipe(d->udev, 0), operation,
			      USB_TYPE_VENDOR|USB_DIR_IN, addr << 1, index,
			      usb_buf, sizeof(usb_buf), AU6610_USB_TIMEOUT);
	if (ret < 0)
		return ret;

	switch (operation) {
	case AU6610_REQ_I2C_READ:
	case AU6610_REQ_USB_READ:
		/* requested value is always 5th byte in buffer */
		rbuf[0] = usb_buf[4];
	}

	return ret;
}