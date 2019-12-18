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
struct dvb_frontend {struct cx22700_state* demodulator_priv; } ;
struct cx22700_state {int dummy; } ;

/* Variables and functions */
 int cx22700_readreg (struct cx22700_state*,int) ; 

__attribute__((used)) static int cx22700_read_signal_strength(struct dvb_frontend* fe, u16* signal_strength)
{
	struct cx22700_state* state = fe->demodulator_priv;

	u16 rs_ber = (cx22700_readreg (state, 0x0d) << 9)
		   | (cx22700_readreg (state, 0x0e) << 1);
	*signal_strength = ~rs_ber;

	return 0;
}