#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_device {int dummy; } ;
struct TYPE_3__ {int* usb_buf; struct usb_device* dev; } ;
struct sd {TYPE_2__* sensor; TYPE_1__ gspca_dev; } ;
typedef  int __u8 ;
struct TYPE_4__ {int i2c_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_CONF ; 
 int /*<<< orphan*/  I2C_BUFFER_LENGTH ; 
 int I2C_MAX_BYTES ; 
 int I2C_WRITE_CMD ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int const,...) ; 
 int /*<<< orphan*/  STV06XX_URB_MSG_TIMEOUT ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stv06xx_write_sensor_finish (struct sd*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int stv06xx_write_sensor_bytes(struct sd *sd, const u8 *data, u8 len)
{
	int err, i, j;
	struct usb_device *udev = sd->gspca_dev.dev;
	__u8 *buf = sd->gspca_dev.usb_buf;

	PDEBUG(D_CONF, "I2C: Command buffer contains %d entries", len);
	for (i = 0; i < len;) {
		/* Build the command buffer */
		memset(buf, 0, I2C_BUFFER_LENGTH);
		for (j = 0; j < I2C_MAX_BYTES && i < len; j++, i++) {
			buf[j] = data[2*i];
			buf[0x10 + j] = data[2*i+1];
			PDEBUG(D_CONF, "I2C: Writing 0x%02x to reg 0x%02x",
			data[2*i+1], data[2*i]);
		}
		buf[0x20] = sd->sensor->i2c_addr;
		buf[0x21] = j - 1; /* Number of commands to send - 1 */
		buf[0x22] = I2C_WRITE_CMD;
		err = usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
				      0x04, 0x40, 0x0400, 0, buf,
				      I2C_BUFFER_LENGTH,
				      STV06XX_URB_MSG_TIMEOUT);
		if (err < 0)
			return err;
	}
	return stv06xx_write_sensor_finish(sd);
}