#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tps_pmic {struct regulator_dev** rdev; struct i2c_client* client; TYPE_1__* desc; struct tps_info const** info; int /*<<< orphan*/  io_lock; } ;
struct tps_info {int /*<<< orphan*/  name; } ;
struct regulator_init_data {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct i2c_device_id {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct TYPE_5__ {struct regulator_init_data* platform_data; } ;
struct i2c_client {TYPE_2__ dev; int /*<<< orphan*/  adapter; } ;
struct TYPE_4__ {int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int TPS6507X_DCDC_3 ; 
 int TPS6507X_NUM_REGULATOR ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tps_pmic*) ; 
 int /*<<< orphan*/  kfree (struct tps_pmic*) ; 
 struct tps_pmic* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * num_voltages ; 
 struct regulator_dev* regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_init_data*,struct tps_pmic*) ; 
 int /*<<< orphan*/  regulator_unregister (struct regulator_dev*) ; 
 int /*<<< orphan*/  tps6507x_dcdc_ops ; 
 int /*<<< orphan*/  tps6507x_ldo_ops ; 

__attribute__((used)) static
int tps_6507x_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
	static int desc_id;
	const struct tps_info *info = (void *)id->driver_data;
	struct regulator_init_data *init_data;
	struct regulator_dev *rdev;
	struct tps_pmic *tps;
	int i;

	if (!i2c_check_functionality(client->adapter,
				I2C_FUNC_SMBUS_BYTE_DATA))
		return -EIO;

	/**
	 * init_data points to array of regulator_init structures
	 * coming from the board-evm file.
	 */
	init_data = client->dev.platform_data;

	if (!init_data)
		return -EIO;

	tps = kzalloc(sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	mutex_init(&tps->io_lock);

	/* common for all regulators */
	tps->client = client;

	for (i = 0; i < TPS6507X_NUM_REGULATOR; i++, info++, init_data++) {
		/* Register the regulators */
		tps->info[i] = info;
		tps->desc[i].name = info->name;
		tps->desc[i].id = desc_id++;
		tps->desc[i].n_voltages = num_voltages[i];
		tps->desc[i].ops = (i > TPS6507X_DCDC_3 ?
				&tps6507x_ldo_ops : &tps6507x_dcdc_ops);
		tps->desc[i].type = REGULATOR_VOLTAGE;
		tps->desc[i].owner = THIS_MODULE;

		rdev = regulator_register(&tps->desc[i],
					&client->dev, init_data, tps);
		if (IS_ERR(rdev)) {
			dev_err(&client->dev, "failed to register %s\n",
				id->name);

			/* Unregister */
			while (i)
				regulator_unregister(tps->rdev[--i]);

			tps->client = NULL;

			/* clear the client data in i2c */
			i2c_set_clientdata(client, NULL);

			kfree(tps);
			return PTR_ERR(rdev);
		}

		/* Save regulator for cleanup */
		tps->rdev[i] = rdev;
	}

	i2c_set_clientdata(client, tps);

	return 0;
}