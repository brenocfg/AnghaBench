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
struct ngene_channel {int /*<<< orphan*/  number; struct ngene* dev; } ;
struct ngene {int /*<<< orphan*/  i2c_switch_mutex; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  down (int /*<<< orphan*/ *) ; 
 scalar_t__ i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  ngene_command_i2c_read (struct ngene*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngene_command_i2c_write (struct ngene*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngene_i2c_set_bus (struct ngene*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ngene_i2c_master_xfer(struct i2c_adapter *adapter,
				 struct i2c_msg msg[], int num)
{
	struct ngene_channel *chan =
		(struct ngene_channel *)i2c_get_adapdata(adapter);
	struct ngene *dev = chan->dev;

	down(&dev->i2c_switch_mutex);
	ngene_i2c_set_bus(dev, chan->number);

	if (num == 2 && msg[1].flags & I2C_M_RD && !(msg[0].flags & I2C_M_RD))
		if (!ngene_command_i2c_read(dev, msg[0].addr,
					    msg[0].buf, msg[0].len,
					    msg[1].buf, msg[1].len, 0))
			goto done;

	if (num == 1 && !(msg[0].flags & I2C_M_RD))
		if (!ngene_command_i2c_write(dev, msg[0].addr,
					     msg[0].buf, msg[0].len))
			goto done;
	if (num == 1 && (msg[0].flags & I2C_M_RD))
		if (!ngene_command_i2c_read(dev, msg[0].addr, NULL, 0,
					    msg[0].buf, msg[0].len, 0))
			goto done;

	up(&dev->i2c_switch_mutex);
	return -EIO;

done:
	up(&dev->i2c_switch_mutex);
	return num;
}