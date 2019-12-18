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
typedef  int u32 ;
struct dvb_frontend {struct cx24110_state* demodulator_priv; } ;
struct cx24110_state {int lastber; } ;

/* Variables and functions */
 int cx24110_readreg (struct cx24110_state*,int) ; 
 int /*<<< orphan*/  cx24110_writereg (struct cx24110_state*,int,int) ; 

__attribute__((used)) static int cx24110_read_ber(struct dvb_frontend* fe, u32* ber)
{
	struct cx24110_state *state = fe->demodulator_priv;

	/* fixme (maybe): value range is 16 bit. Scale? */
	if(cx24110_readreg(state,0x24)&0x10) {
		/* the Viterbi error counter has finished one counting window */
		cx24110_writereg(state,0x24,0x04); /* select the ber reg */
		state->lastber=cx24110_readreg(state,0x25)|
			(cx24110_readreg(state,0x26)<<8);
		cx24110_writereg(state,0x24,0x04); /* start new count window */
		cx24110_writereg(state,0x24,0x14);
	}
	*ber = state->lastber;

	return 0;
}