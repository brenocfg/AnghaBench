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
struct pca9532_data {int /*<<< orphan*/  update_lock; int /*<<< orphan*/ * psc; int /*<<< orphan*/ * pwm; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCA9532_REG_PSC (int) ; 
 int /*<<< orphan*/  PCA9532_REG_PWM (int) ; 
 struct pca9532_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pca9532_setpwm(struct i2c_client *client, int pwm)
{
	struct pca9532_data *data = i2c_get_clientdata(client);
	mutex_lock(&data->update_lock);
	i2c_smbus_write_byte_data(client, PCA9532_REG_PWM(pwm),
		data->pwm[pwm]);
	i2c_smbus_write_byte_data(client, PCA9532_REG_PSC(pwm),
		data->psc[pwm]);
	mutex_unlock(&data->update_lock);
	return 0;
}