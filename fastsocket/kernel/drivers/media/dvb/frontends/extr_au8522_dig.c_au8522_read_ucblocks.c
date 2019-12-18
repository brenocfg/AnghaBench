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
typedef  int /*<<< orphan*/  u32 ;
struct dvb_frontend {struct au8522_state* demodulator_priv; } ;
struct au8522_state {scalar_t__ current_modulation; } ;

/* Variables and functions */
 scalar_t__ VSB_8 ; 
 int /*<<< orphan*/  au8522_readreg (struct au8522_state*,int) ; 

__attribute__((used)) static int au8522_read_ucblocks(struct dvb_frontend *fe, u32 *ucblocks)
{
	struct au8522_state *state = fe->demodulator_priv;

	if (state->current_modulation == VSB_8)
		*ucblocks = au8522_readreg(state, 0x4087);
	else
		*ucblocks = au8522_readreg(state, 0x4543);

	return 0;
}