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
struct i2c_msg {scalar_t__ len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int af9005_i2c_read (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int af9005_i2c_write (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int af9005_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msg[],
			   int num)
{
	/* only implements what the mt2060 module does, don't know how
	   to make it really generic */
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	int ret;
	u8 reg, addr;
	u8 *value;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	if (num > 2)
		warn("more than 2 i2c messages at a time is not handled yet. TODO.");

	if (num == 2) {
		/* reads a single register */
		reg = *msg[0].buf;
		addr = msg[0].addr;
		value = msg[1].buf;
		ret = af9005_i2c_read(d, addr, reg, value, 1);
		if (ret == 0)
			ret = 2;
	} else {
		/* write one or more registers */
		reg = msg[0].buf[0];
		addr = msg[0].addr;
		value = &msg[0].buf[1];
		ret = af9005_i2c_write(d, addr, reg, value, msg[0].len - 1);
		if (ret == 0)
			ret = 1;
	}

	mutex_unlock(&d->i2c_mutex);
	return ret;
}