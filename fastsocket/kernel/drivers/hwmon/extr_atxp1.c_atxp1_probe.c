#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct atxp1_data {int vrm; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; scalar_t__ valid; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atxp1_group ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct atxp1_data*) ; 
 int /*<<< orphan*/  kfree (struct atxp1_data*) ; 
 struct atxp1_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vid_which_vrm () ; 

__attribute__((used)) static int atxp1_probe(struct i2c_client *new_client,
		       const struct i2c_device_id *id)
{
	struct atxp1_data *data;
	int err;

	data = kzalloc(sizeof(struct atxp1_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	/* Get VRM */
	data->vrm = vid_which_vrm();

	i2c_set_clientdata(new_client, data);
	data->valid = 0;

	mutex_init(&data->update_lock);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&new_client->dev.kobj, &atxp1_group)))
		goto exit_free;

	data->hwmon_dev = hwmon_device_register(&new_client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exit_remove_files;
	}

	dev_info(&new_client->dev, "Using VRM: %d.%d\n",
			 data->vrm / 10, data->vrm % 10);

	return 0;

exit_remove_files:
	sysfs_remove_group(&new_client->dev.kobj, &atxp1_group);
exit_free:
	kfree(data);
exit:
	return err;
}