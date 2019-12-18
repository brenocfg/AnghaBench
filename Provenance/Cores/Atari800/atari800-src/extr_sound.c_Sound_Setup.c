#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int freq; unsigned int frag_frames; int channels; int sample_size; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  Log_print (char*,int) ; 
 int MAX_CHANNELS ; 
 int /*<<< orphan*/  PLATFORM_SoundSetup (TYPE_1__*) ; 
 int /*<<< orphan*/  POKEYSND_BIT16 ; 
 int /*<<< orphan*/  POKEYSND_FREQ_17_EXACT ; 
 int /*<<< orphan*/  POKEYSND_Init (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ POKEYSND_enable_new_pokey ; 
 int POKEYSND_stereo_enabled ; 
 int /*<<< orphan*/  Sound_Exit () ; 
 int /*<<< orphan*/  Sound_SetLatency (int /*<<< orphan*/ ) ; 
 TYPE_1__ Sound_desired ; 
 int /*<<< orphan*/  Sound_enabled ; 
 int /*<<< orphan*/  Sound_latency ; 
 TYPE_1__ Sound_out ; 
 int TRUE ; 
 int /*<<< orphan*/  Util_malloc (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int paused ; 
 int /*<<< orphan*/  process_buffer ; 
 int process_buffer_size ; 

int Sound_Setup(void)
{
	/* Sanitize freq. */
	if (POKEYSND_enable_new_pokey && Sound_desired.freq < 8192)
		/* MZ POKEY seems to segfault or remain silent with rate < 8009 Hz. */
		Sound_desired.freq = 8192;
	else if (Sound_desired.freq < 1000)
		/* Such low value is impractical. */
		Sound_desired.freq = 1000;
	else if (Sound_desired.freq > 65535)
		/* POKEY emulation doesn't support rate > 65535 Hz. */
		Sound_desired.freq = 65535;

	/* 0 indicates setting frag_size automatically. */
	if (Sound_desired.frag_frames != 0) {
		/* Make sure frag_frames is a power of 2. */
		unsigned int pow_val = 1;
		unsigned int val = Sound_desired.frag_frames;
		while (val >>= 1)
			pow_val <<= 1;
		if (pow_val < Sound_desired.frag_frames)
			pow_val <<= 1;
		Sound_desired.frag_frames = pow_val;

		if (Sound_desired.frag_frames < 16)
			/* Lower values are simply not practical. */
			Sound_desired.frag_frames = 16;
	}

	Sound_out = Sound_desired;
	if (!(Sound_enabled = PLATFORM_SoundSetup(&Sound_out)))
		return FALSE;

	/* Now setup contains actual audio output settings. */
	if ((POKEYSND_enable_new_pokey && Sound_out.freq < 8192)
		|| Sound_out.freq < 1000 || Sound_out.freq > 65535) {
		Log_print("%d frequency not supported", Sound_out.freq);
		Sound_Exit();
		return FALSE;
	}
	if (Sound_out.channels > MAX_CHANNELS) {
		Log_print("%d channels not supported", Sound_out.channels);
		Sound_Exit();
		return FALSE;
	}

	POKEYSND_stereo_enabled = Sound_out.channels == 2;
#ifndef SOUND_CALLBACK
	free(process_buffer);
	process_buffer_size = Sound_out.frag_frames * Sound_out.channels * Sound_out.sample_size;
	process_buffer = Util_malloc(process_buffer_size);
#endif /* !SOUND_CALLBACK */

	POKEYSND_Init(POKEYSND_FREQ_17_EXACT, Sound_out.freq, Sound_out.channels, Sound_out.sample_size == 2 ? POKEYSND_BIT16 : 0);

#ifdef SYNCHRONIZED_SOUND
	Sound_SetLatency(Sound_latency);
#endif /* SYNCHRONIZED_SOUND */

	Sound_desired.freq = Sound_out.freq;
	Sound_desired.sample_size = Sound_out.sample_size;
	Sound_desired.channels = Sound_out.channels;
	/* Don't copy Sound_out.frag_frames to Sound_desired.frag_frames.
       Reason: some backends (e.g. SDL on PulseAudio) always
	   decrease the desired frag_size when opening audio. If the
	   obtained value was copied, repeated calls to Sound_Setup
	   would quickly decrease frag_size to 0. */

	paused = TRUE;
	return TRUE;
}