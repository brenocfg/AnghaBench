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
struct thmc50_data {scalar_t__ has_temp3; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  type; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct thmc50_data*) ; 
 int /*<<< orphan*/  kfree (struct thmc50_data*) ; 
 struct thmc50_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  temp3_group ; 
 int /*<<< orphan*/  thmc50_group ; 
 int /*<<< orphan*/  thmc50_init_client (struct i2c_client*) ; 

__attribute__((used)) static int thmc50_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct thmc50_data *data;
	int err;

	data = kzalloc(sizeof(struct thmc50_data), GFP_KERNEL);
	if (!data) {
		pr_debug("thmc50: detect failed, kzalloc failed!\n");
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	data->type = id->driver_data;
	mutex_init(&data->update_lock);

	thmc50_init_client(client);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &thmc50_group)))
		goto exit_free;

	/* Register ADM1022 sysfs hooks */
	if (data->has_temp3)
		if ((err = sysfs_create_group(&client->dev.kobj,
					      &temp3_group)))
			goto exit_remove_sysfs_thmc50;

	/* Register a new directory entry with module sensors */
	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_sysfs;
	}

	return 0;

exit_remove_sysfs:
	if (data->has_temp3)
		sysfs_remove_group(&client->dev.kobj, &temp3_group);
exit_remove_sysfs_thmc50:
	sysfs_remove_group(&client->dev.kobj, &thmc50_group);
exit_free:
	kfree(data);
exit:
	return err;
}