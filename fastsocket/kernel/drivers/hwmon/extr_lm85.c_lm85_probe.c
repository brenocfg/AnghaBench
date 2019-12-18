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
struct lm85_data {int type; int vid; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  vrm; int /*<<< orphan*/  freq_map; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM85_REG_VID ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
#define  adm1027 131 
 int /*<<< orphan*/  adm1027_freq_map ; 
#define  adt7463 130 
 int const adt7468 ; 
#define  emc6d100 129 
#define  emc6d102 128 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm85_data*) ; 
 int /*<<< orphan*/  kfree (struct lm85_data*) ; 
 struct lm85_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm85_freq_map ; 
 int /*<<< orphan*/  lm85_group ; 
 int /*<<< orphan*/  lm85_group_in4 ; 
 int /*<<< orphan*/  lm85_group_in567 ; 
 int /*<<< orphan*/  lm85_init_client (struct i2c_client*) ; 
 int lm85_read_value (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vid_which_vrm () ; 

__attribute__((used)) static int lm85_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct lm85_data *data;
	int err;

	data = kzalloc(sizeof(struct lm85_data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	i2c_set_clientdata(client, data);
	data->type = id->driver_data;
	mutex_init(&data->update_lock);

	/* Fill in the chip specific driver values */
	switch (data->type) {
	case adm1027:
	case adt7463:
	case emc6d100:
	case emc6d102:
		data->freq_map = adm1027_freq_map;
		break;
	default:
		data->freq_map = lm85_freq_map;
	}

	/* Set the VRM version */
	data->vrm = vid_which_vrm();

	/* Initialize the LM85 chip */
	lm85_init_client(client);

	/* Register sysfs hooks */
	err = sysfs_create_group(&client->dev.kobj, &lm85_group);
	if (err)
		goto err_kfree;

	/* The ADT7463/68 have an optional VRM 10 mode where pin 21 is used
	   as a sixth digital VID input rather than an analog input. */
	data->vid = lm85_read_value(client, LM85_REG_VID);
	if (!((data->type == adt7463 || data->type == adt7468) &&
	    (data->vid & 0x80)))
		if ((err = sysfs_create_group(&client->dev.kobj,
					&lm85_group_in4)))
			goto err_remove_files;

	/* The EMC6D100 has 3 additional voltage inputs */
	if (data->type == emc6d100)
		if ((err = sysfs_create_group(&client->dev.kobj,
					&lm85_group_in567)))
			goto err_remove_files;

	data->hwmon_dev = hwmon_device_register(&client->dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto err_remove_files;
	}

	return 0;

	/* Error out and cleanup code */
 err_remove_files:
	sysfs_remove_group(&client->dev.kobj, &lm85_group);
	sysfs_remove_group(&client->dev.kobj, &lm85_group_in4);
	if (data->type == emc6d100)
		sysfs_remove_group(&client->dev.kobj, &lm85_group_in567);
 err_kfree:
	kfree(data);
	return err;
}