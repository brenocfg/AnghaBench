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
struct lm77_data {int /*<<< orphan*/  update_lock; scalar_t__ temp_hyst; scalar_t__ temp_crit; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM77_REG_TEMP_HYST ; 
 int /*<<< orphan*/  LM77_TEMP_TO_REG (scalar_t__) ; 
 struct lm77_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lm77_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_temp_crit_hyst(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm77_data *data = i2c_get_clientdata(client);
	unsigned long val = simple_strtoul(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->temp_hyst = data->temp_crit - val;
	lm77_write_value(client, LM77_REG_TEMP_HYST,
			 LM77_TEMP_TO_REG(data->temp_hyst));
	mutex_unlock(&data->update_lock);
	return count;
}