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
struct i2c_client {int dummy; } ;
struct ds1374 {int /*<<< orphan*/  mutex; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DS1374_REG_CR ; 
 int DS1374_REG_CR_AIE ; 
 int DS1374_REG_CR_WACE ; 
 int DS1374_REG_CR_WDALM ; 
 int ENOIOCTLCMD ; 
#define  RTC_AIE_OFF 129 
#define  RTC_AIE_ON 128 
 struct ds1374* i2c_get_clientdata (struct i2c_client*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static int ds1374_ioctl(struct device *dev, unsigned int cmd, unsigned long arg)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct ds1374 *ds1374 = i2c_get_clientdata(client);
	int ret = -ENOIOCTLCMD;

	mutex_lock(&ds1374->mutex);

	switch (cmd) {
	case RTC_AIE_OFF:
		ret = i2c_smbus_read_byte_data(client, DS1374_REG_CR);
		if (ret < 0)
			goto out;

		ret &= ~DS1374_REG_CR_WACE;

		ret = i2c_smbus_write_byte_data(client, DS1374_REG_CR, ret);
		if (ret < 0)
			goto out;

		break;

	case RTC_AIE_ON:
		ret = i2c_smbus_read_byte_data(client, DS1374_REG_CR);
		if (ret < 0)
			goto out;

		ret |= DS1374_REG_CR_WACE | DS1374_REG_CR_AIE;
		ret &= ~DS1374_REG_CR_WDALM;

		ret = i2c_smbus_write_byte_data(client, DS1374_REG_CR, ret);
		if (ret < 0)
			goto out;

		break;
	}

out:
	mutex_unlock(&ds1374->mutex);
	return ret;
}