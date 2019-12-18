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
struct adm1031_data {int conf1; scalar_t__* pwm; int /*<<< orphan*/ * auto_temp; int /*<<< orphan*/ * temp; int /*<<< orphan*/  chip_type; } ;

/* Variables and functions */
 int ADM1031_CONF1_AUTO_MODE ; 
 int /*<<< orphan*/  AUTO_TEMP_MIN_FROM_REG_DEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adm1031 ; 

__attribute__((used)) static int trust_fan_readings(struct adm1031_data *data, int chan)
{
	int res = 0;

	if (data->conf1 & ADM1031_CONF1_AUTO_MODE) {
		switch (data->conf1 & 0x60) {
		case 0x00:	/* remote temp1 controls fan1 remote temp2 controls fan2 */
			res = data->temp[chan+1] >=
			      AUTO_TEMP_MIN_FROM_REG_DEG(data->auto_temp[chan+1]);
			break;
		case 0x20:	/* remote temp1 controls both fans */
			res =
			    data->temp[1] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->auto_temp[1]);
			break;
		case 0x40:	/* remote temp2 controls both fans */
			res =
			    data->temp[2] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->auto_temp[2]);
			break;
		case 0x60:	/* max controls both fans */
			res =
			    data->temp[0] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->auto_temp[0])
			    || data->temp[1] >=
			    AUTO_TEMP_MIN_FROM_REG_DEG(data->auto_temp[1])
			    || (data->chip_type == adm1031
				&& data->temp[2] >=
				AUTO_TEMP_MIN_FROM_REG_DEG(data->auto_temp[2]));
			break;
		}
	} else {
		res = data->pwm[chan] > 0;
	}
	return res;
}