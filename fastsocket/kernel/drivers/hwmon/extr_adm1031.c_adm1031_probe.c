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
struct adm1031_data {scalar_t__ chip_type; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/ * chan_select_table; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ adm1030 ; 
 scalar_t__ adm1031 ; 
 int /*<<< orphan*/  adm1031_group ; 
 int /*<<< orphan*/  adm1031_group_opt ; 
 int /*<<< orphan*/  adm1031_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  auto_channel_select_table_adm1030 ; 
 int /*<<< orphan*/  auto_channel_select_table_adm1031 ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adm1031_data*) ; 
 int /*<<< orphan*/  kfree (struct adm1031_data*) ; 
 struct adm1031_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adm1031_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct adm1031_data *data;
	int err;

	data = kzalloc(sizeof(struct adm1031_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	data->chip_type = id->driver_data;
	mutex_init(&data->update_lock);

	if (data->chip_type == adm1030)
		data->chan_select_table = &auto_channel_select_table_adm1030;
	else
		data->chan_select_table = &auto_channel_select_table_adm1031;

	/* Initialize the ADM1031 chip */
	adm1031_init_client(client);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &adm1031_group)))
		goto exit_free;

	if (data->chip_type == adm1031) {
		if ((err = sysfs_create_group(&client->dev.kobj,
						&adm1031_group_opt)))
			goto exit_remove;
	}

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	sysfs_remove_group(&client->dev.kobj, &adm1031_group);
	sysfs_remove_group(&client->dev.kobj, &adm1031_group_opt);
exit_free:
	kfree(data);
exit:
	return err;
}