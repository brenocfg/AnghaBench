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
struct gl518_data {scalar_t__ type; int alarm_mask; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GL518_REG_REVISION ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gl518_group ; 
 int /*<<< orphan*/  gl518_group_r80 ; 
 int /*<<< orphan*/  gl518_init_client (struct i2c_client*) ; 
 int gl518_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 scalar_t__ gl518sm_r00 ; 
 scalar_t__ gl518sm_r80 ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct gl518_data*) ; 
 int /*<<< orphan*/  kfree (struct gl518_data*) ; 
 struct gl518_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gl518_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct gl518_data *data;
	int err, revision;

	data = kzalloc(sizeof(struct gl518_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	revision = gl518_read_value(client, GL518_REG_REVISION);
	data->type = revision == 0x80 ? gl518sm_r80 : gl518sm_r00;
	mutex_init(&data->update_lock);

	/* Initialize the GL518SM chip */
	data->alarm_mask = 0xff;
	gl518_init_client(client);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &gl518_group)))
		goto exit_free;
	if (data->type == gl518sm_r80)
		if ((err = sysfs_create_group(&client->dev.kobj,
					      &gl518_group_r80)))
			goto exit_remove_files;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	return 0;

exit_remove_files:
	sysfs_remove_group(&client->dev.kobj, &gl518_group);
	if (data->type == gl518sm_r80)
		sysfs_remove_group(&client->dev.kobj, &gl518_group_r80);
exit_free:
	kfree(data);
exit:
	return err;
}