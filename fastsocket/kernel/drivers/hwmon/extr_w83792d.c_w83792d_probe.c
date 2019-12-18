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
struct w83792d_data {int /*<<< orphan*/ ** lm75; int /*<<< orphan*/  hwmon_dev; void** fan_min; int /*<<< orphan*/  update_lock; scalar_t__ valid; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * W83792D_REG_FAN_MIN ; 
 int /*<<< orphan*/  W83792D_REG_GPIO_EN ; 
 int /*<<< orphan*/  W83792D_REG_PIN ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct w83792d_data*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct w83792d_data*) ; 
 struct w83792d_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int w83792d_detect_subclients (struct i2c_client*) ; 
 int /*<<< orphan*/  w83792d_group ; 
 int /*<<< orphan*/ * w83792d_group_fan ; 
 int /*<<< orphan*/  w83792d_init_client (struct i2c_client*) ; 
 void* w83792d_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
w83792d_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct w83792d_data *data;
	struct device *dev = &client->dev;
	int i, val1, err;

	data = kzalloc(sizeof(struct w83792d_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto ERROR0;
	}

	i2c_set_clientdata(client, data);
	data->valid = 0;
	mutex_init(&data->update_lock);

	err = w83792d_detect_subclients(client);
	if (err)
		goto ERROR1;

	/* Initialize the chip */
	w83792d_init_client(client);

	/* A few vars need to be filled upon startup */
	for (i = 0; i < 7; i++) {
		data->fan_min[i] = w83792d_read_value(client,
					W83792D_REG_FAN_MIN[i]);
	}

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&dev->kobj, &w83792d_group)))
		goto ERROR3;

	/* Read GPIO enable register to check if pins for fan 4,5 are used as
	   GPIO */
	val1 = w83792d_read_value(client, W83792D_REG_GPIO_EN);

	if (!(val1 & 0x40))
		if ((err = sysfs_create_group(&dev->kobj,
					      &w83792d_group_fan[0])))
			goto exit_remove_files;

	if (!(val1 & 0x20))
		if ((err = sysfs_create_group(&dev->kobj,
					      &w83792d_group_fan[1])))
			goto exit_remove_files;

	val1 = w83792d_read_value(client, W83792D_REG_PIN);
	if (val1 & 0x40)
		if ((err = sysfs_create_group(&dev->kobj,
					      &w83792d_group_fan[2])))
			goto exit_remove_files;

	if (val1 & 0x04)
		if ((err = sysfs_create_group(&dev->kobj,
					      &w83792d_group_fan[3])))
			goto exit_remove_files;

	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	return 0;

exit_remove_files:
	sysfs_remove_group(&dev->kobj, &w83792d_group);
	for (i = 0; i < ARRAY_SIZE(w83792d_group_fan); i++)
		sysfs_remove_group(&dev->kobj, &w83792d_group_fan[i]);
ERROR3:
	if (data->lm75[0] != NULL)
		i2c_unregister_device(data->lm75[0]);
	if (data->lm75[1] != NULL)
		i2c_unregister_device(data->lm75[1]);
ERROR1:
	kfree(data);
ERROR0:
	return err;
}