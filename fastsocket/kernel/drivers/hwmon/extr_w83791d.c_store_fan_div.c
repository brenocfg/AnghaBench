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
struct w83791d_data {int* fan_min; int* fan_div; int /*<<< orphan*/  update_lock; } ;
struct sensor_device_attribute {int index; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_FROM_REG (int) ; 
 size_t EINVAL ; 
 unsigned long FAN_FROM_REG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * W83791D_REG_FAN_DIV ; 
 int /*<<< orphan*/ * W83791D_REG_FAN_MIN ; 
 int /*<<< orphan*/  W83791D_REG_VBAT ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int div_to_reg (int,int /*<<< orphan*/ ) ; 
 int fan_to_reg (unsigned long,int /*<<< orphan*/ ) ; 
 struct w83791d_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 
 struct sensor_device_attribute* to_sensor_dev_attr (struct device_attribute*) ; 
 int w83791d_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w83791d_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t store_fan_div(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t count)
{
	struct sensor_device_attribute *sensor_attr = to_sensor_dev_attr(attr);
	struct i2c_client *client = to_i2c_client(dev);
	struct w83791d_data *data = i2c_get_clientdata(client);
	int nr = sensor_attr->index;
	unsigned long min;
	u8 tmp_fan_div;
	u8 fan_div_reg;
	u8 vbat_reg;
	int indx = 0;
	u8 keep_mask = 0;
	u8 new_shift = 0;

	/* Save fan_min */
	min = FAN_FROM_REG(data->fan_min[nr], DIV_FROM_REG(data->fan_div[nr]));

	mutex_lock(&data->update_lock);
	data->fan_div[nr] = div_to_reg(nr, simple_strtoul(buf, NULL, 10));

	switch (nr) {
	case 0:
		indx = 0;
		keep_mask = 0xcf;
		new_shift = 4;
		break;
	case 1:
		indx = 0;
		keep_mask = 0x3f;
		new_shift = 6;
		break;
	case 2:
		indx = 1;
		keep_mask = 0x3f;
		new_shift = 6;
		break;
	case 3:
		indx = 2;
		keep_mask = 0xf8;
		new_shift = 0;
		break;
	case 4:
		indx = 2;
		keep_mask = 0x8f;
		new_shift = 4;
		break;
#ifdef DEBUG
	default:
		dev_warn(dev, "store_fan_div: Unexpected nr seen: %d\n", nr);
		count = -EINVAL;
		goto err_exit;
#endif
	}

	fan_div_reg = w83791d_read(client, W83791D_REG_FAN_DIV[indx])
			& keep_mask;
	tmp_fan_div = (data->fan_div[nr] << new_shift) & ~keep_mask;

	w83791d_write(client, W83791D_REG_FAN_DIV[indx],
				fan_div_reg | tmp_fan_div);

	/* Bit 2 of fans 0-2 is stored in the vbat register (bits 5-7) */
	if (nr < 3) {
		keep_mask = ~(1 << (nr + 5));
		vbat_reg = w83791d_read(client, W83791D_REG_VBAT)
				& keep_mask;
		tmp_fan_div = (data->fan_div[nr] << (3 + nr)) & ~keep_mask;
		w83791d_write(client, W83791D_REG_VBAT,
				vbat_reg | tmp_fan_div);
	}

	/* Restore fan_min */
	data->fan_min[nr] = fan_to_reg(min, DIV_FROM_REG(data->fan_div[nr]));
	w83791d_write(client, W83791D_REG_FAN_MIN[nr], data->fan_min[nr]);

#ifdef DEBUG
err_exit:
#endif
	mutex_unlock(&data->update_lock);

	return count;
}