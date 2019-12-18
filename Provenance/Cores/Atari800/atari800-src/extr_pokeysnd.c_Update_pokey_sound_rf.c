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
typedef  int UWORD ;
typedef  int ULONG ;
typedef  int UBYTE ;
struct TYPE_2__ {scalar_t__ nDigitized; } ;

/* Variables and functions */
 int ANTIC_CPU_CLOCK ; 
 int /*<<< orphan*/  BIENIAS_FIX ; 
 int* Div_n_cnt ; 
 int* Div_n_max ; 
 int* Outvol ; 
 size_t POKEYSND_SAMPBUF_MAX ; 
 int POKEYSND_samp_freq ; 
 int* POKEYSND_sampbuf_AUDV ; 
 int* POKEYSND_sampbuf_cnt ; 
 int POKEYSND_sampbuf_last ; 
 int /*<<< orphan*/  POKEYSND_sampbuf_lastval ; 
 size_t POKEYSND_sampbuf_ptr ; 
 size_t POKEYSND_sampbuf_rptr ; 
 int /*<<< orphan*/ * POKEYSND_sampbuf_val ; 
 scalar_t__ POKEYSND_stereo_enabled ; 
 int* POKEY_AUDC ; 
 int* POKEY_AUDCTL ; 
 int* POKEY_AUDF ; 
 int* POKEY_Base_mult ; 
 int POKEY_CH1_179 ; 
 int POKEY_CH1_CH2 ; 
 int POKEY_CH1_FILTER ; 
 int POKEY_CH2_FILTER ; 
 int POKEY_CH3_179 ; 
 int POKEY_CH3_CH4 ; 
 int POKEY_CHAN1 ; 
 int POKEY_CHAN2 ; 
 int POKEY_CHAN3 ; 
 int POKEY_CHAN4 ; 
#define  POKEY_OFFSET_AUDC1 136 
#define  POKEY_OFFSET_AUDC2 135 
#define  POKEY_OFFSET_AUDC3 134 
#define  POKEY_OFFSET_AUDC4 133 
#define  POKEY_OFFSET_AUDCTL 132 
#define  POKEY_OFFSET_AUDF1 131 
#define  POKEY_OFFSET_AUDF2 130 
#define  POKEY_OFFSET_AUDF3 129 
#define  POKEY_OFFSET_AUDF4 128 
 int POKEY_VOLUME_MASK ; 
 int POKEY_VOL_ONLY ; 
 int Samp_n_max ; 
 TYPE_1__ g_Sound ; 
 int* pokeysnd_AUDV ; 
 int* sampbuf_cnt2 ; 
 int sampbuf_last2 ; 
 int /*<<< orphan*/  sampbuf_lastval2 ; 
 size_t sampbuf_ptr2 ; 
 size_t sampbuf_rptr2 ; 
 int /*<<< orphan*/ * sampbuf_val2 ; 

