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
 unsigned int ADCCR_SAMPLERATE_11 ; 
 unsigned int ADCCR_SAMPLERATE_16 ; 
 unsigned int ADCCR_SAMPLERATE_22 ; 
 unsigned int ADCCR_SAMPLERATE_24 ; 
 unsigned int ADCCR_SAMPLERATE_32 ; 
 unsigned int ADCCR_SAMPLERATE_44 ; 
 unsigned int ADCCR_SAMPLERATE_48 ; 
 unsigned int ADCCR_SAMPLERATE_8 ; 
 int /*<<< orphan*/  snd_BUG () ; 

__attribute__((used)) static unsigned int snd_emu10k1_capture_rate_reg(unsigned int rate)
{
	switch (rate) {
	case 8000:	return ADCCR_SAMPLERATE_8;
	case 11025:	return ADCCR_SAMPLERATE_11;
	case 16000:	return ADCCR_SAMPLERATE_16;
	case 22050:	return ADCCR_SAMPLERATE_22;
	case 24000:	return ADCCR_SAMPLERATE_24;
	case 32000:	return ADCCR_SAMPLERATE_32;
	case 44100:	return ADCCR_SAMPLERATE_44;
	case 48000:	return ADCCR_SAMPLERATE_48;
	default:
			snd_BUG();
			return ADCCR_SAMPLERATE_8;
	}
}