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
struct va1j5jf8007s_state {int dummy; } ;
struct dvb_frontend {struct va1j5jf8007s_state* demodulator_priv; } ;

/* Variables and functions */
 int va1j5jf8007s_init_frequency (struct va1j5jf8007s_state*) ; 
 int va1j5jf8007s_set_sleep (struct va1j5jf8007s_state*,int) ; 

__attribute__((used)) static int va1j5jf8007s_sleep(struct dvb_frontend *fe)
{
	struct va1j5jf8007s_state *state;
	int ret;

	state = fe->demodulator_priv;

	ret = va1j5jf8007s_init_frequency(state);
	if (ret < 0)
		return ret;

	return va1j5jf8007s_set_sleep(state, 1);
}