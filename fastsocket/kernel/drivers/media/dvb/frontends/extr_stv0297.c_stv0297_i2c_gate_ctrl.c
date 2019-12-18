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
struct stv0297_state {int dummy; } ;
struct dvb_frontend {struct stv0297_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0297_writereg (struct stv0297_state*,int,int) ; 

__attribute__((used)) static int stv0297_i2c_gate_ctrl(struct dvb_frontend *fe, int enable)
{
	struct stv0297_state *state = fe->demodulator_priv;

	if (enable) {
		stv0297_writereg(state, 0x87, 0x78);
		stv0297_writereg(state, 0x86, 0xc8);
	}

	return 0;
}