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
typedef  scalar_t__ UINT32 ;
struct TYPE_2__ {double lfo_am_inc; double lfo_pm_inc; double noise_f; int eg_timer_add; int eg_timer_overflow; scalar_t__* fn_tab; } ;

/* Variables and functions */
 int EG_SH ; 
 int FREQ_SH ; 
 int LFO_SH ; 
 TYPE_1__ ym2413 ; 

__attribute__((used)) static void OPLL_initalize(void)
{
  int i;

  /* YM2413 always running at original frequency */
  double freqbase = 1.0;

  /* make fnumber -> increment counter table */
  for( i = 0 ; i < 1024; i++ )
  {
    /* OPLL (YM2413) phase increment counter = 18bit */
    ym2413.fn_tab[i] = (UINT32)( (double)i * 64 * freqbase * (1<<(FREQ_SH-10)) ); /* -10 because chip works with 10.10 fixed point, while we use 16.16 */
  }

  /* Amplitude modulation: 27 output levels (triangle waveform); 1 level takes one of: 192, 256 or 448 samples */
  /* One entry from LFO_AM_TABLE lasts for 64 samples */
  ym2413.lfo_am_inc = (1.0 / 64.0 ) * (1<<LFO_SH) * freqbase;

  /* Vibrato: 8 output levels (triangle waveform); 1 level takes 1024 samples */
  ym2413.lfo_pm_inc = (1.0 / 1024.0) * (1<<LFO_SH) * freqbase;

  /* Noise generator: a step takes 1 sample */
  ym2413.noise_f = (1.0 / 1.0) * (1<<FREQ_SH) * freqbase;

  ym2413.eg_timer_add  = (1<<EG_SH) * freqbase;
  ym2413.eg_timer_overflow = ( 1 ) * (1<<EG_SH);
}