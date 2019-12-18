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
struct i2c_msg {int addr; int len; int flags; int /*<<< orphan*/  buf; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; } ;

/* Variables and functions */
 int EAGAIN ; 
 int I2C_M_RD ; 
 int REQUEST_I2C_READ ; 
 int REQUEST_I2C_WRITE ; 
 int /*<<< orphan*/  deb_info (char*,int) ; 
 int dib0700_ctrl_rd (struct dvb_usb_device*,int*,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dib0700_ctrl_wr (struct dvb_usb_device*,int*,int) ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dib0700_i2c_xfer_legacy(struct i2c_adapter *adap,
				   struct i2c_msg *msg, int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	int i,len;
	u8 buf[255];

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		/* fill in the address */
		buf[1] = msg[i].addr << 1;
		/* fill the buffer */
		memcpy(&buf[2], msg[i].buf, msg[i].len);

		/* write/read request */
		if (i+1 < num && (msg[i+1].flags & I2C_M_RD)) {
			buf[0] = REQUEST_I2C_READ;
			buf[1] |= 1;

			/* special thing in the current firmware: when length is zero the read-failed */
			if ((len = dib0700_ctrl_rd(d, buf, msg[i].len + 2, msg[i+1].buf, msg[i+1].len)) <= 0) {
				deb_info("I2C read failed on address 0x%02x\n",
					 msg[i].addr);
				break;
			}

			msg[i+1].len = len;

			i++;
		} else {
			buf[0] = REQUEST_I2C_WRITE;
			if (dib0700_ctrl_wr(d, buf, msg[i].len + 2) < 0)
				break;
		}
	}

	mutex_unlock(&d->i2c_mutex);
	return i;
}