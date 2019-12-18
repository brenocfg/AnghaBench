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
struct smsc47m192_data {int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  vrm; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMSC47M192_REG_CONFIG ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct smsc47m192_data*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct smsc47m192_data*) ; 
 struct smsc47m192_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smsc47m192_group ; 
 int /*<<< orphan*/  smsc47m192_group_in4 ; 
 int /*<<< orphan*/  smsc47m192_init_client (struct i2c_client*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static int smsc47m192_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct smsc47m192_data *data;
	int config;
	int err;

	data = kzalloc(sizeof(struct smsc47m192_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	data->vrm = vid_which_vrm();
	mutex_init(&data->update_lock);

	/* Initialize the SMSC47M192 chip */
	smsc47m192_init_client(client);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &smsc47m192_group)))
		goto exit_free;

	/* Pin 110 is either in4 (+12V) or VID4 */
	config = i2c_smbus_read_byte_data(client, SMSC47M192_REG_CONFIG);
	if (!(config & 0x20)) {
		if ((err = sysfs_create_group(&client->dev.kobj,
					      &smsc47m192_group_in4)))
			goto exit_remove_files;
	}

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	return 0;

exit_remove_files:
	sysfs_remove_group(&client->dev.kobj, &smsc47m192_group);
	sysfs_remove_group(&client->dev.kobj, &smsc47m192_group_in4);
exit_free:
	kfree(data);
exit:
	return err;
}