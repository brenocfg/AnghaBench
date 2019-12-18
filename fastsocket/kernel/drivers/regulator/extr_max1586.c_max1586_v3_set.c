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
struct regulator_dev {int dummy; } ;
struct max1586_data {unsigned int max_uV; unsigned int min_uV; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_V3_SELECT ; 
 int MAX1586_V3_MAX_VSEL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int) ; 
 int max1586_v3_calc_voltage (struct max1586_data*,unsigned int) ; 
 struct max1586_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max1586_v3_set(struct regulator_dev *rdev, int min_uV, int max_uV)
{
	struct max1586_data *max1586 = rdev_get_drvdata(rdev);
	struct i2c_client *client = max1586->client;
	unsigned range_uV = max1586->max_uV - max1586->min_uV;
	unsigned selector;
	u8 v3_prog;

	if (min_uV > max1586->max_uV || max_uV < max1586->min_uV)
		return -EINVAL;
	if (min_uV < max1586->min_uV)
		min_uV = max1586->min_uV;

	selector = ((min_uV - max1586->min_uV) * MAX1586_V3_MAX_VSEL +
			range_uV - 1) / range_uV;
	if (max1586_v3_calc_voltage(max1586, selector) > max_uV)
		return -EINVAL;

	dev_dbg(&client->dev, "changing voltage v3 to %dmv\n",
		max1586_v3_calc_voltage(max1586, selector) / 1000);

	v3_prog = I2C_V3_SELECT | (u8) selector;
	return i2c_smbus_write_byte(client, v3_prog);
}