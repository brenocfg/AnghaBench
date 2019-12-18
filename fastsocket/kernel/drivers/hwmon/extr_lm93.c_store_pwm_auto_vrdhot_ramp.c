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
typedef  int /*<<< orphan*/  u32 ;
struct lm93_data {int /*<<< orphan*/  update_lock; } ;
struct i2c_client {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int LM93_RAMP_TO_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LM93_REG_PWM_RAMP_CTL ; 
 struct lm93_data* i2c_get_clientdata (struct i2c_client*) ; 
 int lm93_read_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lm93_write_byte (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 struct i2c_client* to_i2c_client (struct device*) ; 

__attribute__((used)) static ssize_t store_pwm_auto_vrdhot_ramp(struct device *dev,
						struct device_attribute *attr,
						const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	struct lm93_data *data = i2c_get_clientdata(client);
	u32 val = simple_strtoul(buf, NULL, 10);
	u8 ramp;

	mutex_lock(&data->update_lock);
	ramp = lm93_read_byte(client, LM93_REG_PWM_RAMP_CTL);
	ramp = (ramp & 0xf0) | (LM93_RAMP_TO_REG(val) & 0x0f);
	lm93_write_byte(client, LM93_REG_PWM_RAMP_CTL, ramp);
	mutex_unlock(&data->update_lock);
	return 0;
}