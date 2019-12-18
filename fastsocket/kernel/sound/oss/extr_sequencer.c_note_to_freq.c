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
 int BASE_OCTAVE ; 

int note_to_freq(int note_num)
{

	/*
	 * This routine converts a midi note to a frequency (multiplied by 1000)
	 */

	int note, octave, note_freq;
	static int notes[] =
	{
		261632, 277189, 293671, 311132, 329632, 349232,
		369998, 391998, 415306, 440000, 466162, 493880
	};

#define BASE_OCTAVE	5

	octave = note_num / 12;
	note = note_num % 12;

	note_freq = notes[note];

	if (octave < BASE_OCTAVE)
		note_freq >>= (BASE_OCTAVE - octave);
	else if (octave > BASE_OCTAVE)
		note_freq <<= (octave - BASE_OCTAVE);

	/*
	 * note_freq >>= 1;
	 */

	return note_freq;
}