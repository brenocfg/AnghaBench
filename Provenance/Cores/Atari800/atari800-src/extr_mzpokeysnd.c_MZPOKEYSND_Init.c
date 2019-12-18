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
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int POKEYSND_BIT16 ; 
 int /*<<< orphan*/  POKEYSND_Process_ptr ; 
 int /*<<< orphan*/  POKEYSND_UpdateConsol_ptr ; 
 int /*<<< orphan*/  POKEYSND_UpdateSerio ; 
 int /*<<< orphan*/  POKEYSND_UpdateVolOnly ; 
 int /*<<< orphan*/  POKEYSND_Update_ptr ; 
 double POKEYSND_playback_freq ; 
 int POKEYSND_samp_freq ; 
 int /*<<< orphan*/  ResetPokeyState (scalar_t__) ; 
 int /*<<< orphan*/  Update_consol_sound_mz ; 
 int /*<<< orphan*/  Update_pokey_sound_mz ; 
 int /*<<< orphan*/  Update_serio_sound_mz ; 
 int /*<<< orphan*/  Update_vol_only_sound_mz ; 
 int audible_frq ; 
 int /*<<< orphan*/  build_poly17 () ; 
 int /*<<< orphan*/  build_poly4 () ; 
 int /*<<< orphan*/  build_poly5 () ; 
 int /*<<< orphan*/  build_poly9 () ; 
 int /*<<< orphan*/  filter_11 ; 
 int /*<<< orphan*/  filter_11_8 ; 
 int /*<<< orphan*/  filter_22 ; 
 int /*<<< orphan*/  filter_22_8 ; 
 int /*<<< orphan*/  filter_44 ; 
 int /*<<< orphan*/  filter_44_8 ; 
 int /*<<< orphan*/  filter_48 ; 
 int /*<<< orphan*/  filter_48_8 ; 
 int /*<<< orphan*/  filter_8 ; 
 int /*<<< orphan*/  filter_8_8 ; 
 int /*<<< orphan*/  filter_data ; 
 int /*<<< orphan*/  filter_size ; 
 int /*<<< orphan*/  filter_size_11 ; 
 int /*<<< orphan*/  filter_size_11_8 ; 
 int /*<<< orphan*/  filter_size_22 ; 
 int /*<<< orphan*/  filter_size_22_8 ; 
 int /*<<< orphan*/  filter_size_44 ; 
 int /*<<< orphan*/  filter_size_44_8 ; 
 int /*<<< orphan*/  filter_size_48 ; 
 int /*<<< orphan*/  filter_size_48_8 ; 
 int /*<<< orphan*/  filter_size_8 ; 
 int /*<<< orphan*/  filter_size_8_8 ; 
 int /*<<< orphan*/  init_syncsound () ; 
 int /*<<< orphan*/  mzpokeysnd_process_16 ; 
 int /*<<< orphan*/  mzpokeysnd_process_8 ; 
 int /*<<< orphan*/  num_cur_pokeys ; 
 double pokey_frq ; 
 scalar_t__ pokey_frq_ideal ; 
 scalar_t__ pokey_states ; 
 int /*<<< orphan*/  remez_filter_table (double,double*,int) ; 
 int snd_quality ; 

int MZPOKEYSND_Init(ULONG freq17, int playback_freq, UBYTE num_pokeys,
                        int flags, int quality
#ifdef __PLUS
                        , int clear_regs
#endif
                       )
{
    double cutoff;

    snd_quality = quality;

    POKEYSND_Update_ptr = Update_pokey_sound_mz;
#ifdef SERIO_SOUND
    POKEYSND_UpdateSerio = Update_serio_sound_mz;
#endif
#ifdef CONSOLE_SOUND
    POKEYSND_UpdateConsol_ptr = Update_consol_sound_mz;
#endif
#ifdef VOL_ONLY_SOUND
    POKEYSND_UpdateVolOnly = Update_vol_only_sound_mz;
#endif

#ifdef VOL_ONLY_SOUND
	POKEYSND_samp_freq=playback_freq;
#endif  /* VOL_ONLY_SOUND */

	POKEYSND_Process_ptr = (flags & POKEYSND_BIT16) ? mzpokeysnd_process_16 : mzpokeysnd_process_8;

    switch(playback_freq)
    {
#if 0
    case 44100:
        if(flags & POKEYSND_BIT16)
        {
            filter_data = filter_44;
            filter_size = filter_size_44;
        }
        else
        {
            filter_data = filter_44_8;
            filter_size = filter_size_44_8;
        }
        pokey_frq = 1808100; /* 1.02% off ideal */
        audible_frq = 20000; /* ultrasound */
        break;
    case 22050:
        if(flags & POKEYSND_BIT16)
        {
            filter_data = filter_22;
            filter_size = filter_size_22;
        }
        else
        {
            filter_data = filter_22_8;
            filter_size = filter_size_22_8;
        }
        pokey_frq = 1786050; /* 0.2% off ideal */
        audible_frq = 10000; /* 30db filter attenuation */
        break;
    case 11025:
        if(flags & POKEYSND_BIT16)
        {
            filter_data = filter_11;
            filter_size = filter_size_11;
        }
        else
        {
            filter_data = filter_11_8;
            filter_size = filter_size_11_8;
        }
        pokey_frq = 1786050; /* 0.2% off ideal */
        audible_frq = 4500; /* 30db filter attenuation */
        break;
    case 48000:
        if(flags & POKEYSND_BIT16)
        {
            filter_data = filter_48;
            filter_size = filter_size_48;
        }
        else
        {
            filter_data = filter_48_8;
            filter_size = filter_size_48_8;
        }
        pokey_frq = 1776000; /* 0.7% off ideal */
        audible_frq = 20000; /* ultrasound */
        break;
    case 8000:
        if(flags & POKEYSND_BIT16)
        {
            filter_data = filter_8;
            filter_size = filter_size_8;
        }
        else
        {
            filter_data = filter_8_8;
            filter_size = filter_size_8_8;
        }
        pokey_frq = 1792000; /* 0.1% off ideal */
        audible_frq = 4000; /* Nyquist, also 30db attn, should be 50 */
        break;
#endif
    default:
        pokey_frq = (int)(((double)pokey_frq_ideal/POKEYSND_playback_freq) + 0.5)
          * POKEYSND_playback_freq;
	filter_size = remez_filter_table((double)POKEYSND_playback_freq/pokey_frq,
					 &cutoff, quality);
	audible_frq = (int ) (cutoff * pokey_frq);
    }

    build_poly4();
    build_poly5();
    build_poly9();
    build_poly17();

#ifdef __PLUS
	if (clear_regs)
#endif
	{
		ResetPokeyState(pokey_states);
		ResetPokeyState(pokey_states + 1);
	}
	num_cur_pokeys = num_pokeys;

#ifdef SYNCHRONIZED_SOUND
	init_syncsound();
#endif
	return 0; /* OK */
}