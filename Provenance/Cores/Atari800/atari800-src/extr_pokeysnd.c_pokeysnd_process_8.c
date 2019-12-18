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
typedef  size_t ULONG ;
typedef  int UBYTE ;
struct TYPE_2__ {scalar_t__ nDigitized; } ;
typedef  int /*<<< orphan*/  SWORD ;

/* Variables and functions */
 void* ANTIC_CPU_CLOCK ; 
 size_t* Div_n_cnt ; 
 scalar_t__* Div_n_max ; 
 int FALSE ; 
 int Num_pokeys ; 
 int* Outvol ; 
 size_t P17 ; 
 size_t P4 ; 
 size_t P5 ; 
 size_t P9 ; 
 size_t POKEYSND_SAMPBUF_MAX ; 
 int POKEYSND_SAMP_MAX ; 
 int POKEYSND_SAMP_MIN ; 
 int* POKEYSND_sampbuf_cnt ; 
 void* POKEYSND_sampbuf_last ; 
 size_t POKEYSND_sampbuf_ptr ; 
 size_t POKEYSND_sampbuf_rptr ; 
 scalar_t__* POKEYSND_sampbuf_val ; 
 scalar_t__ POKEYSND_sampout ; 
 scalar_t__ POKEYSND_stereo_enabled ; 
 int* POKEY_AUDC ; 
 int* POKEY_AUDCTL ; 
 int POKEY_CH1_FILTER ; 
 int POKEY_CH2_FILTER ; 
 int POKEY_CHAN1 ; 
 int POKEY_CHAN2 ; 
 int POKEY_CHAN3 ; 
 int POKEY_CHAN4 ; 
 int POKEY_NOTPOLY5 ; 
 size_t POKEY_POLY17_SIZE ; 
 int POKEY_POLY4 ; 
 size_t POKEY_POLY4_SIZE ; 
 size_t POKEY_POLY5_SIZE ; 
 int POKEY_POLY9 ; 
 size_t POKEY_POLY9_SIZE ; 
 int POKEY_PURETONE ; 
 int POKEY_SAMPLE ; 
 int POKEY_VOL_ONLY ; 
 size_t* POKEY_poly17_lookup ; 
 int* POKEY_poly9_lookup ; 
 size_t READ_U32 (int*) ; 
 int* Samp_n_cnt ; 
 int Samp_n_max ; 
 int TRUE ; 
 int /*<<< orphan*/  WRITE_U32 (int*,size_t) ; 
 int* bit4 ; 
 scalar_t__* bit5 ; 
 TYPE_1__ g_Sound ; 
 int last_val ; 
 int last_val2 ; 
 int* pokeysnd_AUDV ; 
 int* sampbuf_cnt2 ; 
 void* sampbuf_last2 ; 
 size_t sampbuf_ptr2 ; 
 size_t sampbuf_rptr2 ; 
 scalar_t__* sampbuf_val2 ; 
 scalar_t__ sampout2 ; 
 scalar_t__ speaker ; 

