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
 int* cent_tuning ; 
 int* semitone_tuning ; 

unsigned long compute_finetune(unsigned long base_freq, int bend, int range,
		 int vibrato_cents)
{
	unsigned long amount;
	int negative, semitones, cents, multiplier = 1;

	if (!bend)
		return base_freq;
	if (!range)
		return base_freq;

	if (!base_freq)
		return base_freq;

	if (range >= 8192)
		range = 8192;

	bend = bend * range / 8192;	/* Convert to cents */
	bend += vibrato_cents;

	if (!bend)
		return base_freq;

	negative = bend < 0 ? 1 : 0;

	if (bend < 0)
		bend *= -1;
	if (bend > range)
		bend = range;

	/*
	   if (bend > 2399)
	   bend = 2399;
	 */
	while (bend > 2399)
	{
		multiplier *= 4;
		bend -= 2400;
	}

	semitones = bend / 100;
	if (semitones > 99)
		semitones = 99;
	cents = bend % 100;

	amount = (int) (semitone_tuning[semitones] * multiplier * cent_tuning[cents]) / 10000;

	if (negative)
		return (base_freq * 10000) / amount;	/* Bend down */
	else
		return (base_freq * amount) / 10000;	/* Bend up */
}