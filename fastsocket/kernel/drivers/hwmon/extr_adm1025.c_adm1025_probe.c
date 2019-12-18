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
typedef  int u8 ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct adm1025_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1025_REG_CONFIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm1025_group ; 
 int /*<<< orphan*/  adm1025_group_in4 ; 
 int /*<<< orphan*/  adm1025_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adm1025_data*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct adm1025_data*) ; 
 struct adm1025_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int adm1025_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct adm1025_data *data;
	int err;
	u8 config;

	data = kzalloc(sizeof(struct adm1025_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the ADM1025 chip */
	adm1025_init_client(client);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &adm1025_group)))
		goto exit_free;

	/* Pin 11 is either in4 (+12V) or VID4 */
	config = i2c_smbus_read_byte_data(client, ADM1025_REG_CONFIG);
	if (!(config & 0x20)) {
		if ((err = sysfs_create_group(&client->dev.kobj,
					      &adm1025_group_in4)))
			goto exit_remove;
	}

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove;
	}

	return 0;

exit_remove:
	sysfs_remove_group(&client->dev.kobj, &adm1025_group);
	sysfs_remove_group(&client->dev.kobj, &adm1025_group_in4);
exit_free:
	kfree(data);
exit:
	return err;
}