__attribute__((used)) static void pokeysnd_process_8(void *sndbuffer, int sndn)
{
	register UBYTE *buffer = (UBYTE *) sndbuffer;
	register int n = sndn;

	register ULONG *div_n_ptr;
	register UBYTE *samp_cnt_w_ptr;
	register ULONG event_min;
	register UBYTE next_event;
#ifdef CLIP_SOUND
	register SWORD cur_val;		/* then we have to count as 16-bit signed */
#ifdef STEREO_SOUND
	register SWORD cur_val2;
#endif
#else /* CLIP_SOUND */
	register UBYTE cur_val;		/* otherwise we'll simplify as 8-bit unsigned */
#ifdef STEREO_SOUND
	register UBYTE cur_val2;
#endif
#endif /* CLIP_SOUND */
	register UBYTE *out_ptr;
	register UBYTE audc;
	register UBYTE toggle;
	register UBYTE count;
	register UBYTE *vol_ptr;

	/* set a pointer to the whole portion of the samp_n_cnt */
#ifdef WORDS_BIGENDIAN
	samp_cnt_w_ptr = ((UBYTE *) (&Samp_n_cnt[0]) + 3);
#else
	samp_cnt_w_ptr = ((UBYTE *) (&Samp_n_cnt[0]) + 1);
#endif

	/* set a pointer for optimization */
	out_ptr = Outvol;
	vol_ptr = pokeysnd_AUDV;

	/* The current output is pre-determined and then adjusted based on each */
	/* output change for increased performance (less over-all math). */
	/* add the output values of all 4 channels */
	cur_val = POKEYSND_SAMP_MIN;
#ifdef STEREO_SOUND
#ifdef __PLUS
	if (POKEYSND_stereo_enabled)
#endif
	cur_val2 = POKEYSND_SAMP_MIN;
#endif /* STEREO_SOUND */

	count = Num_pokeys;
	do {
		if (*out_ptr++)
			cur_val += *vol_ptr;
		vol_ptr++;

		if (*out_ptr++)
			cur_val += *vol_ptr;
		vol_ptr++;

		if (*out_ptr++)
			cur_val += *vol_ptr;
		vol_ptr++;

		if (*out_ptr++)
			cur_val += *vol_ptr;
		vol_ptr++;
#ifdef STEREO_SOUND
#ifdef __PLUS
		if (POKEYSND_stereo_enabled)
#endif
		{
			count--;
			if (count) {
				if (*out_ptr++)
					cur_val2 += *vol_ptr;
				vol_ptr++;

				if (*out_ptr++)
					cur_val2 += *vol_ptr;
				vol_ptr++;

				if (*out_ptr++)
					cur_val2 += *vol_ptr;
				vol_ptr++;

				if (*out_ptr++)
					cur_val2 += *vol_ptr;
				vol_ptr++;
			}
			else
				break;
		}
#endif /* STEREO_SOUND */
		count--;
	} while (count);

#ifdef SYNCHRONIZED_SOUND
	cur_val += speaker;
#endif

	/* loop until the buffer is filled */
	while (n) {
		/* Normally the routine would simply decrement the 'div by N' */
		/* counters and react when they reach zero.  Since we normally */
		/* won't be processing except once every 80 or so counts, */
		/* I've optimized by finding the smallest count and then */
		/* 'accelerated' time by adjusting all pointers by that amount. */

		/* find next smallest event (either sample or chan 1-4) */
		next_event = POKEY_SAMPLE;
		event_min = READ_U32(samp_cnt_w_ptr);

		div_n_ptr = Div_n_cnt;

		count = 0;
		do {
			/* Though I could have used a loop here, this is faster */
			if (*div_n_ptr <= event_min) {
				event_min = *div_n_ptr;
				next_event = POKEY_CHAN1 + (count << 2);
			}
			div_n_ptr++;
			if (*div_n_ptr <= event_min) {
				event_min = *div_n_ptr;
				next_event = POKEY_CHAN2 + (count << 2);
			}
			div_n_ptr++;
			if (*div_n_ptr <= event_min) {
				event_min = *div_n_ptr;
				next_event = POKEY_CHAN3 + (count << 2);
			}
			div_n_ptr++;
			if (*div_n_ptr <= event_min) {
				event_min = *div_n_ptr;
				next_event = POKEY_CHAN4 + (count << 2);
			}
			div_n_ptr++;

			count++;
		} while (count < Num_pokeys);

		/* if the next event is a channel change */
		if (next_event != POKEY_SAMPLE) {
			/* shift the polynomial counters */

			count = Num_pokeys;
			do {
				/* decrement all counters by the smallest count found */
				/* again, no loop for efficiency */
				div_n_ptr--;
				*div_n_ptr -= event_min;
				div_n_ptr--;
				*div_n_ptr -= event_min;
				div_n_ptr--;
				*div_n_ptr -= event_min;
				div_n_ptr--;
				*div_n_ptr -= event_min;

				count--;
			} while (count);


			WRITE_U32(samp_cnt_w_ptr, READ_U32(samp_cnt_w_ptr) - event_min);

			/* since the polynomials require a mod (%) function which is
			   division, I don't adjust the polynomials on the SAMPLE events,
			   only the CHAN events.  I have to keep track of the change,
			   though. */

			P4 = (P4 + event_min) % POKEY_POLY4_SIZE;
			P5 = (P5 + event_min) % POKEY_POLY5_SIZE;
			P9 = (P9 + event_min) % POKEY_POLY9_SIZE;
			P17 = (P17 + event_min) % POKEY_POLY17_SIZE;

			/* adjust channel counter */
			Div_n_cnt[next_event] += Div_n_max[next_event];

			/* get the current AUDC into a register (for optimization) */
			audc = POKEY_AUDC[next_event];

			/* set a pointer to the current output (for opt...) */
			out_ptr = &Outvol[next_event];

			/* assume no changes to the output */
			toggle = FALSE;

			/* From here, a good understanding of the hardware is required */
			/* to understand what is happening.  I won't be able to provide */
			/* much description to explain it here. */

			/* if VOLUME only then nothing to process */
			if (!(audc & POKEY_VOL_ONLY)) {
				/* if the output is pure or the output is poly5 and the poly5 bit */
				/* is set */
				if ((audc & POKEY_NOTPOLY5) || bit5[P5]) {
					/* if the PURETONE bit is set */
					if (audc & POKEY_PURETONE) {
						/* then simply toggle the output */
						toggle = TRUE;
					}
					/* otherwise if POLY4 is selected */
					else if (audc & POKEY_POLY4) {
						/* then compare to the poly4 bit */
						toggle = (bit4[P4] == !(*out_ptr));
					}
					else {
						/* if 9-bit poly is selected on this chip */
						if (POKEY_AUDCTL[next_event >> 2] & POKEY_POLY9) {
							/* compare to the poly9 bit */
							toggle = ((POKEY_poly9_lookup[P9] & 1) == !(*out_ptr));
						}
						else {
							/* otherwise compare to the poly17 bit */
							toggle = (((POKEY_poly17_lookup[P17 >> 3] >> (P17 & 7)) & 1) == !(*out_ptr));
						}
					}
				}
			}

			/* check channel 1 filter (clocked by channel 3) */
			if ( POKEY_AUDCTL[next_event >> 2] & POKEY_CH1_FILTER) {
				/* if we're processing channel 3 */
				if ((next_event & 0x03) == POKEY_CHAN3) {
					/* check output of channel 1 on same chip */
					if (Outvol[next_event & 0xfd]) {
						/* if on, turn it off */
						Outvol[next_event & 0xfd] = 0;
#ifdef STEREO_SOUND
#ifdef __PLUS
						if (POKEYSND_stereo_enabled && (next_event & 0x04))
#else
						if ((next_event & 0x04))
#endif
							cur_val2 -= pokeysnd_AUDV[next_event & 0xfd];
						else
#endif /* STEREO_SOUND */
							cur_val -= pokeysnd_AUDV[next_event & 0xfd];
					}
				}
			}

			/* check channel 2 filter (clocked by channel 4) */
			if ( POKEY_AUDCTL[next_event >> 2] & POKEY_CH2_FILTER) {
				/* if we're processing channel 4 */
				if ((next_event & 0x03) == POKEY_CHAN4) {
					/* check output of channel 2 on same chip */
					if (Outvol[next_event & 0xfd]) {
						/* if on, turn it off */
						Outvol[next_event & 0xfd] = 0;
#ifdef STEREO_SOUND
#ifdef __PLUS
						if (POKEYSND_stereo_enabled && (next_event & 0x04))
#else
						if ((next_event & 0x04))
#endif
							cur_val2 -= pokeysnd_AUDV[next_event & 0xfd];
						else
#endif /* STEREO_SOUND */
							cur_val -= pokeysnd_AUDV[next_event & 0xfd];
					}
				}
			}

			/* if the current output bit has changed */
			if (toggle) {
				if (*out_ptr) {
					/* remove this channel from the signal */
#ifdef STEREO_SOUND
#ifdef __PLUS
					if (POKEYSND_stereo_enabled && (next_event & 0x04))
#else
					if ((next_event & 0x04))
#endif
						cur_val2 -= pokeysnd_AUDV[next_event];
					else
#endif /* STEREO_SOUND */
						cur_val -= pokeysnd_AUDV[next_event];

					/* and turn the output off */
					*out_ptr = 0;
				}
				else {
					/* turn the output on */
					*out_ptr = 1;

					/* and add it to the output signal */
#ifdef STEREO_SOUND
#ifdef __PLUS
					if (POKEYSND_stereo_enabled && (next_event & 0x04))
#else
					if ((next_event & 0x04))
#endif
						cur_val2 += pokeysnd_AUDV[next_event];
					else
#endif /* STEREO_SOUND */
						cur_val += pokeysnd_AUDV[next_event];
				}
			}
		}
		else {					/* otherwise we're processing a sample */
			/* adjust the sample counter - note we're using the 24.8 integer
			   which includes an 8 bit fraction for accuracy */

			int iout;
#ifdef STEREO_SOUND
			int iout2;
#endif
#ifdef INTERPOLATE_SOUND
			if (cur_val != last_val) {
				if (*Samp_n_cnt < Samp_n_max) {		/* need interpolation */
					iout = (cur_val * (*Samp_n_cnt) +
							last_val * (Samp_n_max - *Samp_n_cnt))
						/ Samp_n_max;
				}
				else
					iout = cur_val;
				last_val = cur_val;
			}
			else
				iout = cur_val;
#ifdef STEREO_SOUND
#ifdef __PLUS
		if (POKEYSND_stereo_enabled)
#endif
			if (cur_val2 != last_val2) {
				if (*Samp_n_cnt < Samp_n_max) {		/* need interpolation */
					iout2 = (cur_val2 * (*Samp_n_cnt) +
							last_val2 * (Samp_n_max - *Samp_n_cnt))
						/ Samp_n_max;
				}
				else
					iout2 = cur_val2;
				last_val2 = cur_val2;
			}
			else
				iout2 = cur_val2;
#endif  /* STEREO_SOUND */
#else   /* INTERPOLATE_SOUND */
			iout = cur_val;
#ifdef STEREO_SOUND
#ifdef __PLUS
		if (POKEYSND_stereo_enabled)
#endif
			iout2 = cur_val2;
#endif  /* STEREO_SOUND */
#endif  /* INTERPOLATE_SOUND */

#ifdef VOL_ONLY_SOUND
#ifdef __PLUS
			if (g_Sound.nDigitized)
#endif
			{
				if (POKEYSND_sampbuf_rptr != POKEYSND_sampbuf_ptr) {
					int l;
					if (POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_rptr] > 0)
						POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_rptr] -= 1280;
					while ((l = POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_rptr]) <= 0) {
						POKEYSND_sampout = POKEYSND_sampbuf_val[POKEYSND_sampbuf_rptr];
						POKEYSND_sampbuf_rptr++;
						if (POKEYSND_sampbuf_rptr >= POKEYSND_SAMPBUF_MAX)
							POKEYSND_sampbuf_rptr = 0;
						if (POKEYSND_sampbuf_rptr != POKEYSND_sampbuf_ptr)
							POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_rptr] += l;
						else
							break;
					}
				}
				iout += POKEYSND_sampout;
