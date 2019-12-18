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
struct sensor_device_attribute_2 {int index; int nr; } ;
struct dme1737_data {int* pwm; int* pwm_acz; int* pwm_min; int /*<<< orphan*/ * pwm_rr; int /*<<< orphan*/ * pwm_config; int /*<<< orphan*/ * pwm_freq; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int PWM_ACZ_FROM_REG (int /*<<< orphan*/ ) ; 
 int PWM_EN_FROM_REG (int /*<<< orphan*/ ) ; 
 int PWM_FREQ_FROM_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PWM_OFF_FROM_REG (int /*<<< orphan*/ ,int) ; 
 int PWM_RR_FROM_REG (int /*<<< orphan*/ ,int) ; 
#define  SYS_PWM 135 
#define  SYS_PWM_AUTO_CHANNELS_ZONE 134 
#define  SYS_PWM_AUTO_POINT1_PWM 133 
#define  SYS_PWM_AUTO_POINT2_PWM 132 
#define  SYS_PWM_AUTO_PWM_MIN 131 
#define  SYS_PWM_ENABLE 130 
#define  SYS_PWM_FREQ 129 
#define  SYS_PWM_RAMP_RATE 128 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 struct dme1737_data* dme1737_update_device (struct device*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 struct sensor_device_attribute_2* to_sensor_dev_attr_2 (struct device_attribute*) ; 

__attribute__((used)) static ssize_t show_pwm(struct device *dev, struct device_attribute *attr,
			char *buf)
{
	struct dme1737_data *data = dme1737_update_device(dev);
	struct sensor_device_attribute_2
		*sensor_attr_2 = to_sensor_dev_attr_2(attr);
	int ix = sensor_attr_2->index;
	int fn = sensor_attr_2->nr;
	int res;

	switch (fn) {
	case SYS_PWM:
		if (PWM_EN_FROM_REG(data->pwm_config[ix]) == 0) {
			res = 255;
		} else {
			res = data->pwm[ix];
		}
		break;
	case SYS_PWM_FREQ:
		res = PWM_FREQ_FROM_REG(data->pwm_freq[ix]);
		break;
	case SYS_PWM_ENABLE:
		if (ix >= 3) {
			res = 1; /* pwm[5-6] hard-wired to manual mode */
		} else {
			res = PWM_EN_FROM_REG(data->pwm_config[ix]);
		}
		break;
	case SYS_PWM_RAMP_RATE:
		/* Only valid for pwm[1-3] */
		res = PWM_RR_FROM_REG(data->pwm_rr[ix > 0], ix);
		break;
	case SYS_PWM_AUTO_CHANNELS_ZONE:
		/* Only valid for pwm[1-3] */
		if (PWM_EN_FROM_REG(data->pwm_config[ix]) == 2) {
			res = PWM_ACZ_FROM_REG(data->pwm_config[ix]);
		} else {
			res = data->pwm_acz[ix];
		}
		break;
	case SYS_PWM_AUTO_PWM_MIN:
		/* Only valid for pwm[1-3] */
		if (PWM_OFF_FROM_REG(data->pwm_rr[0], ix)) {
			res = data->pwm_min[ix];
		} else {
			res = 0;
		}
		break;
	case SYS_PWM_AUTO_POINT1_PWM:
		/* Only valid for pwm[1-3] */
		res = data->pwm_min[ix];
		break;
	case SYS_PWM_AUTO_POINT2_PWM:
		/* Only valid for pwm[1-3] */
		res = 255; /* hard-wired */
		break;
	default:
		res = 0;
		dev_dbg(dev, "Unknown function %d.\n", fn);
	}

	return sprintf(buf, "%d\n", res);
}