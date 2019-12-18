#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct lm90_data {scalar_t__ kind; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; int /*<<< orphan*/  parent; } ;
struct i2c_client {int flags; TYPE_2__ dev; } ;
struct i2c_adapter {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev_attr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_CLIENT_PEC ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ adm1032 ; 
 int /*<<< orphan*/  dev_attr_pec ; 
 int device_create_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm90_data*) ; 
 int /*<<< orphan*/  kfree (struct lm90_data*) ; 
 struct lm90_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm90_group ; 
 int /*<<< orphan*/  lm90_init_client (struct i2c_client*) ; 
 scalar_t__ max6646 ; 
 scalar_t__ max6657 ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_1__ sensor_dev_attr_temp2_offset ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm90_probe(struct i2c_client *new_client,
		      const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = to_i2c_adapter(new_client->dev.parent);
	struct lm90_data *data;
	int err;

	data = kzalloc(sizeof(struct lm90_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}
	i2c_set_clientdata(new_client, data);
	mutex_init(&data->update_lock);

	/* Set the device type */
	data->kind = id->driver_data;
	if (data->kind == adm1032) {
		if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE))
			new_client->flags &= ~I2C_CLIENT_PEC;
	}

	/* Initialize the LM90 chip */
	lm90_init_client(new_client);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&new_client->dev.kobj, &lm90_group)))
		goto exit_free;
	if (new_client->flags & I2C_CLIENT_PEC) {
		if ((err = device_create_file(&new_client->dev,
					      &dev_attr_pec)))
			goto exit_remove_files;
	}
	if (data->kind != max6657 && data->kind != max6646) {
		if ((err = device_create_file(&new_client->dev,
				&sensor_dev_attr_temp2_offset.dev_attr)))
			goto exit_remove_files;
	}

	data->hwmon_dev = hwmon_device_register(&new_client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	return 0;

exit_remove_files:
	sysfs_remove_group(&new_client->dev.kobj, &lm90_group);
	device_remove_file(&new_client->dev, &dev_attr_pec);
exit_free:
	kfree(data);
exit:
	return err;
}