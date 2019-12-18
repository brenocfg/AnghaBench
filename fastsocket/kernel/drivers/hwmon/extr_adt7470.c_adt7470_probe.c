#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_3__ dev; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  attrs; } ;
struct adt7470_data {int num_temp_sensors; TYPE_1__ attrs; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  auto_update; int /*<<< orphan*/  auto_update_stop; int /*<<< orphan*/  lock; int /*<<< orphan*/  auto_update_interval; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTO_UPDATE_INTERVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adt7470_attr ; 
 int /*<<< orphan*/  adt7470_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  adt7470_update_thread ; 
 int /*<<< orphan*/  dev_info (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_3__*) ; 
 int /*<<< orphan*/  hwmon_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adt7470_data*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct adt7470_data*) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct adt7470_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int adt7470_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct adt7470_data *data;
	int err;

	data = kzalloc(sizeof(struct adt7470_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	data->num_temp_sensors = -1;
	data->auto_update_interval = AUTO_UPDATE_INTERVAL;

	i2c_set_clientdata(client, data);
	mutex_init(&data->lock);

	dev_info(&client->dev, "%s chip found\n", client->name);

	/* Initialize the ADT7470 chip */
	adt7470_init_client(client);

	/* Register sysfs hooks */
	data->attrs.attrs = adt7470_attr;
	if ((err = sysfs_create_group(&client->dev.kobj, &data->attrs)))
		goto exit_free;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	init_completion(&data->auto_update_stop);
	data->auto_update = kthread_run(adt7470_update_thread, client,
					dev_name(data->hwmon_dev));
	if (IS_ERR(data->auto_update))
		goto exit_unregister;

	return 0;

exit_unregister:
	hwmon_device_unregister(data->hwmon_dev);
exit_remove:
	sysfs_remove_group(&client->dev.kobj, &data->attrs);
exit_free:
	kfree(data);
exit:
	return err;
}