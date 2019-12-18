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
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adm1026_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * in_max; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/ * ADM1026_REG_IN_MAX ; 
 int /*<<< orphan*/  INS_TO_REG (int,scalar_t__) ; 
 scalar_t__ NEG12_OFFSET ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adm1026_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_in16_max(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1026_data *data = i2c_get_clientdata(client);
	int val = simple_strtol(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	data->in_max[16] = INS_TO_REG(16, val+NEG12_OFFSET);
	adm1026_write_value(client, ADM1026_REG_IN_MAX[16], data->in_max[16]);
	mutex_unlock(&data->update_lock);
	return count;
}