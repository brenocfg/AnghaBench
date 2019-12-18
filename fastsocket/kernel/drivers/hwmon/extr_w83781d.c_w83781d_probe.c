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
struct w83781d_data {scalar_t__* lm75; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  type; struct i2c_client* client; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  lock; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct w83781d_data*) ; 
 int /*<<< orphan*/  i2c_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct w83781d_data*) ; 
 struct w83781d_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int w83781d_create_files (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int w83781d_detect_subclients (struct i2c_client*) ; 
 int /*<<< orphan*/  w83781d_group ; 
 int /*<<< orphan*/  w83781d_group_opt ; 
 int /*<<< orphan*/  w83781d_init_device (struct device*) ; 

__attribute__((used)) static int
w83781d_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct w83781d_data *data;
	int err;

	data = kzalloc(sizeof(struct w83781d_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto ERROR1;
	}

	i2c_set_clientdata(client, data);
	mutex_init(&data->lock);
	mutex_init(&data->update_lock);

	data->type = id->driver_data;
	data->client = client;

	/* attach secondary i2c lm75-like clients */
	err = w83781d_detect_subclients(client);
	if (err)
		goto ERROR3;

	/* Initialize the chip */
	w83781d_init_device(dev);

	/* Register sysfs hooks */
	err = w83781d_create_files(dev, data->type, 0);
	if (err)
		goto ERROR4;

	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto ERROR4;
	}

	return 0;

ERROR4:
	sysfs_remove_group(&dev->kobj, &w83781d_group);
	sysfs_remove_group(&dev->kobj, &w83781d_group_opt);

	if (data->lm75[0])
		i2c_unregister_device(data->lm75[0]);
	if (data->lm75[1])
		i2c_unregister_device(data->lm75[1]);
ERROR3:
	i2c_set_clientdata(client, NULL);
	kfree(data);
ERROR1:
	return err;
}