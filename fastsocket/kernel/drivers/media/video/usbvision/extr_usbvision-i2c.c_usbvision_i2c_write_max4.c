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
struct usb_usbvision {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int DBG_I2C ; 
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  PDEBUG (int,char*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  USBVISION_OP_CODE ; 
 scalar_t__ USBVISION_SER_ADRS ; 
 int /*<<< orphan*/  USBVISION_SER_CONT ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_ENDPOINT ; 
 int USB_TYPE_VENDOR ; 
 int i2c_debug ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int) ; 
 int usbvision_read_reg (struct usb_usbvision*,int /*<<< orphan*/ ) ; 
 int usbvision_write_reg (struct usb_usbvision*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int usbvision_i2c_write_max4(struct usb_usbvision *usbvision,
				 unsigned char addr, const char *buf,
				 short len)
{
	int rc, retries;
	int i;
	unsigned char value[6];
	unsigned char ser_cont;

	ser_cont = (len & 0x07) | 0x10;

	value[0] = addr;
	value[1] = ser_cont;
	for (i = 0; i < len; i++)
		value[i + 2] = buf[i];

	for (retries = 5;;) {
		rc = usb_control_msg(usbvision->dev,
				     usb_sndctrlpipe(usbvision->dev, 1),
				     USBVISION_OP_CODE,
				     USB_DIR_OUT | USB_TYPE_VENDOR |
				     USB_RECIP_ENDPOINT, 0,
				     (__u16) USBVISION_SER_ADRS, value,
				     len + 2, HZ);

		if (rc < 0)
			return rc;

		rc = usbvision_write_reg(usbvision, USBVISION_SER_CONT,
				      (len & 0x07) | 0x10);
		if (rc < 0)
			return rc;

		/* Test for Busy and ACK */
		do {
			rc = usbvision_read_reg(usbvision, USBVISION_SER_CONT);
		} while (rc > 0 && ((rc & 0x10) != 0));	/* Retry while busy */
		if (rc < 0)
			return rc;

		if ((rc & 0x20) == 0)	/* Ack? */
			break;

		/* I2C abort */
		usbvision_write_reg(usbvision, USBVISION_SER_CONT, 0x00);

		if (--retries < 0)
			return -1;

	}

	if (i2c_debug & DBG_I2C) {
		int idx;

		for (idx = 0; idx < len; idx++)
			PDEBUG(DBG_I2C, "wrote %x at address %x", (unsigned char)buf[idx], addr);
	}
	return len;
}