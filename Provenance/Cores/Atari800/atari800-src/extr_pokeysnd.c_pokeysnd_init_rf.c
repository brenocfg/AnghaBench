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
typedef  int ULONG ;
typedef  int UBYTE ;

/* Variables and functions */
 scalar_t__* Div_n_cnt ; 
 int* Div_n_max ; 
 int Num_pokeys ; 
 scalar_t__* Outbit ; 
 scalar_t__* Outvol ; 
 scalar_t__ P17 ; 
 scalar_t__ P4 ; 
 scalar_t__ P5 ; 
 scalar_t__ P9 ; 
 int POKEYSND_BIT16 ; 
 int /*<<< orphan*/  POKEYSND_Process_ptr ; 
 int /*<<< orphan*/  POKEYSND_UpdateConsol_ptr ; 
 int /*<<< orphan*/  POKEYSND_UpdateSerio ; 
 int /*<<< orphan*/  POKEYSND_UpdateVolOnly ; 
 int /*<<< orphan*/  POKEYSND_Update_ptr ; 
 int POKEYSND_samp_freq ; 
 scalar_t__* POKEYSND_sampbuf_AUDV ; 
 int POKEY_MAXPOKEYS ; 
 scalar_t__* Samp_n_cnt ; 
 int Samp_n_max ; 
 int /*<<< orphan*/  Update_consol_sound_rf ; 
 int /*<<< orphan*/  Update_pokey_sound_rf ; 
 int /*<<< orphan*/  Update_serio_sound_rf ; 
 int /*<<< orphan*/  Update_vol_only_sound_rf ; 
 int /*<<< orphan*/  init_syncsound () ; 
 scalar_t__* pokeysnd_AUDV ; 
 int /*<<< orphan*/  pokeysnd_process_16 ; 
 int /*<<< orphan*/  pokeysnd_process_8 ; 

__attribute__((used)) static int pokeysnd_init_rf(ULONG freq17, int playback_freq,
           UBYTE num_pokeys, int flags)
{
	UBYTE chan;

	POKEYSND_Update_ptr = Update_pokey_sound_rf;
#ifdef SERIO_SOUND
	POKEYSND_UpdateSerio = Update_serio_sound_rf;
#endif
#ifdef CONSOLE_SOUND
	POKEYSND_UpdateConsol_ptr = Update_consol_sound_rf;
#endif
#ifdef VOL_ONLY_SOUND
	POKEYSND_UpdateVolOnly = Update_vol_only_sound_rf;
#endif

	POKEYSND_Process_ptr = (flags & POKEYSND_BIT16) ? pokeysnd_process_16 : pokeysnd_process_8;

#ifdef VOL_ONLY_SOUND
	POKEYSND_samp_freq = playback_freq;
#endif

	/* start all of the polynomial counters at zero */
	P4 = 0;
	P5 = 0;
	P9 = 0;
	P17 = 0;

	/* calculate the sample 'divide by N' value based on the playback freq. */
	Samp_n_max = ((ULONG) freq17 << 8) / playback_freq;

	Samp_n_cnt[0] = 0;			/* initialize all bits of the sample */
	Samp_n_cnt[1] = 0;			/* 'divide by N' counter */

	for (chan = 0; chan < (POKEY_MAXPOKEYS * 4); chan++) {
		Outvol[chan] = 0;
		Outbit[chan] = 0;
		Div_n_cnt[chan] = 0;
		Div_n_max[chan] = 0x7fffffffL;
		pokeysnd_AUDV[chan] = 0;
#ifdef VOL_ONLY_SOUND
		POKEYSND_sampbuf_AUDV[chan] = 0;
#endif
	}

	/* set the number of pokey chips currently emulated */
	Num_pokeys = num_pokeys;

#ifdef SYNCHRONIZED_SOUND
	init_syncsound();
#endif
	return 0; /* OK */
}