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
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_V6_SELECT ; 
 int MAX1586_V6_MAX_UV ; 
 int MAX1586_V6_MIN_UV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int) ; 
 int max1586_v6_calc_voltage (unsigned int) ; 
 struct i2c_client* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max1586_v6_set(struct regulator_dev *rdev, int min_uV, int max_uV)
{
	struct i2c_client *client = rdev_get_drvdata(rdev);
	unsigned selector;
	u8 v6_prog;

	if (min_uV < MAX1586_V6_MIN_UV || min_uV > MAX1586_V6_MAX_UV)
		return -EINVAL;
	if (max_uV < MAX1586_V6_MIN_UV || max_uV > MAX1586_V6_MAX_UV)
		return -EINVAL;

	if (min_uV >= 3000000)
		selector = 3;
	if (min_uV < 3000000)
		selector = 2;
	if (min_uV < 2500000)
		selector = 1;
	if (min_uV < 1800000)
		selector = 0;

	if (max1586_v6_calc_voltage(selector) > max_uV)
		return -EINVAL;

	dev_dbg(&client->dev, "changing voltage v6 to %dmv\n",
		max1586_v6_calc_voltage(selector) / 1000);

	v6_prog = I2C_V6_SELECT | (u8) selector;
	return i2c_smbus_write_byte(client, v6_prog);
}