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
struct adt7462_data {int* pwm_cfg; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ADT7462_PWM_CHANNEL_MASK ; 
 int ADT7462_PWM_CHANNEL_SHIFT ; 
 int /*<<< orphan*/  ADT7462_REG_PWM_CFG (int) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void set_pwm_channel(struct i2c_client *client,
			    struct adt7462_data *data,
			    int which,
			    int value)
{
	int temp = data->pwm_cfg[which] & ~ADT7462_PWM_CHANNEL_MASK;
	temp |= value << ADT7462_PWM_CHANNEL_SHIFT;

	mutex_lock(&data->lock);
	data->pwm_cfg[which] = temp;
	i2c_smbus_write_byte_data(client, ADT7462_REG_PWM_CFG(which), temp);
	mutex_unlock(&data->lock);
}