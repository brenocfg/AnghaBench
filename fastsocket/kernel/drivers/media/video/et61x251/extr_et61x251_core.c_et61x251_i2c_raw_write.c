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
typedef  int u8 ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int i2c_slave_id; int rsta; int /*<<< orphan*/  name; } ;
struct et61x251_device {int* control_buffer; TYPE_1__ sensor; struct usb_device* usbdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET61X251_CTRL_TIMEOUT ; 
 int /*<<< orphan*/  PDBGG (char*,int,int,int,int,int,int,int,int,int,int) ; 
 scalar_t__ et61x251_i2c_wait (struct et61x251_device*,TYPE_1__*) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

int
et61x251_i2c_raw_write(struct et61x251_device* cam, u8 n, u8 data1, u8 data2,
		       u8 data3, u8 data4, u8 data5, u8 data6, u8 data7,
		       u8 data8, u8 address)
{
	struct usb_device* udev = cam->usbdev;
	u8* data = cam->control_buffer;
	int err = 0, res;

	data[0] = data2;
	data[1] = data3;
	data[2] = data4;
	data[3] = data5;
	data[4] = data6;
	data[5] = data7;
	data[6] = data8;
	res = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x00, 0x41,
			      0, 0x81, data, n-1, ET61X251_CTRL_TIMEOUT);
	if (res < 0)
		err += res;

	data[0] = address;
	data[1] = cam->sensor.i2c_slave_id;
	data[2] = cam->sensor.rsta | 0x02 | (n << 4);
	res = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x00, 0x41,
			      0, 0x88, data, 3, ET61X251_CTRL_TIMEOUT);
	if (res < 0)
		err += res;

	/* Start writing through the serial interface */
	data[0] = data1;
	res = usb_control_msg(udev, usb_sndctrlpipe(udev, 0), 0x00, 0x41,
			      0, 0x80, data, 1, ET61X251_CTRL_TIMEOUT);
	if (res < 0)
		err += res;

	err += et61x251_i2c_wait(cam, &cam->sensor);

	if (err)
		DBG(3, "I2C raw write failed for %s image sensor",
		    cam->sensor.name);

	PDBGG("I2C raw write: %u bytes, address = 0x%02X, data1 = 0x%02X, "
	      "data2 = 0x%02X, data3 = 0x%02X, data4 = 0x%02X, data5 = 0x%02X,"
	      " data6 = 0x%02X, data7 = 0x%02X, data8 = 0x%02X", n, address,
	      data1, data2, data3, data4, data5, data6, data7, data8);

	return err ? -1 : 0;

}