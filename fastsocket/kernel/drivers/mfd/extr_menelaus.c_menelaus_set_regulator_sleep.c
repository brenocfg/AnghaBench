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
typedef  int u32 ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  MENELAUS_GPIO_CTRL ; 
 int /*<<< orphan*/  MENELAUS_SLEEP_CTRL2 ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int menelaus_read_reg (int /*<<< orphan*/ ) ; 
 int menelaus_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_menelaus ; 

int menelaus_set_regulator_sleep(int enable, u32 val)
{
	int t, ret;
	struct i2c_client *c = the_menelaus->client;

	mutex_lock(&the_menelaus->lock);
	ret = menelaus_write_reg(MENELAUS_SLEEP_CTRL2, val);
	if (ret < 0)
		goto out;

	dev_dbg(&c->dev, "regulator sleep configuration: %02x\n", val);

	ret = menelaus_read_reg(MENELAUS_GPIO_CTRL);
	if (ret < 0)
		goto out;
	t = ((1 << 6) | 0x04);
	if (enable)
		ret |= t;
	else
		ret &= ~t;
	ret = menelaus_write_reg(MENELAUS_GPIO_CTRL, ret);
out:
	mutex_unlock(&the_menelaus->lock);
	return ret;
}