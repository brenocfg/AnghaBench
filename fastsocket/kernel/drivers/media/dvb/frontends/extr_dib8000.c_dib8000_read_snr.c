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
typedef  int u16 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int dib8000_read_word (struct dib8000_state*,int) ; 
 int intlog10 (int) ; 

__attribute__((used)) static int dib8000_read_snr(struct dvb_frontend *fe, u16 * snr)
{
	struct dib8000_state *state = fe->demodulator_priv;
	u16 val;
	s32 signal_mant, signal_exp, noise_mant, noise_exp;
	u32 result = 0;

	val = dib8000_read_word(state, 542);
	noise_mant = (val >> 6) & 0xff;
	noise_exp = (val & 0x3f);

	val = dib8000_read_word(state, 543);
	signal_mant = (val >> 6) & 0xff;
	signal_exp = (val & 0x3f);

	if ((noise_exp & 0x20) != 0)
		noise_exp -= 0x40;
	if ((signal_exp & 0x20) != 0)
		signal_exp -= 0x40;

	if (signal_mant != 0)
		result = intlog10(2) * 10 * signal_exp + 10 * intlog10(signal_mant);
	else
		result = intlog10(2) * 10 * signal_exp - 100;
	if (noise_mant != 0)
		result -= intlog10(2) * 10 * noise_exp + 10 * intlog10(noise_mant);
	else
		result -= intlog10(2) * 10 * noise_exp - 100;

	*snr = result / ((1 << 24) / 10);
	return 0;
}