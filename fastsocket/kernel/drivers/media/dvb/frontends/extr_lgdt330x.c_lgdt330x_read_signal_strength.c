#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct lgdt330x_state {int snr; } ;
struct TYPE_2__ {int (* read_snr ) (struct dvb_frontend*,int*) ;} ;
struct dvb_frontend {TYPE_1__ ops; scalar_t__ demodulator_priv; } ;

/* Variables and functions */
 int stub1 (struct dvb_frontend*,int*) ; 

__attribute__((used)) static int lgdt330x_read_signal_strength(struct dvb_frontend* fe, u16* strength)
{
	/* Calculate Strength from SNR up to 35dB */
	/* Even though the SNR can go higher than 35dB, there is some comfort */
	/* factor in having a range of strong signals that can show at 100%   */
	struct lgdt330x_state* state = (struct lgdt330x_state*) fe->demodulator_priv;
	u16 snr;
	int ret;

	ret = fe->ops.read_snr(fe, &snr);
	if (ret != 0)
		return ret;
	/* Rather than use the 8.8 value snr, use state->snr which is 8.24 */
	/* scale the range 0 - 35*2^24 into 0 - 65535 */
	if (state->snr >= 8960 * 0x10000)
		*strength = 0xffff;
	else
		*strength = state->snr / 8960;

	return 0;
}