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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  scalar_t__ timf ;
struct dib3000mc_state {int timf; } ;
typedef  int s16 ;

/* Variables and functions */
 int TRANSMISSION_MODE_2K ; 
 int dib3000mc_read_word (struct dib3000mc_state*,int) ; 
 int /*<<< orphan*/  dib3000mc_write_word (struct dib3000mc_state*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int dib3000mc_set_timing(struct dib3000mc_state *state, s16 nfft, u32 bw, u8 update_offset)
{
	u32 timf;

	if (state->timf == 0) {
		timf = 1384402; // default value for 8MHz
		if (update_offset)
			msleep(200); // first time we do an update
	} else
		timf = state->timf;

	timf *= (bw / 1000);

	if (update_offset) {
		s16 tim_offs = dib3000mc_read_word(state, 416);

		if (tim_offs &  0x2000)
			tim_offs -= 0x4000;

		if (nfft == TRANSMISSION_MODE_2K)
			tim_offs *= 4;

		timf += tim_offs;
		state->timf = timf / (bw / 1000);
	}

	dprintk("timf: %d\n", timf);

	dib3000mc_write_word(state, 23, (u16) (timf >> 16));
	dib3000mc_write_word(state, 24, (u16) (timf      ) & 0xffff);

	return 0;
}