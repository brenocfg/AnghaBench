#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lm93_data {void (* update ) (struct lm93_data*,struct i2c_client*) ;int /*<<< orphan*/  hwmon_dev; int /*<<< orphan*/  update_lock; scalar_t__ valid; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int LM93_SMBUS_FUNC_FULL ; 
 int LM93_SMBUS_FUNC_MIN ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  disable_block ; 
 int /*<<< orphan*/  hwmon_device_register (TYPE_1__*) ; 
 int i2c_get_functionality (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lm93_data*) ; 
 int /*<<< orphan*/  kfree (struct lm93_data*) ; 
 struct lm93_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm93_attr_grp ; 
 int /*<<< orphan*/  lm93_init_client (struct i2c_client*) ; 
 void lm93_update_client_full (struct lm93_data*,struct i2c_client*) ; 
 void lm93_update_client_min (struct lm93_data*,struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lm93_probe(struct i2c_client *client,
		      const struct i2c_device_id *id)
{
	struct lm93_data *data;
	int err, func;
	void (*update)(struct lm93_data *, struct i2c_client *);

	/* choose update routine based on bus capabilities */
	func = i2c_get_functionality(client->adapter);
	if (((LM93_SMBUS_FUNC_FULL & func) == LM93_SMBUS_FUNC_FULL) &&
			(!disable_block)) {
		dev_dbg(&client->dev, "using SMBus block data transactions\n");
		update = lm93_update_client_full;
	} else if ((LM93_SMBUS_FUNC_MIN & func) == LM93_SMBUS_FUNC_MIN) {
		dev_dbg(&client->dev, "disabled SMBus block data "
			"transactions\n");
		update = lm93_update_client_min;
	} else {
		dev_dbg(&client->dev, "detect failed, "
			"smbus byte and/or word data not supported!\n");
		err = -ENODEV;
		goto err_out;
	}

	data = kzalloc(sizeof(struct lm93_data), GFP_KERNEL);
	if (!data) {
		dev_dbg(&client->dev, "out of memory!\n");
		err = -ENOMEM;
		goto err_out;
	}
	i2c_set_clientdata(client, data);

	/* housekeeping */
	data->valid = 0;
	data->update = update;
	mutex_init(&data->update_lock);

	/* initialize the chip */
	lm93_init_client(client);

	err = sysfs_create_group(&client->dev.kobj, &lm93_attr_grp);
	if (err)
		goto err_free;

	/* Register hwmon driver class */
	data->hwmon_dev = hwmon_device_register(&client->dev);
	if ( !IS_ERR(data->hwmon_dev))
		return 0;

	err = PTR_ERR(data->hwmon_dev);
	dev_err(&client->dev, "error registering hwmon device.\n");
	sysfs_remove_group(&client->dev.kobj, &lm93_attr_grp);
err_free:
	kfree(data);
err_out:
	return err;
}