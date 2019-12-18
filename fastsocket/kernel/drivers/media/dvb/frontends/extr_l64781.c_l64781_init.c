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
struct l64781_state {scalar_t__ first; } ;
struct dvb_frontend {struct l64781_state* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  l64781_writereg (struct l64781_state*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  reset_and_configure (struct l64781_state*) ; 

__attribute__((used)) static int l64781_init(struct dvb_frontend* fe)
{
	struct l64781_state* state = fe->demodulator_priv;

	reset_and_configure (state);

	/* Power up */
	l64781_writereg (state, 0x3e, 0xa5);

	/* Reset hard */
	l64781_writereg (state, 0x2a, 0x04);
	l64781_writereg (state, 0x2a, 0x00);

	/* Set tuner specific things */
	/* AFC_POL, set also in reset_afc */
	l64781_writereg (state, 0x07, 0x8e);

	/* Use internal ADC */
	l64781_writereg (state, 0x0b, 0x81);

	/* AGC loop gain, and polarity is positive */
	l64781_writereg (state, 0x0c, 0x84);

	/* Internal ADC outputs two's complement */
	l64781_writereg (state, 0x0d, 0x8c);

	/* With ppm=8000, it seems the DTR_SENSITIVITY will result in
	   value of 2 with all possible bandwidths and guard
	   intervals, which is the initial value anyway. */
	/*l64781_writereg (state, 0x19, 0x92);*/

	/* Everything is two's complement, soft bit and CSI_OUT too */
	l64781_writereg (state, 0x1e, 0x09);

	/* delay a bit after first init attempt */
	if (state->first) {
		state->first = 0;
		msleep(200);
	}

	return 0;
}