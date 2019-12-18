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

__attribute__((used)) static void freq_to_fnum    (int freq, int *block, int *fnum)
{
	int f, octave;

	/*
	 * Converts the note frequency to block and fnum values for the FM chip
	 */
	/*
	 * First try to compute the block -value (octave) where the note belongs
	 */

	f = freq;

	octave = 5;

	if (f == 0)
		octave = 0;
	else if (f < 261)
	{
		while (f < 261)
		{
			octave--;
			f <<= 1;
		}
	}
	else if (f > 493)
	{
		while (f > 493)
		{
			 octave++;
			 f >>= 1;
		}
	}

	if (octave > 7)
		octave = 7;

	*fnum = freq * (1 << (20 - octave)) / 49716;
	*block = octave;
}