#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct w83791d_data {int* fan_min; int /*<<< orphan*/ ** lm75; int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int NUMBER_OF_FANIN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  W83791D_REG_DID_VID4 ; 
 int /*<<< orphan*/ * W83791D_REG_FAN_MIN ; 
 int /*<<< orphan*/  W83791D_REG_GPIO ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int) ; 
 int /*<<< orphan*/  hwmon_device_register (struct device*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct w83791d_data*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct w83791d_data*) ; 
 struct w83791d_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int w83791d_detect_subclients (struct i2c_client*) ; 
 int /*<<< orphan*/  w83791d_group ; 
 int /*<<< orphan*/  w83791d_group_fanpwm45 ; 
 int /*<<< orphan*/  w83791d_init_client (struct i2c_client*) ; 
 int w83791d_read (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int w83791d_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct w83791d_data *data;
	struct device *dev = &client->dev;
	int i, err;
	u8 has_fanpwm45;

#ifdef DEBUG
	int val1;
	val1 = w83791d_read(client, W83791D_REG_DID_VID4);
	dev_dbg(dev, "Device ID version: %d.%d (0x%02x)\n",
			(val1 >> 5) & 0x07, (val1 >> 1) & 0x0f, val1);
#endif

	data = kzalloc(sizeof(struct w83791d_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto error0;
	}

	i2c_set_clientdata(client, data);
	mutex_init(&data->update_lock);

	err = w83791d_detect_subclients(client);
	if (err)
		goto error1;

	/* Initialize the chip */
	w83791d_init_client(client);

	/* If the fan_div is changed, make sure there is a rational
	   fan_min in place */
	for (i = 0; i < NUMBER_OF_FANIN; i++) {
		data->fan_min[i] = w83791d_read(client, W83791D_REG_FAN_MIN[i]);
	}

	/* Register sysfs hooks */
	if ((err = sysfs_create_group(&client->dev.kobj, &w83791d_group)))
		goto error3;

	/* Check if pins of fan/pwm 4-5 are in use as GPIO */
	has_fanpwm45 = w83791d_read(client, W83791D_REG_GPIO) & 0x10;
	if (has_fanpwm45) {
		err = sysfs_create_group(&client->dev.kobj,
					 &w83791d_group_fanpwm45);
		if (err)
			goto error4;
	}

	/* Everything is ready, now register the working device */
	data->hwmon_dev = hwmon_device_register(dev);
	if (IS_ERR(data->hwmon_dev)) {
		err = PTR_ERR(data->hwmon_dev);
		goto error5;
	}

	return 0;

error5:
	if (has_fanpwm45)
		sysfs_remove_group(&client->dev.kobj, &w83791d_group_fanpwm45);
error4:
	sysfs_remove_group(&client->dev.kobj, &w83791d_group);
error3:
	if (data->lm75[0] != NULL)
		i2c_unregister_device(data->lm75[0]);
	if (data->lm75[1] != NULL)
		i2c_unregister_device(data->lm75[1]);
error1:
	kfree(data);
error0:
	return err;
}