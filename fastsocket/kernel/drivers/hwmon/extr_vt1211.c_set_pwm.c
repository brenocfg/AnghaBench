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
struct vt1211_data {int* fan_div; int fan_ctl; int* pwm_ctl; int pwm_clk; int /*<<< orphan*/  update_lock; int /*<<< orphan*/  uch_config; } ;
struct sensor_device_attribute_2 {int index; int nr; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  ISTEMP (long,int /*<<< orphan*/ ) ; 
 int SENSORS_LIMIT (long,int,int) ; 
#define  SHOW_SET_PWM_AUTO_CHANNELS_TEMP 130 
#define  SHOW_SET_PWM_ENABLE 129 
#define  SHOW_SET_PWM_FREQ 128 
 int /*<<< orphan*/  VT1211_REG_FAN_DIV ; 
 int /*<<< orphan*/  VT1211_REG_PWM_CLK ; 
 int /*<<< orphan*/  VT1211_REG_PWM_CTL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct vt1211_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,long) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 long simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 
 int vt1211_read8 (struct vt1211_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vt1211_write8 (struct vt1211_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t set_pwm(struct device *dev, struct device_attribute *attr,
		       const char *buf, size_t count)
{
	struct vt1211_data *data = dev_get_drvdata(dev);
	struct sensor_device_attribute_2 *sensor_attr_2 =
						to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	long val = simple_strtol(buf, NULL, 10);
	int tmp, reg;

	mutex_lock(&data->update_lock);

	switch (fn) {
	case SHOW_SET_PWM_ENABLE:
		/* sync the data cache */
		reg = vt1211_read8(data, VT1211_REG_FAN_DIV);
		data->fan_div[0] = (reg >> 4) & 3;
		data->fan_div[1] = (reg >> 6) & 3;
		data->fan_ctl = reg & 0xf;
		reg = vt1211_read8(data, VT1211_REG_PWM_CTL);
		data->pwm_ctl[0] = reg & 0xf;
		data->pwm_ctl[1] = (reg >> 4) & 0xf;
		switch (val) {
		case 0:
			data->pwm_ctl[ix] &= 7;
			/* disable SmartGuardian if both PWM outputs are
			 * disabled */
			if ((data->pwm_ctl[ix ^ 1] & 1) == 0) {
				data->fan_ctl &= 0xe;
			}
			break;
		case 2:
			data->pwm_ctl[ix] |= 8;
			data->fan_ctl |= 1;
			break;
		default:
			count = -EINVAL;
			dev_warn(dev, "pwm mode %ld not supported. "
				 "Choose one of 0 or 2.\n", val);
			goto EXIT;
		}
		vt1211_write8(data, VT1211_REG_PWM_CTL,
			      ((data->pwm_ctl[1] << 4) |
				data->pwm_ctl[0]));
		vt1211_write8(data, VT1211_REG_FAN_DIV,
			      ((data->fan_div[1] << 6) |
			       (data->fan_div[0] << 4) |
				data->fan_ctl));
		break;
	case SHOW_SET_PWM_FREQ:
		val = 135000 / SENSORS_LIMIT(val, 135000 >> 7, 135000);
		/* calculate tmp = log2(val) */
		tmp = 0;
		for (val >>= 1; val > 0; val >>= 1) {
			tmp++;
		}
		/* sync the data cache */
		reg = vt1211_read8(data, VT1211_REG_PWM_CLK);
		data->pwm_clk = (reg & 0xf8) | tmp;
		vt1211_write8(data, VT1211_REG_PWM_CLK, data->pwm_clk);
		break;
	case SHOW_SET_PWM_AUTO_CHANNELS_TEMP:
		if ((val < 1) || (val > 7)) {
			count = -EINVAL;
			dev_warn(dev, "temp channel %ld not supported. "
				 "Choose a value between 1 and 7.\n", val);
			goto EXIT;
		}
		if (!ISTEMP(val - 1, data->uch_config)) {
			count = -EINVAL;
			dev_warn(dev, "temp channel %ld is not available.\n",
				 val);
			goto EXIT;
		}
		/* sync the data cache */
		reg = vt1211_read8(data, VT1211_REG_PWM_CTL);
		data->pwm_ctl[0] = reg & 0xf;
		data->pwm_ctl[1] = (reg >> 4) & 0xf;
		data->pwm_ctl[ix] = (data->pwm_ctl[ix] & 8) | (val - 1);
		vt1211_write8(data, VT1211_REG_PWM_CTL,
			      ((data->pwm_ctl[1] << 4) | data->pwm_ctl[0]));
		break;
	default:
		dev_dbg(dev, "Unknown attr fetch (%d)\n", fn);
	}

EXIT:
	mutex_unlock(&data->update_lock);
	return count;
}