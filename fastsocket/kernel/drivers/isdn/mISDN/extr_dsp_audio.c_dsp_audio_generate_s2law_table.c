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

/* Variables and functions */
 int DSP_OPT_ULAW ; 
 int /*<<< orphan*/ * dsp_audio_s16_to_law ; 
 int dsp_options ; 
 int /*<<< orphan*/  linear2alaw (int) ; 
 int /*<<< orphan*/  linear2ulaw (int) ; 
 int /*<<< orphan*/  reverse_bits (int /*<<< orphan*/ ) ; 

void
dsp_audio_generate_s2law_table(void)
{
	int i;

	if (dsp_options & DSP_OPT_ULAW) {
		/* generating ulaw-table */
		for (i = -32768; i < 32768; i++) {
			dsp_audio_s16_to_law[i & 0xffff] =
				reverse_bits(linear2ulaw(i));
		}
	} else {
		/* generating alaw-table */
		for (i = -32768; i < 32768; i++) {
			dsp_audio_s16_to_law[i & 0xffff] =
				reverse_bits(linear2alaw(i));
		}
	}
}