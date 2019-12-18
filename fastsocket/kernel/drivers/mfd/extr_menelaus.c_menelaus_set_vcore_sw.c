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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ vcore_hw_mode; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MENELAUS_VCORE_CTRL1 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int menelaus_get_vtg_value (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int menelaus_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_menelaus ; 
 int /*<<< orphan*/  vcore_values ; 

int menelaus_set_vcore_sw(unsigned int mV)
{
	int val, ret;
	struct i2c_client *c = the_menelaus->client;

	val = menelaus_get_vtg_value(mV, vcore_values,
				     ARRAY_SIZE(vcore_values));
	if (val < 0)
		return -EINVAL;

	dev_dbg(&c->dev, "Setting VCORE to %d mV (val 0x%02x)\n", mV, val);

	/* Set SW mode and the voltage in one go. */
	mutex_lock(&the_menelaus->lock);
	ret = menelaus_write_reg(MENELAUS_VCORE_CTRL1, val);
	if (ret == 0)
		the_menelaus->vcore_hw_mode = 0;
	mutex_unlock(&the_menelaus->lock);
	msleep(1);

	return ret;
}