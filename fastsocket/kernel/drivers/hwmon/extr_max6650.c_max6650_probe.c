#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct max6650_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max6650_data*) ; 
 int /*<<< orphan*/  kfree (struct max6650_data*) ; 
 struct max6650_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max6650_attr_grp ; 
 int max6650_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max6650_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct max6650_data *data;
	int err;

	if (!(data = kzalloc(sizeof(struct max6650_data), GFP_KERNEL))) {
		dev_err(&client->dev, "out of memory.\n");
		return -ENOMEM;
	}

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/*
	 * Initialize the max6650 chip
	 */
	err = max6650_init_client(client);
	if (err)
		goto err_free;

	err = sysfs_create_group(&client->dev.kobj, &max6650_attr_grp);
	if (err)
		goto err_free;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (!IS_ERR(data->hwmon_dev))
		return 0;

	err = PTR_ERR(data->hwmon_dev);
	dev_err(&client->dev, "error registering hwmon device.\n");
	sysfs_remove_group(&client->dev.kobj, &max6650_attr_grp);
err_free:
	kfree(data);
	return err;
}