#ifdef STEREO_SOUND
#ifdef __PLUS
				if (POKEYSND_stereo_enabled)
#endif
				{
					if (sampbuf_rptr2 != sampbuf_ptr2) {
						int l;
						if (sampbuf_cnt2[sampbuf_rptr2] > 0)
							sampbuf_cnt2[sampbuf_rptr2] -= 1280;
						while ((l = sampbuf_cnt2[sampbuf_rptr2]) <= 0) {
							sampout2 = sampbuf_val2[sampbuf_rptr2];
							sampbuf_rptr2++;
							if (sampbuf_rptr2 >= POKEYSND_SAMPBUF_MAX)
								sampbuf_rptr2 = 0;
							if (sampbuf_rptr2 != sampbuf_ptr2)
								sampbuf_cnt2[sampbuf_rptr2] += l;
							else
								break;
						}
					}
					iout2 += sampout2;
				}
#endif  /* STEREO_SOUND */
			}
#endif  /* VOL_ONLY_SOUND */

#ifdef CLIP_SOUND
			if (iout > POKEYSND_SAMP_MAX) {	/* then check high limit */
				*buffer++ = (UBYTE) POKEYSND_SAMP_MAX;	/* and limit if greater */
			}
			else if (iout < POKEYSND_SAMP_MIN) {		/* else check low limit */
				*buffer++ = (UBYTE) POKEYSND_SAMP_MIN;	/* and limit if less */
			}
			else {				/* otherwise use raw value */
				*buffer++ = (UBYTE) iout;
			}
