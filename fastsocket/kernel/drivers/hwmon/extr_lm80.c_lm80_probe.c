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
struct lm80_data {int /*<<< orphan*/  hwmon_dev; void** fan_min; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM80_REG_FAN_MIN (int) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm80_data*) ; 
 int /*<<< orphan*/  kfree (struct lm80_data*) ; 
 struct lm80_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm80_group ; 
 int /*<<< orphan*/  lm80_init_client (struct i2c_client*) ; 
 void* lm80_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm80_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct lm80_data *data;
	int err;

	data = kzalloc(sizeof(struct lm80_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Initialize the LM80 chip */
	lm80_init_client(client);

	/* A few vars need to be filled upon startup */
	data->fan_min[0] = lm80_read_value(client, LM80_REG_FAN_MIN(1));
	data->fan_min[1] = lm80_read_value(client, LM80_REG_FAN_MIN(2));

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &lm80_group)))
		goto error_free;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto error_remove;
	}

	return 0;

error_remove:
	sysfs_remove_group(&client->dev.kobj, &lm80_group);
error_free:
	kfree(data);
exit:
	return err;
}