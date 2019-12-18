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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct g760a_data {int valid; int /*<<< orphan*/  update_lock; scalar_t__ last_updated; void* fan_sta; void* act_cnt; void* set_cnt; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G760A_REG_ACT_CNT ; 
 int /*<<< orphan*/  G760A_REG_FAN_STA ; 
 int /*<<< orphan*/  G760A_REG_SET_CNT ; 
 scalar_t__ G760A_UPDATE_INTERVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 void* g760a_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct g760a_data* i2c_get_clientdata (struct i2c_client*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static struct g760a_data *g760a_update_client(struct device *dev)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct g760a_data *data = i2c_get_clientdata(client);

	mutex_lock(&data->update_lock);

	if (time_after(jiffies, data->last_updated + G760A_UPDATE_INTERVAL)
	    || !data->valid) {
		dev_dbg(&client->dev, "Starting g760a update\n");

		data->set_cnt = g760a_read_value(client, G760A_REG_SET_CNT);
		data->act_cnt = g760a_read_value(client, G760A_REG_ACT_CNT);
		data->fan_sta = g760a_read_value(client, G760A_REG_FAN_STA);

		data->last_updated = jiffies;
		data->valid = 1;
	}

	mutex_unlock(&data->update_lock);

	return data;
}