#ifdef STEREO_SOUND
#ifdef __PLUS
			if (POKEYSND_stereo_enabled) {
				if (iout2 > POKEYSND_SAMP_MAX)
					*buffer++ = (UBYTE) POKEYSND_SAMP_MAX;
				else if (iout2 < POKEYSND_SAMP_MIN)
					*buffer++ = (UBYTE) POKEYSND_SAMP_MIN;
				else
					*buffer++ = (UBYTE) iout2;
			}
#else /* __PLUS */
			if (Num_pokeys > 1) {
				if ((POKEYSND_stereo_enabled ? iout2 : iout) > POKEYSND_SAMP_MAX) {	/* then check high limit */
					*buffer++ = (UBYTE) POKEYSND_SAMP_MAX;	/* and limit if greater */
				}
				else if ((POKEYSND_stereo_enabled ? iout2 : iout) < POKEYSND_SAMP_MIN) {		/* else check low limit */
					*buffer++ = (UBYTE) POKEYSND_SAMP_MIN;	/* and limit if less */
				}
				else {				/* otherwise use raw value */
					*buffer++ = (UBYTE) (POKEYSND_stereo_enabled ? iout2 : iout);
				}
			}
#endif /* __PLUS */
#endif /* STEREO_SOUND */
#else /* CLIP_SOUND */
			*buffer++ = (UBYTE) iout;	/* clipping not selected, use value */
