#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_4__ {double freqbase; double rate; scalar_t__ clock; } ;
struct TYPE_5__ {int eg_timer_add; double* lfo_freq; TYPE_1__ ST; } ;
struct TYPE_6__ {TYPE_2__ OPN; } ;

/* Variables and functions */
 int EG_SH ; 
 int FREQ_SH ; 
 int LFO_SH ; 
 int /*<<< orphan*/  dt_tab ; 
 scalar_t__* fn_table ; 
 int /*<<< orphan*/  init_timetables (int /*<<< orphan*/ ) ; 
 double* lfo_samples_per_step ; 
 TYPE_3__ ym2612 ; 

__attribute__((used)) static void OPNSetPres(int pres)
{
	int i;

	/* frequency base */
	ym2612.OPN.ST.freqbase = (ym2612.OPN.ST.rate) ? ((double)ym2612.OPN.ST.clock / ym2612.OPN.ST.rate) / pres : 0;

	ym2612.OPN.eg_timer_add  = (1<<EG_SH) * ym2612.OPN.ST.freqbase;

	/* make time tables */
	init_timetables( dt_tab );

	/* there are 2048 FNUMs that can be generated using FNUM/BLK registers
        but LFO works with one more bit of a precision so we really need 4096 elements */
	/* calculate fnumber -> increment counter table */
	for(i = 0; i < 4096; i++)
	{
		/* freq table for octave 7 */
		/* OPN phase increment counter = 20bit */
		fn_table[i] = (UINT32)( (double)i * 32 * ym2612.OPN.ST.freqbase * (1<<(FREQ_SH-10)) ); /* -10 because chip works with 10.10 fixed point, while we use 16.16 */
	}

	/* LFO freq. table */
	for(i = 0; i < 8; i++)
	{
		/* Amplitude modulation: 64 output levels (triangle waveform); 1 level lasts for one of "lfo_samples_per_step" samples */
		/* Phase modulation: one entry from lfo_pm_output lasts for one of 4 * "lfo_samples_per_step" samples  */
		ym2612.OPN.lfo_freq[i] = (1.0 / lfo_samples_per_step[i]) * (1<<LFO_SH) * ym2612.OPN.ST.freqbase;
	}
}