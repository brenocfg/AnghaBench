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
struct dvb_frontend {struct cx24123_state* demodulator_priv; } ;
struct cx24123_state {int dummy; } ;
typedef  int fe_sec_voltage_t ;

/* Variables and functions */
 int EINVAL ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int cx24123_writereg (struct cx24123_state*,int,int) ; 
 int /*<<< orphan*/  dprintk (char*) ; 

__attribute__((used)) static int cx24123_set_voltage(struct dvb_frontend *fe,
	fe_sec_voltage_t voltage)
{
	struct cx24123_state *state = fe->demodulator_priv;
	u8 val;

	val = cx24123_readreg(state, 0x29) & ~0x40;

	switch (voltage) {
	case SEC_VOLTAGE_13:
		dprintk("setting voltage 13V\n");
		return cx24123_writereg(state, 0x29, val & 0x7f);
	case SEC_VOLTAGE_18:
		dprintk("setting voltage 18V\n");
		return cx24123_writereg(state, 0x29, val | 0x80);
	case SEC_VOLTAGE_OFF:
		/* already handled in cx88-dvb */
		return 0;
	default:
		return -EINVAL;
	};

	return 0;
}