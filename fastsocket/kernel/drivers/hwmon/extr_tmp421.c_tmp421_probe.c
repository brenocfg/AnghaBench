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
struct tmp421_data {int /*<<< orphan*/ * hwmon_dev; int /*<<< orphan*/  channels; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tmp421_data*) ; 
 int /*<<< orphan*/  kfree (struct tmp421_data*) ; 
 struct tmp421_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp421_group ; 
 int tmp421_init_client (struct i2c_client*) ; 

__attribute__((used)) static int tmp421_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct tmp421_data *data;
	int err;

	data = kzalloc(sizeof(struct tmp421_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);
	data->channels = id->driver_data;

	err = tmp421_init_client(client);
	if (err)
		goto exit_free;

	err = sysfs_create_group(&client->dev.kobj, &tmp421_group);
	if (err)
		goto exit_free;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		data->hwmon_dev = NULL;
		goto exit_remove;
	}
	return 0;

exit_remove:
	sysfs_remove_group(&client->dev.kobj, &tmp421_group);

exit_free:
	i2c_set_clientdata(client, NULL);
	kfree(data);

	return err;
}