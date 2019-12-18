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
struct adm1026_data {int config1; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  vrm; int /*<<< orphan*/  update_lock; } ;

/* Variables and functions */
 int CFG1_AIN8_9 ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm1026_group ; 
 int /*<<< orphan*/  adm1026_group_in8_9 ; 
 int /*<<< orphan*/  adm1026_group_temp3 ; 
 int /*<<< orphan*/  adm1026_init_client (struct i2c_client*) ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct adm1026_data*) ; 
 int /*<<< orphan*/  kfree (struct adm1026_data*) ; 
 struct adm1026_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static int adm1026_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct adm1026_data *data;
	int err;

	data = kzalloc(sizeof(struct adm1026_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	/* Set the VRM version */
	data->vrm = vid_which_vrm();

	/* Initialize the ADM1026 chip */
	adm1026_init_client(client);

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &adm1026_group)))
		goto exitfree;
	if (data->config1 & CFG1_AIN8_9)
		err = sysfs_create_group(&client->dev.kobj,
					 &adm1026_group_in8_9);
	else
		err = sysfs_create_group(&client->dev.kobj,
					 &adm1026_group_temp3);
	if (err)
		goto exitremove;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto exitremove;
	}

	return 0;

	/* Error out and cleanup code */
exitremove:
	sysfs_remove_group(&client->dev.kobj, &adm1026_group);
	if (data->config1 & CFG1_AIN8_9)
		sysfs_remove_group(&client->dev.kobj, &adm1026_group_in8_9);
	else
		sysfs_remove_group(&client->dev.kobj, &adm1026_group_temp3);
exitfree:
	kfree(data);
exit:
	return err;
}