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
struct i2c_msg {int addr; int flags; int len; int /*<<< orphan*/ * buf; } ;
struct i2c_adapter {struct cx231xx_i2c* algo_data; } ;
struct cx231xx_i2c {int nr; struct cx231xx* dev; } ;
struct cx231xx {int /*<<< orphan*/  i2c_lock; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 int cx231xx_i2c_check_for_device (struct i2c_adapter*,struct i2c_msg*) ; 
 int cx231xx_i2c_recv_bytes (struct i2c_adapter*,struct i2c_msg*) ; 
 int cx231xx_i2c_recv_bytes_with_saddr (struct i2c_adapter*,struct i2c_msg*,struct i2c_msg*) ; 
 int cx231xx_i2c_send_bytes (struct i2c_adapter*,struct i2c_msg*) ; 
 int /*<<< orphan*/  dprintk2 (int,char*,...) ; 
 int i2c_debug ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int cx231xx_i2c_xfer(struct i2c_adapter *i2c_adap,
			    struct i2c_msg msgs[], int num)
{
	struct cx231xx_i2c *bus = i2c_adap->algo_data;
	struct cx231xx *dev = bus->dev;
	int addr, rc, i, byte;

	if (num <= 0)
		return 0;
	mutex_lock(&dev->i2c_lock);
	for (i = 0; i < num; i++) {

		addr = msgs[i].addr >> 1;

		dprintk2(2, "%s %s addr=%x len=%d:",
			 (msgs[i].flags & I2C_M_RD) ? "read" : "write",
			 i == num - 1 ? "stop" : "nonstop", addr, msgs[i].len);
		if (!msgs[i].len) {
			/* no len: check only for device presence */
			rc = cx231xx_i2c_check_for_device(i2c_adap, &msgs[i]);
			if (rc < 0) {
				dprintk2(2, " no device\n");
				mutex_unlock(&dev->i2c_lock);
				return rc;
			}

		} else if (msgs[i].flags & I2C_M_RD) {
			/* read bytes */
			rc = cx231xx_i2c_recv_bytes(i2c_adap, &msgs[i]);
			if (i2c_debug >= 2) {
				for (byte = 0; byte < msgs[i].len; byte++)
					printk(" %02x", msgs[i].buf[byte]);
			}
		} else if (i + 1 < num && (msgs[i + 1].flags & I2C_M_RD) &&
			   msgs[i].addr == msgs[i + 1].addr
			   && (msgs[i].len <= 2) && (bus->nr < 3)) {
			/* read bytes */
			rc = cx231xx_i2c_recv_bytes_with_saddr(i2c_adap,
							       &msgs[i],
							       &msgs[i + 1]);
			if (i2c_debug >= 2) {
				for (byte = 0; byte < msgs[i].len; byte++)
					printk(" %02x", msgs[i].buf[byte]);
			}
			i++;
		} else {
			/* write bytes */
			if (i2c_debug >= 2) {
				for (byte = 0; byte < msgs[i].len; byte++)
					printk(" %02x", msgs[i].buf[byte]);
			}
			rc = cx231xx_i2c_send_bytes(i2c_adap, &msgs[i]);
		}
		if (rc < 0)
			goto err;
		if (i2c_debug >= 2)
			printk("\n");
	}
	mutex_unlock(&dev->i2c_lock);
	return num;
err:
	dprintk2(2, " ERROR: %i\n", rc);
	mutex_unlock(&dev->i2c_lock);
	return rc;
}