__attribute__((used)) static void Update_pokey_sound_rf(UWORD addr, UBYTE val, UBYTE chip,
				  UBYTE gain)
{
	ULONG new_val = 0;
	UBYTE chan;
	UBYTE chan_mask;
	UBYTE chip_offs;

	/* calculate the chip_offs for the channel arrays */
	chip_offs = chip << 2;

	/* determine which address was changed */
	switch (addr & 0x0f) {
	case POKEY_OFFSET_AUDF1:
		/* POKEY_AUDF[POKEY_CHAN1 + chip_offs] = val; */
		chan_mask = 1 << POKEY_CHAN1;
		if (POKEY_AUDCTL[chip] & POKEY_CH1_CH2)		/* if ch 1&2 tied together */
			chan_mask |= 1 << POKEY_CHAN2;	/* then also change on ch2 */
		break;
	case POKEY_OFFSET_AUDC1:
		/* POKEY_AUDC[POKEY_CHAN1 + chip_offs] = val; */
		pokeysnd_AUDV[POKEY_CHAN1 + chip_offs] = (val & POKEY_VOLUME_MASK) * gain;
		chan_mask = 1 << POKEY_CHAN1;
		break;
	case POKEY_OFFSET_AUDF2:
		/* POKEY_AUDF[POKEY_CHAN2 + chip_offs] = val; */
		chan_mask = 1 << POKEY_CHAN2;
		break;
	case POKEY_OFFSET_AUDC2:
		/* POKEY_AUDC[POKEY_CHAN2 + chip_offs] = val; */
		pokeysnd_AUDV[POKEY_CHAN2 + chip_offs] = (val & POKEY_VOLUME_MASK) * gain;
		chan_mask = 1 << POKEY_CHAN2;
		break;
	case POKEY_OFFSET_AUDF3:
		/* POKEY_AUDF[POKEY_CHAN3 + chip_offs] = val; */
		chan_mask = 1 << POKEY_CHAN3;
		if (POKEY_AUDCTL[chip] & POKEY_CH3_CH4)		/* if ch 3&4 tied together */
			chan_mask |= 1 << POKEY_CHAN4;	/* then also change on ch4 */
		break;
	case POKEY_OFFSET_AUDC3:
		/* POKEY_AUDC[POKEY_CHAN3 + chip_offs] = val; */
		pokeysnd_AUDV[POKEY_CHAN3 + chip_offs] = (val & POKEY_VOLUME_MASK) * gain;
		chan_mask = 1 << POKEY_CHAN3;
		break;
	case POKEY_OFFSET_AUDF4:
		/* POKEY_AUDF[POKEY_CHAN4 + chip_offs] = val; */
		chan_mask = 1 << POKEY_CHAN4;
		break;
	case POKEY_OFFSET_AUDC4:
		/* POKEY_AUDC[POKEY_CHAN4 + chip_offs] = val; */
		pokeysnd_AUDV[POKEY_CHAN4 + chip_offs] = (val & POKEY_VOLUME_MASK) * gain;
		chan_mask = 1 << POKEY_CHAN4;
		break;
	case POKEY_OFFSET_AUDCTL:
		/* POKEY_AUDCTL[chip] = val; */
		chan_mask = 15;			/* all channels */
		break;
	default:
		chan_mask = 0;
		break;
	}

	/************************************************************/
	/* As defined in the manual, the exact Div_n_cnt values are */
	/* different depending on the frequency and resolution:     */
	/*    64 kHz or 15 kHz - AUDF + 1                           */
	/*    1 MHz, 8-bit -     AUDF + 4                           */
	/*    1 MHz, 16-bit -    POKEY_AUDF[POKEY_CHAN1]+256*POKEY_AUDF[POKEY_CHAN2] + 7    */
	/************************************************************/

	/* only reset the channels that have changed */

	if (chan_mask & (1 << POKEY_CHAN1)) {
		/* process channel 1 frequency */
		if (POKEY_AUDCTL[chip] & POKEY_CH1_179)
			new_val = POKEY_AUDF[POKEY_CHAN1 + chip_offs] + 4;
		else
			new_val = (POKEY_AUDF[POKEY_CHAN1 + chip_offs] + 1) * POKEY_Base_mult[chip];

		if (new_val != Div_n_max[POKEY_CHAN1 + chip_offs]) {
			Div_n_max[POKEY_CHAN1 + chip_offs] = new_val;

			if (Div_n_cnt[POKEY_CHAN1 + chip_offs] > new_val) {
				Div_n_cnt[POKEY_CHAN1 + chip_offs] = new_val;
			}
		}
	}

	if (chan_mask & (1 << POKEY_CHAN2)) {
		/* process channel 2 frequency */
		if (POKEY_AUDCTL[chip] & POKEY_CH1_CH2) {
			if (POKEY_AUDCTL[chip] & POKEY_CH1_179)
				new_val = POKEY_AUDF[POKEY_CHAN2 + chip_offs] * 256 +
					POKEY_AUDF[POKEY_CHAN1 + chip_offs] + 7;
			else
				new_val = (POKEY_AUDF[POKEY_CHAN2 + chip_offs] * 256 +
						   POKEY_AUDF[POKEY_CHAN1 + chip_offs] + 1) * POKEY_Base_mult[chip];
		}
		else
			new_val = (POKEY_AUDF[POKEY_CHAN2 + chip_offs] + 1) * POKEY_Base_mult[chip];

		if (new_val != Div_n_max[POKEY_CHAN2 + chip_offs]) {
			Div_n_max[POKEY_CHAN2 + chip_offs] = new_val;

			if (Div_n_cnt[POKEY_CHAN2 + chip_offs] > new_val) {
				Div_n_cnt[POKEY_CHAN2 + chip_offs] = new_val;
			}
		}
	}

	if (chan_mask & (1 << POKEY_CHAN3)) {
		/* process channel 3 frequency */
		if (POKEY_AUDCTL[chip] & POKEY_CH3_179)
			new_val = POKEY_AUDF[POKEY_CHAN3 + chip_offs] + 4;
		else
			new_val = (POKEY_AUDF[POKEY_CHAN3 + chip_offs] + 1) * POKEY_Base_mult[chip];

		if (new_val != Div_n_max[POKEY_CHAN3 + chip_offs]) {
			Div_n_max[POKEY_CHAN3 + chip_offs] = new_val;

			if (Div_n_cnt[POKEY_CHAN3 + chip_offs] > new_val) {
				Div_n_cnt[POKEY_CHAN3 + chip_offs] = new_val;
			}
		}
	}

	if (chan_mask & (1 << POKEY_CHAN4)) {
		/* process channel 4 frequency */
		if (POKEY_AUDCTL[chip] & POKEY_CH3_CH4) {
			if (POKEY_AUDCTL[chip] & POKEY_CH3_179)
				new_val = POKEY_AUDF[POKEY_CHAN4 + chip_offs] * 256 +
					POKEY_AUDF[POKEY_CHAN3 + chip_offs] + 7;
			else
				new_val = (POKEY_AUDF[POKEY_CHAN4 + chip_offs] * 256 +
						   POKEY_AUDF[POKEY_CHAN3 + chip_offs] + 1) * POKEY_Base_mult[chip];
		}
		else
			new_val = (POKEY_AUDF[POKEY_CHAN4 + chip_offs] + 1) * POKEY_Base_mult[chip];

		if (new_val != Div_n_max[POKEY_CHAN4 + chip_offs]) {
			Div_n_max[POKEY_CHAN4 + chip_offs] = new_val;

			if (Div_n_cnt[POKEY_CHAN4 + chip_offs] > new_val) {
				Div_n_cnt[POKEY_CHAN4 + chip_offs] = new_val;
			}
		}
	}

	/* if channel is volume only, set current output */
	for (chan = POKEY_CHAN1; chan <= POKEY_CHAN4; chan++) {
		if (chan_mask & (1 << chan)) {

#ifdef VOL_ONLY_SOUND

#ifdef __PLUS
			if (g_Sound.nDigitized)
#endif
			if ((POKEY_AUDC[chan + chip_offs] & POKEY_VOL_ONLY)) {

#ifdef STEREO_SOUND

#ifdef __PLUS
				if (POKEYSND_stereo_enabled && chip & 0x01)
#else
				if (chip & 0x01)
#endif
				{
					sampbuf_lastval2 += pokeysnd_AUDV[chan + chip_offs]
						- POKEYSND_sampbuf_AUDV[chan + chip_offs];

					sampbuf_val2[sampbuf_ptr2] = sampbuf_lastval2;
					POKEYSND_sampbuf_AUDV[chan + chip_offs] = pokeysnd_AUDV[chan + chip_offs];
					sampbuf_cnt2[sampbuf_ptr2] =
						(ANTIC_CPU_CLOCK - sampbuf_last2) * 128 * POKEYSND_samp_freq / 178979;
					sampbuf_last2 = ANTIC_CPU_CLOCK;
					sampbuf_ptr2++;
					if (sampbuf_ptr2 >= POKEYSND_SAMPBUF_MAX)
						sampbuf_ptr2 = 0;
					if (sampbuf_ptr2 == sampbuf_rptr2) {
						sampbuf_rptr2++;
						if (sampbuf_rptr2 >= POKEYSND_SAMPBUF_MAX)
							sampbuf_rptr2 = 0;
					}
				}
				else
#endif /* STEREO_SOUND */
				{
					POKEYSND_sampbuf_lastval += pokeysnd_AUDV[chan + chip_offs]
						-POKEYSND_sampbuf_AUDV[chan + chip_offs];

					POKEYSND_sampbuf_val[POKEYSND_sampbuf_ptr] = POKEYSND_sampbuf_lastval;
					POKEYSND_sampbuf_AUDV[chan + chip_offs] = pokeysnd_AUDV[chan + chip_offs];
					POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_ptr] =
						(ANTIC_CPU_CLOCK - POKEYSND_sampbuf_last) * 128 * POKEYSND_samp_freq / 178979;
					POKEYSND_sampbuf_last = ANTIC_CPU_CLOCK;
					POKEYSND_sampbuf_ptr++;
					if (POKEYSND_sampbuf_ptr >= POKEYSND_SAMPBUF_MAX)
						POKEYSND_sampbuf_ptr = 0;
					if (POKEYSND_sampbuf_ptr == POKEYSND_sampbuf_rptr) {
						POKEYSND_sampbuf_rptr++;
						if (POKEYSND_sampbuf_rptr >= POKEYSND_SAMPBUF_MAX)
							POKEYSND_sampbuf_rptr = 0;
					}
				}
			}

#endif /* VOL_ONLY_SOUND */

			/* I've disabled any frequencies that exceed the sampling
			   frequency.  There isn't much point in processing frequencies
			   that the hardware can't reproduce.  I've also disabled
			   processing if the volume is zero. */

			/* if the channel is volume only */
			/* or the channel is off (volume == 0) */
			/* or the channel freq is greater than the playback freq */
			if ( (POKEY_AUDC[chan + chip_offs] & POKEY_VOL_ONLY) ||
				((POKEY_AUDC[chan + chip_offs] & POKEY_VOLUME_MASK) == 0)
				|| (!BIENIAS_FIX && (Div_n_max[chan + chip_offs] < (Samp_n_max >> 8)))
				) {
				/* indicate the channel is 'on' */
				Outvol[chan + chip_offs] = 1;

				/* can only ignore channel if filtering off */
				if ((chan == POKEY_CHAN3 && !(POKEY_AUDCTL[chip] & POKEY_CH1_FILTER)) ||
					(chan == POKEY_CHAN4 && !(POKEY_AUDCTL[chip] & POKEY_CH2_FILTER)) ||
					(chan == POKEY_CHAN1) ||
					(chan == POKEY_CHAN2)
					|| (!BIENIAS_FIX && (Div_n_max[chan + chip_offs] < (Samp_n_max >> 8)))
				) {
					/* and set channel freq to max to reduce processing */
					Div_n_max[chan + chip_offs] = 0x7fffffffL;
					Div_n_cnt[chan + chip_offs] = 0x7fffffffL;
				}
			}
		}
	}

	/*    _enable(); */ /* RSF - removed for portability 31-MAR-97 */
}