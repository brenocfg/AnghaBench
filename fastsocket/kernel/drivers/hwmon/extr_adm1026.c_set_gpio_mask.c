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
struct adm1026_data {int gpio_mask; int alarm_mask; int /*<<< orphan*/  update_lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1026_REG_GPIO_MASK_0_7 ; 
 int /*<<< orphan*/  ADM1026_REG_GPIO_MASK_8_15 ; 
 int /*<<< orphan*/  ADM1026_REG_MASK1 ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,int /*<<< orphan*/ ,long) ; 
 struct adm1026_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_gpio_mask(struct device *dev, struct device_attribute *attr, const char *buf,
		size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1026_data *data = i2c_get_clientdata(client);
	int val = simple_strtol(buf, NULL, 10);
	long mask;

	mutex_lock(&data->update_lock);
	data->gpio_mask = val & 0x1ffff;
	mask = data->gpio_mask;
	adm1026_write_value(client, ADM1026_REG_GPIO_MASK_0_7, mask & 0xff);
	mask >>= 8;
	adm1026_write_value(client, ADM1026_REG_GPIO_MASK_8_15, mask & 0xff);
	mask = ((mask >> 1) & 0x80) | (data->alarm_mask >> 24 & 0x7f);
	adm1026_write_value(client, ADM1026_REG_MASK1, mask & 0xff);
	mutex_unlock(&data->update_lock);
	return count;
}