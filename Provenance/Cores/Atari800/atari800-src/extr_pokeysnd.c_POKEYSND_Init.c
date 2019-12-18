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
typedef  int /*<<< orphan*/  ULONG ;
typedef  unsigned int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ANTIC_CPU_CLOCK ; 
 double Atari800_FPS_NTSC ; 
 double Atari800_FPS_PAL ; 
 int Atari800_TV_PAL ; 
 int Atari800_tv_mode ; 
 int POKEYSND_BIT16 ; 
 int POKEYSND_DoInit () ; 
 unsigned int POKEYSND_num_pokeys ; 
 int POKEYSND_playback_freq ; 
 unsigned int* POKEYSND_process_buffer ; 
 scalar_t__ POKEYSND_process_buffer_fill ; 
 unsigned int POKEYSND_process_buffer_length ; 
 int POKEYSND_snd_flags ; 
 scalar_t__ Util_malloc (unsigned int) ; 
 int /*<<< orphan*/  VOTRAXSND_Init (int,unsigned int,int) ; 
 scalar_t__ ceil (double) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 int mz_clear_regs ; 
 int /*<<< orphan*/  prev_update_tick ; 
 int /*<<< orphan*/  snd_freq17 ; 

int POKEYSND_Init(ULONG freq17, int playback_freq, UBYTE num_pokeys,
                     int flags
#ifdef __PLUS
                     , int clear_regs
#endif
)
{
	snd_freq17 = freq17;
	POKEYSND_playback_freq = playback_freq;
	POKEYSND_num_pokeys = num_pokeys;
	POKEYSND_snd_flags = flags;
#ifdef __PLUS
	mz_clear_regs = clear_regs;
#endif
#ifdef SYNCHRONIZED_SOUND
	{
		/* A single call to Atari800_Frame may emulate a bit more CPU ticks than the exact number of
		   ticks per frame (Atari800_tv_mode*114). So we add a few ticks to buffer size just to be safe. */
		unsigned int const surplus_ticks = 10;
		double samples_per_frame = (double)POKEYSND_playback_freq/(Atari800_tv_mode == Atari800_TV_PAL ? Atari800_FPS_PAL : Atari800_FPS_NTSC);
		unsigned int ticks_per_frame = Atari800_tv_mode*114;
		unsigned int max_ticks_per_frame = ticks_per_frame + surplus_ticks;
		double ticks_per_sample = (double)ticks_per_frame / samples_per_frame;
		POKEYSND_process_buffer_length = POKEYSND_num_pokeys * (unsigned int)ceil((double)max_ticks_per_frame / ticks_per_sample) * ((POKEYSND_snd_flags & POKEYSND_BIT16) ? 2:1);
		free(POKEYSND_process_buffer);
		POKEYSND_process_buffer = (UBYTE *)Util_malloc(POKEYSND_process_buffer_length);
		POKEYSND_process_buffer_fill = 0;
	    prev_update_tick = ANTIC_CPU_CLOCK;
	}
#endif /* SYNCHRONIZED_SOUND */

#if defined(PBI_XLD) || defined (VOICEBOX)
	VOTRAXSND_Init(playback_freq, num_pokeys, (flags & POKEYSND_BIT16));
#endif
	return POKEYSND_DoInit();
}