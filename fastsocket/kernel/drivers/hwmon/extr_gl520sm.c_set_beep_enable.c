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
typedef  int u8 ;
struct i2c_client {int dummy; } ;
struct gl520_data {int beep_enable; int /*<<< orphan*/  update_lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  GL520_REG_BEEP_ENABLE ; 
 int gl520_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl520_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct gl520_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_beep_enable(struct device *dev, struct device_attribute
			       *attr, const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct gl520_data *data = i2c_get_clientdata(client);
	u8 r = simple_strtoul(buf, NULL, 10)?0:1;

	mutex_lock(&data->update_lock);
	data->beep_enable = !r;
	gl520_write_value(client, GL520_REG_BEEP_ENABLE,
			  (gl520_read_value(client, GL520_REG_BEEP_ENABLE)
			   & ~0x04) | (r << 2));
	mutex_unlock(&data->update_lock);
	return count;
}