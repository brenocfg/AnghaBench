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

/* Variables and functions */
 int ves1x93_writereg (struct ves1x93_state*,int,int) ; 

__attribute__((used)) static int ves1x93_i2c_gate_ctrl(struct dvb_frontend* fe, int enable)
{
	struct ves1x93_state* state = fe->demodulator_priv;

	if (enable) {
		return ves1x93_writereg(state, 0x00, 0x11);
	} else {
		return ves1x93_writereg(state, 0x00, 0x01);
	}
}