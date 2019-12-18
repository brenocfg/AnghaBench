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
struct TYPE_2__ {int vcore_hw_mode; int /*<<< orphan*/  lock; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MENELAUS_VCORE_CTRL1 ; 
 int /*<<< orphan*/  MENELAUS_VCORE_CTRL3 ; 
 int /*<<< orphan*/  MENELAUS_VCORE_CTRL4 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,unsigned int,unsigned int) ; 
 int menelaus_get_vtg_value (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int menelaus_read_reg (int /*<<< orphan*/ ) ; 
 int menelaus_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_menelaus ; 
 int /*<<< orphan*/  vcore_values ; 

int menelaus_set_vcore_hw(unsigned int roof_mV, unsigned int floor_mV)
{
	int fval, rval, val, ret;
	struct i2c_client *c = the_menelaus->client;

	rval = menelaus_get_vtg_value(roof_mV, vcore_values,
				      ARRAY_SIZE(vcore_values));
	if (rval < 0)
		return -EINVAL;
	fval = menelaus_get_vtg_value(floor_mV, vcore_values,
				      ARRAY_SIZE(vcore_values));
	if (fval < 0)
		return -EINVAL;

	dev_dbg(&c->dev, "Setting VCORE FLOOR to %d mV and ROOF to %d mV\n",
	       floor_mV, roof_mV);

	mutex_lock(&the_menelaus->lock);
	ret = menelaus_write_reg(MENELAUS_VCORE_CTRL3, fval);
	if (ret < 0)
		goto out;
	ret = menelaus_write_reg(MENELAUS_VCORE_CTRL4, rval);
	if (ret < 0)
		goto out;
	if (!the_menelaus->vcore_hw_mode) {
		val = menelaus_read_reg(MENELAUS_VCORE_CTRL1);
		/* HW mode, turn OFF byte comparator */
		val |= ((1 << 7) | (1 << 5));
		ret = menelaus_write_reg(MENELAUS_VCORE_CTRL1, val);
		the_menelaus->vcore_hw_mode = 1;
	}
	msleep(1);
out:
	mutex_unlock(&the_menelaus->lock);
	return ret;
}