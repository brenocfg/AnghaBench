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
struct i2c_device_id {scalar_t__ driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct adm1021_data {scalar_t__ type; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm1021_group ; 
 int /*<<< orphan*/  adm1021_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adm1021_data*) ; 
 int /*<<< orphan*/  kfree (struct adm1021_data*) ; 
 struct adm1021_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ lm84 ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  read_only ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adm1021_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct adm1021_data *data;
	int err;

	data = kzalloc(sizeof(struct adm1021_data), GFP_KERNEL);
	if (!data) {
		pr_debug("adm1021: detect failed, kzalloc failed!\n");
		err = -ENOMEM;
		goto error0;
	}

	i2c_set_clientdata(client, data);
	data->type = id->driver_data;
	mutex_init(&data->update_lock);

	/* Initialize the ADM1021 chip */
	if (data->type != lm84 && !read_only)
		adm1021_init_client(client);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &adm1021_group)))
		goto error1;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto error3;
	}

	return 0;

error3:
	sysfs_remove_group(&client->dev.kobj, &adm1021_group);
error1:
	kfree(data);
error0:
	return err;
}