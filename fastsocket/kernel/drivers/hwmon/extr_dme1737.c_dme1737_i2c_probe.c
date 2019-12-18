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
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  name; struct device dev; } ;
struct dme1737_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  name; struct i2c_client* client; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int dme1737_create_files (struct device*) ; 
 int dme1737_init_device (struct device*) ; 
 int /*<<< orphan*/  dme1737_remove_files (struct device*) ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct dme1737_data*) ; 
 int /*<<< orphan*/  kfree (struct dme1737_data*) ; 
 struct dme1737_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dme1737_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct dme1737_data *data;
	struct device *dev = &client->dev;
	int err;

	data = kzalloc(sizeof(struct dme1737_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	data->type = id->driver_data;
	data->client = client;
	data->name = client->name;
	mutex_init(&data->update_lock);

	/* Initialize the DME1737 chip */
	if ((err = dme1737_init_device(dev))) {
		dev_err(dev, "Failed to initialize device.\n");
		goto exit_kfree;
	}

	/* Create sysfs files */
	if ((err = dme1737_create_files(dev))) {
		dev_err(dev, "Failed to create sysfs files.\n");
		goto exit_kfree;
	}

	/* Register device */
	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		dev_err(dev, "Failed to register device.\n");
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	dme1737_remove_files(dev);
exit_kfree:
	kfree(data);
exit:
	return err;
}