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
struct lm63_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * temp8; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  HYST_TO_REG (long) ; 
 int /*<<< orphan*/  LM63_REG_REMOTE_TCRIT_HYST ; 
 long TEMP8_FROM_REG (int /*<<< orphan*/ ) ; 
 struct lm63_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_temp2_crit_hyst(struct device *dev, struct device_attribute *dummy,
				   const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm63_data *data = i2c_get_clientdata(client);
	long val = simple_strtol(buf, NULL, 10);
	long hyst;

	mutex_lock(&data->update_lock);
	hyst = TEMP8_FROM_REG(data->temp8[2]) - val;
	i2c_smbus_write_byte_data(client, LM63_REG_REMOTE_TCRIT_HYST,
				  HYST_TO_REG(hyst));
	mutex_unlock(&data->update_lock);
	return count;
}