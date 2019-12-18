#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int enable; int pwm; int /*<<< orphan*/  auto_pwm_min; } ;
struct adm1026_data {int config1; int /*<<< orphan*/  update_lock; TYPE_1__ pwm1; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADM1026_REG_CONFIG1 ; 
 int /*<<< orphan*/  ADM1026_REG_PWM ; 
 int CFG1_PWM_AFC ; 
 int PWM_MIN_TO_REG (int /*<<< orphan*/ ) ; 
 int PWM_TO_REG (int) ; 
 int /*<<< orphan*/  adm1026_write_value (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct adm1026_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int simple_strtol (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t set_pwm_enable(struct device *dev, struct device_attribute *attr, const char *buf,
		size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct adm1026_data *data = i2c_get_clientdata(client);
	int val = simple_strtol(buf, NULL, 10);
	int old_enable;

	if ((val >= 0) && (val < 3)) {
		mutex_lock(&data->update_lock);
		old_enable = data->pwm1.enable;
		data->pwm1.enable = val;
		data->config1 = (data->config1 & ~CFG1_PWM_AFC)
				| ((val == 2) ? CFG1_PWM_AFC : 0);
		adm1026_write_value(client, ADM1026_REG_CONFIG1,
			data->config1);
		if (val == 2) { /* apply pwm1_auto_pwm_min to pwm1 */
			data->pwm1.pwm = PWM_TO_REG((data->pwm1.pwm & 0x0f) |
				PWM_MIN_TO_REG(data->pwm1.auto_pwm_min));
			adm1026_write_value(client, ADM1026_REG_PWM,
				data->pwm1.pwm);
		} else if (!((old_enable == 1) && (val == 1))) {
			/* set pwm to safe value */
			data->pwm1.pwm = 255;
			adm1026_write_value(client, ADM1026_REG_PWM,
				data->pwm1.pwm);
		}
		mutex_unlock(&data->update_lock);
	}
	return count;
}