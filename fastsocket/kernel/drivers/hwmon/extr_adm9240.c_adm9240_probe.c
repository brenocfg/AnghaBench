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
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct adm9240_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm9240_group ; 
 int /*<<< orphan*/  adm9240_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adm9240_data*) ; 
 int /*<<< orphan*/  kfree (struct adm9240_data*) ; 
 struct adm9240_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adm9240_probe(struct i2c_client *new_client,
			 const struct i2c_device_id *id)
{
	struct adm9240_data *data;
	int err;

	data = kzalloc(sizeof(*data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(new_client, data);
	mutex_init(&data->update_lock);

	adm9240_init_client(new_client);

	/* populate sysfs filesystem */
	if ((err = sysfs_create_group(&new_client->dev.kobj, &adm9240_group)))
		goto exit_free;

	data->hwmon_dev = hwmon_device_register(&new_client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	sysfs_remove_group(&new_client->dev.kobj, &adm9240_group);
exit_free:
	kfree(data);
exit:
	return err;
}