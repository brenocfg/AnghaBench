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
struct lm77_data {int temp_crit; int temp_hyst; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM77_REG_TEMP_CRIT ; 
 int /*<<< orphan*/  LM77_REG_TEMP_HYST ; 
 int /*<<< orphan*/  LM77_TEMP_TO_REG (int) ; 
 struct lm77_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  lm77_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_temp_crit(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm77_data *data = i2c_get_clientdata(client);
	long val = simple_strtoul(buf, NULL, 10);
	int oldcrithyst;
	
	mutex_lock(&data->update_lock);
	oldcrithyst = data->temp_crit - data->temp_hyst;
	data->temp_crit = val;
	data->temp_hyst = data->temp_crit - oldcrithyst;
	lm77_write_value(client, LM77_REG_TEMP_CRIT,
			 LM77_TEMP_TO_REG(data->temp_crit));
	lm77_write_value(client, LM77_REG_TEMP_HYST,
			 LM77_TEMP_TO_REG(data->temp_hyst));
	mutex_unlock(&data->update_lock);
	return count;
}