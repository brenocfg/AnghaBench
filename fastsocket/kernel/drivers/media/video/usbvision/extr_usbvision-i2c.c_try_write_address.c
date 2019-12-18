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
struct usb_usbvision {int dummy; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_I2C ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int usbvision_i2c_write (struct usb_usbvision*,unsigned char,char*,int) ; 

__attribute__((used)) static inline int try_write_address(struct i2c_adapter *i2c_adap,
				    unsigned char addr, int retries)
{
	struct usb_usbvision *usbvision;
	int i, ret = -1;
	char buf[4];

	usbvision = (struct usb_usbvision *)i2c_get_adapdata(i2c_adap);
	buf[0] = 0x00;
	for (i = 0; i <= retries; i++) {
		ret = (usbvision_i2c_write(usbvision, addr, buf, 1));
		if (ret == 1)
			break;	/* success! */
		udelay(5);
		if (i == retries)	/* no success */
			break;
		udelay(10);
	}
	if (i) {
		PDEBUG(DBG_I2C, "Needed %d retries for address %#2x", i, addr);
		PDEBUG(DBG_I2C, "Maybe there's no device at this address");
	}
	return ret;
}