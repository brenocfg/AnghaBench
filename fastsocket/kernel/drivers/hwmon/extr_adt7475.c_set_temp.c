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
typedef  long u8 ;
struct sensor_device_attribute_2 {int nr; size_t index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct adt7475_data {int config5; long** temp; int /*<<< orphan*/  lock; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
#define  AUTOMIN 133 
 int CONFIG5_TEMPOFFSET ; 
 size_t EINVAL ; 
#define  HYSTERSIS 132 
#define  MAX 131 
#define  MIN 130 
#define  OFFSET 129 
 unsigned char REG_CONFIG5 ; 
 unsigned char REG_REMOTE1_HYSTERSIS ; 
 unsigned char REG_REMOTE2_HYSTERSIS ; 
 long SENSORS_LIMIT (long,int,int) ; 
 unsigned char TEMP_MAX_REG (size_t) ; 
 unsigned char TEMP_MIN_REG (size_t) ; 
 unsigned char TEMP_OFFSET_REG (size_t) ; 
 unsigned char TEMP_THERM_REG (size_t) ; 
 unsigned char TEMP_TMIN_REG (size_t) ; 
#define  THERM 128 
 int adt7475_read (unsigned char) ; 
 int /*<<< orphan*/  adt7475_read_hystersis (struct i2c_client*) ; 
 struct adt7475_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,unsigned char,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int reg2temp (struct adt7475_data*,int) ; 
 scalar_t__ strict_strtol (char const*,int,long*) ; 
 long temp2reg (struct adt7475_data*,long) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t set_temp(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct sensor_device_attribute_2 *sattr = to_sensor_dev_attr_2(attr);
	struct i2c_client *client = to_i2c_client(dev);
	struct adt7475_data *data = i2c_get_clientdata(client);
	unsigned char reg = 0;
	u8 out;
	int temp;
	long val;

	if (strict_strtol(buf, 10, &val))
		return -EINVAL;

	mutex_lock(&data->lock);

	/* We need the config register in all cases for temp <-> reg conv. */
	data->config5 = adt7475_read(REG_CONFIG5);

	switch (sattr->nr) {
	case OFFSET:
		if (data->config5 & CONFIG5_TEMPOFFSET) {
			val = SENSORS_LIMIT(val, -63000, 127000);
			out = data->temp[OFFSET][sattr->index] = val / 1000;
		} else {
			val = SENSORS_LIMIT(val, -63000, 64000);
			out = data->temp[OFFSET][sattr->index] = val / 500;
		}
		break;

	case HYSTERSIS:
		/* The value will be given as an absolute value, turn it
		   into an offset based on THERM */

		/* Read fresh THERM and HYSTERSIS values from the chip */
		data->temp[THERM][sattr->index] =
			adt7475_read(TEMP_THERM_REG(sattr->index)) << 2;
		adt7475_read_hystersis(client);

		temp = reg2temp(data, data->temp[THERM][sattr->index]);
		val = SENSORS_LIMIT(val, temp - 15000, temp);
		val = (temp - val) / 1000;

		if (sattr->index != 1) {
			data->temp[HYSTERSIS][sattr->index] &= 0xF0;
			data->temp[HYSTERSIS][sattr->index] |= (val & 0xF) << 4;
		} else {
			data->temp[HYSTERSIS][sattr->index] &= 0x0F;
			data->temp[HYSTERSIS][sattr->index] |= (val & 0xF);
		}

		out = data->temp[HYSTERSIS][sattr->index];
		break;

	default:
		data->temp[sattr->nr][sattr->index] = temp2reg(data, val);

		/* We maintain an extra 2 digits of precision for simplicity
		 * - shift those back off before writing the value */
		out = (u8) (data->temp[sattr->nr][sattr->index] >> 2);
	}

	switch (sattr->nr) {
	case MIN:
		reg = TEMP_MIN_REG(sattr->index);
		break;
	case MAX:
		reg = TEMP_MAX_REG(sattr->index);
		break;
	case OFFSET:
		reg = TEMP_OFFSET_REG(sattr->index);
		break;
	case AUTOMIN:
		reg = TEMP_TMIN_REG(sattr->index);
		break;
	case THERM:
		reg = TEMP_THERM_REG(sattr->index);
		break;
	case HYSTERSIS:
		if (sattr->index != 2)
			reg = REG_REMOTE1_HYSTERSIS;
		else
			reg = REG_REMOTE2_HYSTERSIS;

		break;
	}

	i2c_smbus_write_byte_data(client, reg, out);

	mutex_unlock(&data->lock);
	return count;
}