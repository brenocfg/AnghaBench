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
struct w83791d_data {int beep_mask; int beep_enable; int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int BEEP_MASK_TO_REG (long) ; 
 int GLOBAL_BEEP_ENABLE_MASK ; 
 int GLOBAL_BEEP_ENABLE_SHIFT ; 
 int /*<<< orphan*/ * W83791D_REG_BEEP_CTRL ; 
 struct w83791d_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 int /*<<< orphan*/  w83791d_write (struct i2c_client*,int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static ssize_t store_beep_mask(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct w83791d_data *data = i2c_get_clientdata(client);
	long val = simple_strtol(buf, NULL, 10);
	int i;

	mutex_lock(&data->update_lock);

	/* The beep_enable state overrides any enabling request from
	   the masks */
	data->beep_mask = BEEP_MASK_TO_REG(val) & ~GLOBAL_BEEP_ENABLE_MASK;
	data->beep_mask |= (data->beep_enable << GLOBAL_BEEP_ENABLE_SHIFT);

	val = data->beep_mask;

	for (i = 0; i < 3; i++) {
		w83791d_write(client, W83791D_REG_BEEP_CTRL[i], (val & 0xff));
		val >>= 8;
	}

	mutex_unlock(&data->update_lock);

	return count;
}