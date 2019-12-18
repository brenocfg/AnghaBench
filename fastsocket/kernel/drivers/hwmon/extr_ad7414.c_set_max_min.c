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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ad7414_data {long* temps; int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/ * AD7414_REG_LIMIT ; 
 long SENSORS_LIMIT (long,int,int) ; 
 int /*<<< orphan*/  ad7414_write (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 struct ad7414_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 TYPE_1__* to_sensor_dev_attr (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_max_min(struct device *dev,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ad7414_data *data = i2c_get_clientdata(client);
	int index = to_sensor_dev_attr(attr)->index;
	u8 reg = AD7414_REG_LIMIT[index];
	long temp = simple_strtol(buf, NULL, 10);

	temp = SENSORS_LIMIT(temp, -40000, 85000);
	temp = (temp + (temp < 0 ? -500 : 500)) / 1000;

	mutex_lock(&data->lock);
	data->temps[index] = temp;
	ad7414_write(client, reg, temp);
	mutex_unlock(&data->lock);
	return count;
}