#ifdef STEREO_SOUND
			if (Num_pokeys > 1)
#ifdef ASAP
				*buffer++ = (UBYTE) iout2;
#else
				*buffer++ = (UBYTE) (POKEYSND_stereo_enabled ? iout2 : iout);
#endif
#endif /* STEREO_SOUND */
#endif /* CLIP_SOUND */

#ifdef WORDS_BIGENDIAN
			*(Samp_n_cnt + 1) += Samp_n_max;
#else
			*Samp_n_cnt += Samp_n_max;
#endif
			/* and indicate one less byte in the buffer */
			n--;
#ifdef STEREO_SOUND
#ifdef __PLUS
			if (POKEYSND_stereo_enabled)
#endif
			if (Num_pokeys > 1)
				n--;
#endif
		}
	}
#ifdef VOL_ONLY_SOUND
#ifdef __PLUS
	if (g_Sound.nDigitized)
#endif
	{
		if (POKEYSND_sampbuf_rptr == POKEYSND_sampbuf_ptr)
			POKEYSND_sampbuf_last = ANTIC_CPU_CLOCK;
#ifdef STEREO_SOUND
#ifdef __PLUS
	if (POKEYSND_stereo_enabled)
#endif
		if (sampbuf_rptr2 == sampbuf_ptr2)
			sampbuf_last2 = ANTIC_CPU_CLOCK;
#endif /* STEREO_SOUND */
	}
#endif  /* VOL_ONLY_SOUND */
}