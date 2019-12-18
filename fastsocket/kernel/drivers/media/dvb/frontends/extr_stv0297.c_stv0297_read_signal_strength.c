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
typedef  int u16 ;
struct stv0297_state {int dummy; } ;
struct dvb_frontend {struct stv0297_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  stv0297_readregs (struct stv0297_state*,int,int*,int) ; 

__attribute__((used)) static int stv0297_read_signal_strength(struct dvb_frontend *fe, u16 * strength)
{
	struct stv0297_state *state = fe->demodulator_priv;
	u8 STRENGTH[3];
	u16 tmp;

	stv0297_readregs(state, 0x41, STRENGTH, 3);
	tmp = (STRENGTH[1] & 0x03) << 8 | STRENGTH[0];
	if (STRENGTH[2] & 0x20) {
		if (tmp < 0x200)
			tmp = 0;
		else
			tmp = tmp - 0x200;
	} else {
		if (tmp > 0x1ff)
			tmp = 0;
		else
			tmp = 0x1ff - tmp;
	}
	*strength = (tmp << 7) | (tmp >> 2);
	return 0;
}