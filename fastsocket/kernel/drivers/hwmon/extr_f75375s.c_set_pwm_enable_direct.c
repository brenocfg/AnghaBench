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
struct i2c_client {int dummy; } ;
struct f75375_data {int* pwm; int* pwm_enable; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  F75375_REG_FAN_PWM_DUTY (int) ; 
 int /*<<< orphan*/  F75375_REG_FAN_TIMER ; 
 int FAN_CTRL_MODE (int) ; 
 int f75375_read8 (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f75375_write8 (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct f75375_data* i2c_get_clientdata (struct i2c_client*) ; 

__attribute__((used)) static int set_pwm_enable_direct(struct i2c_client *client, int nr, int val)
{
	struct f75375_data *data = i2c_get_clientdata(client);
	u8 fanmode;

	if (val < 0 || val > 4)
		return -EINVAL;

	fanmode = f75375_read8(client, F75375_REG_FAN_TIMER);
	fanmode = ~(3 << FAN_CTRL_MODE(nr));

	switch (val) {
	case 0: /* Full speed */
		fanmode  |= (3 << FAN_CTRL_MODE(nr));
		data->pwm[nr] = 255;
		f75375_write8(client, F75375_REG_FAN_PWM_DUTY(nr),
				data->pwm[nr]);
		break;
	case 1: /* PWM */
		fanmode  |= (3 << FAN_CTRL_MODE(nr));
		break;
	case 2: /* AUTOMATIC*/
		fanmode  |= (2 << FAN_CTRL_MODE(nr));
		break;
	case 3: /* fan speed */
		break;
	}
	f75375_write8(client, F75375_REG_FAN_TIMER, fanmode);
	data->pwm_enable[nr] = val;
	return 0;
}