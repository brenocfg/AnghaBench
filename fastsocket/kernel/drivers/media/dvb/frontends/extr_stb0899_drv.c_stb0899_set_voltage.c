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
struct stb0899_state {int dummy; } ;
struct dvb_frontend {struct stb0899_state* demodulator_priv; } ;
typedef  int fe_sec_voltage_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  STB0899_GPIO00CFG ; 
 int /*<<< orphan*/  STB0899_GPIO01CFG ; 
 int /*<<< orphan*/  STB0899_GPIO02CFG ; 
 int /*<<< orphan*/  stb0899_write_reg (struct stb0899_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stb0899_set_voltage(struct dvb_frontend *fe, fe_sec_voltage_t voltage)
{
	struct stb0899_state *state = fe->demodulator_priv;

	switch (voltage) {
	case SEC_VOLTAGE_13:
		stb0899_write_reg(state, STB0899_GPIO00CFG, 0x82);
		stb0899_write_reg(state, STB0899_GPIO01CFG, 0x02);
		stb0899_write_reg(state, STB0899_GPIO02CFG, 0x00);
		break;
	case SEC_VOLTAGE_18:
		stb0899_write_reg(state, STB0899_GPIO00CFG, 0x02);
		stb0899_write_reg(state, STB0899_GPIO01CFG, 0x02);
		stb0899_write_reg(state, STB0899_GPIO02CFG, 0x82);
		break;
	case SEC_VOLTAGE_OFF:
		stb0899_write_reg(state, STB0899_GPIO00CFG, 0x82);
		stb0899_write_reg(state, STB0899_GPIO01CFG, 0x82);
		stb0899_write_reg(state, STB0899_GPIO02CFG, 0x82);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}