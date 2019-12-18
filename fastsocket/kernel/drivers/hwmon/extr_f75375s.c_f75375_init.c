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
struct f75375s_platform_data {int /*<<< orphan*/ * pwm; int /*<<< orphan*/ * pwm_enable; } ;
struct f75375_data {int /*<<< orphan*/ * pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  F75375_REG_FAN_PWM_DUTY (int) ; 
 int /*<<< orphan*/  SENSORS_LIMIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f75375_write8 (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_pwm_enable_direct (struct i2c_client*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f75375_init(struct i2c_client *client, struct f75375_data *data,
		struct f75375s_platform_data *f75375s_pdata)
{
	int nr;
	set_pwm_enable_direct(client, 0, f75375s_pdata->pwm_enable[0]);
	set_pwm_enable_direct(client, 1, f75375s_pdata->pwm_enable[1]);
	for (nr = 0; nr < 2; nr++) {
		data->pwm[nr] = SENSORS_LIMIT(f75375s_pdata->pwm[nr], 0, 255);
		f75375_write8(client, F75375_REG_FAN_PWM_DUTY(nr),
			data->pwm[nr]);
	}

}