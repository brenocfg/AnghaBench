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
struct va1j5jf8007t_state {int /*<<< orphan*/  tune_state; } ;
struct dvb_frontend {struct va1j5jf8007t_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  VA1J5JF8007T_IDLE ; 
 int va1j5jf8007t_set_sleep (struct va1j5jf8007t_state*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int va1j5jf8007t_init(struct dvb_frontend *fe)
{
	struct va1j5jf8007t_state *state;

	state = fe->demodulator_priv;
	state->tune_state = VA1J5JF8007T_IDLE;

	return va1j5jf8007t_set_sleep(state, 0);
}