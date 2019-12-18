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
struct i2c_client {int dummy; } ;
struct cx25840_state {scalar_t__ aud_input; int audclk_freq; } ;

/* Variables and functions */
 scalar_t__ CX25840_AUDIO_SERIAL ; 
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  cx25840_write4 (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  is_cx2583x (struct cx25840_state*) ; 
 struct cx25840_state* to_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cx25840_set_audclk_freq(struct i2c_client *client, u32 freq)
{
	struct cx25840_state *state = to_state(i2c_get_clientdata(client));

	if (state->aud_input != CX25840_AUDIO_SERIAL) {
		switch (freq) {
		case 32000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x06, AUX PLL Post Divider = 0x10
			 */
			cx25840_write4(client, 0x108, 0x1006040f);

			/*
			 * VID_PLL Fraction (register 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postdivide
			 */

			/*
			 * AUX_PLL Fraction = 0x1bb39ee
			 * 28636363 * 0x6.dd9cf70/0x10 = 32000 * 384
			 * 196.6 MHz pre-postdivide
			 * FIXME < 200 MHz is out of specified valid range
			 * FIXME 28636363 ref_freq doesn't match VID PLL ref
			 */
			cx25840_write4(client, 0x110, 0x01bb39ee);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 384/384 * AUX_PLL post dvivider
			 */
			cx25840_write(client, 0x127, 0x50);

			if (is_cx2583x(state))
				break;

			/* src3/4/6_ctl */
			/* 0x1.f77f = (4 * 28636360/8 * 2/455) / 32000 */
			cx25840_write4(client, 0x900, 0x0801f77f);
			cx25840_write4(client, 0x904, 0x0801f77f);
			cx25840_write4(client, 0x90c, 0x0801f77f);
			break;

		case 44100:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x09, AUX PLL Post Divider = 0x10
			 */
			cx25840_write4(client, 0x108, 0x1009040f);

			/*
			 * VID_PLL Fraction (register 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postdivide
			 */

			/*
			 * AUX_PLL Fraction = 0x0ec6bd6
			 * 28636363 * 0x9.7635eb0/0x10 = 44100 * 384
			 * 271 MHz pre-postdivide
			 * FIXME 28636363 ref_freq doesn't match VID PLL ref
			 */
			cx25840_write4(client, 0x110, 0x00ec6bd6);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 384/384 * AUX_PLL post dvivider
			 */
			cx25840_write(client, 0x127, 0x50);

			if (is_cx2583x(state))
				break;

			/* src3/4/6_ctl */
			/* 0x1.6d59 = (4 * 28636360/8 * 2/455) / 44100 */
			cx25840_write4(client, 0x900, 0x08016d59);
			cx25840_write4(client, 0x904, 0x08016d59);
			cx25840_write4(client, 0x90c, 0x08016d59);
			break;

		case 48000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0a, AUX PLL Post Divider = 0x10
			 */
			cx25840_write4(client, 0x108, 0x100a040f);

			/*
			 * VID_PLL Fraction (register 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postdivide
			 */

			/*
			 * AUX_PLL Fraction = 0x098d6e5
			 * 28636363 * 0xa.4c6b728/0x10 = 48000 * 384
			 * 295 MHz pre-postdivide
			 * FIXME 28636363 ref_freq doesn't match VID PLL ref
			 */
			cx25840_write4(client, 0x110, 0x0098d6e5);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 384/384 * AUX_PLL post dvivider
			 */
			cx25840_write(client, 0x127, 0x50);

			if (is_cx2583x(state))
				break;

			/* src3/4/6_ctl */
			/* 0x1.4faa = (4 * 28636360/8 * 2/455) / 48000 */
			cx25840_write4(client, 0x900, 0x08014faa);
			cx25840_write4(client, 0x904, 0x08014faa);
			cx25840_write4(client, 0x90c, 0x08014faa);
			break;
		}
	} else {
		switch (freq) {
		case 32000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x08, AUX PLL Post Divider = 0x1e
			 */
			cx25840_write4(client, 0x108, 0x1e08040f);

			/*
			 * VID_PLL Fraction (register 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postdivide
			 */

			/*
			 * AUX_PLL Fraction = 0x12a0869
			 * 28636363 * 0x8.9504348/0x1e = 32000 * 256
			 * 246 MHz pre-postdivide
			 * FIXME 28636363 ref_freq doesn't match VID PLL ref
			 */
			cx25840_write4(client, 0x110, 0x012a0869);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x14 = 256/384 * AUX_PLL post dvivider
			 */
			cx25840_write(client, 0x127, 0x54);

			if (is_cx2583x(state))
				break;

			/* src1_ctl */
			/* 0x1.0000 = 32000/32000 */
			cx25840_write4(client, 0x8f8, 0x08010000);

			/* src3/4/6_ctl */
			/* 0x2.0000 = 2 * (32000/32000) */
			cx25840_write4(client, 0x900, 0x08020000);
			cx25840_write4(client, 0x904, 0x08020000);
			cx25840_write4(client, 0x90c, 0x08020000);
			break;

		case 44100:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x09, AUX PLL Post Divider = 0x18
			 */
			cx25840_write4(client, 0x108, 0x1809040f);

			/*
			 * VID_PLL Fraction (register 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postdivide
			 */

			/*
			 * AUX_PLL Fraction = 0x0ec6bd6
			 * 28636363 * 0x9.7635eb0/0x18 = 44100 * 256
			 * 271 MHz pre-postdivide
			 * FIXME 28636363 ref_freq doesn't match VID PLL ref
			 */
			cx25840_write4(client, 0x110, 0x00ec6bd6);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 256/384 * AUX_PLL post dvivider
			 */
			cx25840_write(client, 0x127, 0x50);

			if (is_cx2583x(state))
				break;

			/* src1_ctl */
			/* 0x1.60cd = 44100/32000 */
			cx25840_write4(client, 0x8f8, 0x080160cd);

			/* src3/4/6_ctl */
			/* 0x1.7385 = 2 * (32000/44100) */
			cx25840_write4(client, 0x900, 0x08017385);
			cx25840_write4(client, 0x904, 0x08017385);
			cx25840_write4(client, 0x90c, 0x08017385);
			break;

		case 48000:
			/*
			 * VID_PLL Integer = 0x0f, VID_PLL Post Divider = 0x04
			 * AUX_PLL Integer = 0x0a, AUX PLL Post Divider = 0x18
			 */
			cx25840_write4(client, 0x108, 0x180a040f);

			/*
			 * VID_PLL Fraction (register 0x10c) = 0x2be2fe
			 * 28636360 * 0xf.15f17f0/4 = 108 MHz
			 * 432 MHz pre-postdivide
			 */

			/*
			 * AUX_PLL Fraction = 0x098d6e5
			 * 28636363 * 0xa.4c6b728/0x18 = 48000 * 256
			 * 295 MHz pre-postdivide
			 * FIXME 28636363 ref_freq doesn't match VID PLL ref
			 */
			cx25840_write4(client, 0x110, 0x0098d6e5);

			/*
			 * SA_MCLK_SEL = 1
			 * SA_MCLK_DIV = 0x10 = 256/384 * AUX_PLL post dvivider
			 */
			cx25840_write(client, 0x127, 0x50);

			if (is_cx2583x(state))
				break;

			/* src1_ctl */
			/* 0x1.8000 = 48000/32000 */
			cx25840_write4(client, 0x8f8, 0x08018000);

			/* src3/4/6_ctl */
			/* 0x1.5555 = 2 * (32000/48000) */
			cx25840_write4(client, 0x900, 0x08015555);
			cx25840_write4(client, 0x904, 0x08015555);
			cx25840_write4(client, 0x90c, 0x08015555);
			break;
		}
	}

	state->audclk_freq = freq;

	return 0;
}