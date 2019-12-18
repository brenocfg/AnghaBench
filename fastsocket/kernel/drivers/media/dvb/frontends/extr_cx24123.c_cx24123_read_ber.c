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
struct dvb_frontend {struct cx24123_state* demodulator_priv; } ;
struct cx24123_state {int dummy; } ;

/* Variables and functions */
 int cx24123_readreg (struct cx24123_state*,int) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 

__attribute__((used)) static int cx24123_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct cx24123_state *state = fe->demodulator_priv;

	/* The true bit error rate is this value divided by
	   the window size (set as 256 * 255) */
	*ber = ((cx24123_readreg(state, 0x1c) & 0x3f) << 16) |
		(cx24123_readreg(state, 0x1d) << 8 |
		 cx24123_readreg(state, 0x1e));

	dprintk("BER = %d\n", *ber);

	return 0;
}