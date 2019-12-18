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
typedef  int /*<<< orphan*/  u32 ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct TYPE_2__ {int* offset; } ;
struct lm93_data {int sfc2; int /*<<< orphan*/  update_lock; TYPE_1__ block10; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  LM93_REG_SFC2 ; 
 int /*<<< orphan*/  LM93_REG_TEMP_OFFSET (int) ; 
 int LM93_TEMP_AUTO_OFFSET_TO_REG (int,int /*<<< orphan*/ ,int,int) ; 
 struct lm93_data* i2c_get_clientdata (struct i2c_client*) ; 
 int lm93_read_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm93_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t store_temp_auto_offset(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *s_attr = to_sensor_dev_attr_2(attr);
	int nr = s_attr->index;
	int ofs = s_attr->nr;
	struct i2c_client *client = to_i2c_client(dev);
	struct lm93_data *data = i2c_get_clientdata(client);
	u32 val = simple_strtoul(buf, NULL, 10);

	mutex_lock(&data->update_lock);
	/* force 0.5C/bit mode */
	data->sfc2 = lm93_read_byte(client, LM93_REG_SFC2);
	data->sfc2 |= ((nr < 2) ? 0x10 : 0x20);
	lm93_write_byte(client, LM93_REG_SFC2, data->sfc2);
	data->block10.offset[ofs] = LM93_TEMP_AUTO_OFFSET_TO_REG(
			data->block10.offset[ofs], val, nr, 1);
	lm93_write_byte(client, LM93_REG_TEMP_OFFSET(ofs),
			data->block10.offset[ofs]);
	mutex_unlock(&data->update_lock);
	return count;
}