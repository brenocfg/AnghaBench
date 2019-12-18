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
struct ves1x93_state {int dummy; } ;
struct dvb_frontend {struct ves1x93_state* demodulator_priv; } ;
typedef  int fe_sec_voltage_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int ves1x93_writereg (struct ves1x93_state*,int,int) ; 

__attribute__((used)) static int ves1x93_set_voltage (struct dvb_frontend* fe, fe_sec_voltage_t voltage)
{
	struct ves1x93_state* state = fe->demodulator_priv;

	switch (voltage) {
	case SEC_VOLTAGE_13:
		return ves1x93_writereg (state, 0x1f, 0x20);
	case SEC_VOLTAGE_18:
		return ves1x93_writereg (state, 0x1f, 0x30);
	case SEC_VOLTAGE_OFF:
		return ves1x93_writereg (state, 0x1f, 0x00);
	default:
		return -EINVAL;
	}
}