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
struct v4l2_device {int dummy; } ;
struct ivtv {int /*<<< orphan*/  i2c_bus_lock; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 struct v4l2_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int ivtv_read (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ivtv_write (struct ivtv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ivtv* to_ivtv (struct v4l2_device*) ; 

__attribute__((used)) static int ivtv_xfer(struct i2c_adapter *i2c_adap, struct i2c_msg *msgs, int num)
{
	struct v4l2_device *v4l2_dev = i2c_get_adapdata(i2c_adap);
	struct ivtv *itv = to_ivtv(v4l2_dev);
	int retval;
	int i;

	mutex_lock(&itv->i2c_bus_lock);
	for (i = retval = 0; retval == 0 && i < num; i++) {
		if (msgs[i].flags & I2C_M_RD)
			retval = ivtv_read(itv, msgs[i].addr, msgs[i].buf, msgs[i].len);
		else {
			/* if followed by a read, don't stop */
			int stop = !(i + 1 < num && msgs[i + 1].flags == I2C_M_RD);

			retval = ivtv_write(itv, msgs[i].addr, msgs[i].buf, msgs[i].len, stop);
		}
	}
	mutex_unlock(&itv->i2c_bus_lock);
	return retval ? retval : num;
}