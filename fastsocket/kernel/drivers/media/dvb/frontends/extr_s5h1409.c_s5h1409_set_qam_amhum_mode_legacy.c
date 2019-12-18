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
typedef  int u16 ;
struct s5h1409_state {int is_qam_locked; } ;
struct dvb_frontend {struct s5h1409_state* demodulator_priv; } ;

/* Variables and functions */
 int s5h1409_readreg (struct s5h1409_state*,int) ; 
 int /*<<< orphan*/  s5h1409_writereg (struct s5h1409_state*,int,int) ; 

__attribute__((used)) static void s5h1409_set_qam_amhum_mode_legacy(struct dvb_frontend *fe)
{
	struct s5h1409_state *state = fe->demodulator_priv;
	u16 reg;

	if (state->is_qam_locked)
		return;

	/* QAM EQ lock check */
	reg = s5h1409_readreg(state, 0xf0);

	if ((reg >> 13) & 0x1) {

		state->is_qam_locked = 1;
		reg &= 0xff;

		s5h1409_writereg(state, 0x96, 0x00c);
		if ((reg < 0x38) || (reg > 0x68)) {
			s5h1409_writereg(state, 0x93, 0x3332);
			s5h1409_writereg(state, 0x9e, 0x2c37);
		} else {
			s5h1409_writereg(state, 0x93, 0x3130);
			s5h1409_writereg(state, 0x9e, 0x2836);
		}

	} else {
		s5h1409_writereg(state, 0x96, 0x0008);
		s5h1409_writereg(state, 0x93, 0x3332);
		s5h1409_writereg(state, 0x9e, 0x2c37);
	}
}