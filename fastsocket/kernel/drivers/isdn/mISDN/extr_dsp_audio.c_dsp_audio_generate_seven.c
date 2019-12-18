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
typedef  size_t u8 ;

/* Variables and functions */
 int DSP_OPT_ULAW ; 
 scalar_t__* dsp_audio_alaw_to_s32 ; 
 size_t* dsp_audio_alaw_to_ulaw ; 
 int* dsp_audio_law2seven ; 
 size_t* dsp_audio_seven2law ; 
 size_t* dsp_audio_ulaw_to_alaw ; 
 int dsp_options ; 

void
dsp_audio_generate_seven(void)
{
	int i, j, k;
	u8 spl;
	u8 sorted_alaw[256];

	/* generate alaw table, sorted by the linear value */
	for (i = 0; i < 256; i++) {
		j = 0;
		for (k = 0; k < 256; k++) {
			if (dsp_audio_alaw_to_s32[k]
			    < dsp_audio_alaw_to_s32[i])
				j++;
		}
		sorted_alaw[j] = i;
	}

	/* generate tabels */
	for (i = 0; i < 256; i++) {
		/* spl is the source: the law-sample (converted to alaw) */
		spl = i;
		if (dsp_options & DSP_OPT_ULAW)
			spl = dsp_audio_ulaw_to_alaw[i];
		/* find the 7-bit-sample */
		for (j = 0; j < 256; j++) {
			if (sorted_alaw[j] == spl)
				break;
		}
		/* write 7-bit audio value */
		dsp_audio_law2seven[i] = j >> 1;
	}
	for (i = 0; i < 128; i++) {
		spl = sorted_alaw[i << 1];
		if (dsp_options & DSP_OPT_ULAW)
			spl = dsp_audio_alaw_to_ulaw[spl];
		dsp_audio_seven2law[i] = spl;
	}
}