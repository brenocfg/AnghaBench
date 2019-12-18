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
struct TYPE_2__ {int speaker; int forcero; } ;

/* Variables and functions */
 unsigned int ANTIC_CPU_CLOCK ; 
 int CONSOLE_VOL ; 
 int GTIA_speaker ; 
 size_t POKEYSND_SAMPBUF_MAX ; 
 int POKEYSND_samp_consol_val ; 
 unsigned int POKEYSND_samp_freq ; 
 unsigned int* POKEYSND_sampbuf_cnt ; 
 unsigned int POKEYSND_sampbuf_last ; 
 int POKEYSND_sampbuf_lastval ; 
 size_t POKEYSND_sampbuf_ptr ; 
 size_t POKEYSND_sampbuf_rptr ; 
 int* POKEYSND_sampbuf_val ; 
 TYPE_1__* pokey_states ; 

__attribute__((used)) static void Update_consol_sound_mz( int set )
{
#ifdef SYNCHRONIZED_SOUND
	if (set) { /* The set variable is 0 only in VOL_ONLY_SOUND routines */
		pokey_states[0].speaker = GTIA_speaker*CONSOLE_VOL;
		pokey_states[0].forcero = 1; /* first chip */
	}
#elif defined(VOL_ONLY_SOUND)
	static int prev_atari_speaker=0;
	static unsigned int prev_cpu_clock=0;
	int d;

	if( !set && POKEYSND_samp_consol_val==0 )	return;
	POKEYSND_sampbuf_lastval-=POKEYSND_samp_consol_val;
	if( prev_atari_speaker!=GTIA_speaker )
	{	POKEYSND_samp_consol_val=GTIA_speaker*8*4;	/* gain */
		prev_cpu_clock=ANTIC_CPU_CLOCK;
	}
	else if( !set )
	{	d=ANTIC_CPU_CLOCK - prev_cpu_clock;
		if( d<114 )
		{	POKEYSND_sampbuf_lastval+=POKEYSND_samp_consol_val;   return;	}
		while( d>=114 /* CPUL */ )
		{	POKEYSND_samp_consol_val=POKEYSND_samp_consol_val*99/100;
			d-=114;
		}
		prev_cpu_clock=ANTIC_CPU_CLOCK-d;
	}
	POKEYSND_sampbuf_lastval+=POKEYSND_samp_consol_val;
	prev_atari_speaker=GTIA_speaker;

	POKEYSND_sampbuf_val[POKEYSND_sampbuf_ptr]=POKEYSND_sampbuf_lastval;
	POKEYSND_sampbuf_cnt[POKEYSND_sampbuf_ptr]=
		(ANTIC_CPU_CLOCK-POKEYSND_sampbuf_last)*128*POKEYSND_samp_freq/178979;
	POKEYSND_sampbuf_last=ANTIC_CPU_CLOCK;
	POKEYSND_sampbuf_ptr++;
	if( POKEYSND_sampbuf_ptr>=POKEYSND_SAMPBUF_MAX )
		POKEYSND_sampbuf_ptr=0;
	if( POKEYSND_sampbuf_ptr==POKEYSND_sampbuf_rptr )
	{	POKEYSND_sampbuf_rptr++;
		if( POKEYSND_sampbuf_rptr>=POKEYSND_SAMPBUF_MAX )
			POKEYSND_sampbuf_rptr=0;
	}
#endif  /* !SYNCHRONIZED_SOUND && VOL_ONLY_SOUND */
}