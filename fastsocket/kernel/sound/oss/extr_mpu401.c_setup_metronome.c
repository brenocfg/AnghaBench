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
 scalar_t__ metronome_mode ; 
 int /*<<< orphan*/  mpu_cmd (int,int,int) ; 

__attribute__((used)) static void setup_metronome(int midi_dev)
{
	int numerator, denominator;
	int clks_per_click, num_32nds_per_beat;
	int beats_per_measure;

	numerator = ((unsigned) metronome_mode >> 24) & 0xff;
	denominator = ((unsigned) metronome_mode >> 16) & 0xff;
	clks_per_click = ((unsigned) metronome_mode >> 8) & 0xff;
	num_32nds_per_beat = (unsigned) metronome_mode & 0xff;
	beats_per_measure = (numerator * 4) >> denominator;

	if (!metronome_mode)
		mpu_cmd(midi_dev, 0x84, 0);	/* Disable metronome */
	else
	{
		mpu_cmd(midi_dev, 0xE4, clks_per_click);
		mpu_cmd(midi_dev, 0xE6, beats_per_measure);
		mpu_cmd(midi_dev, 0x83, 0);	/* Enable metronome without accents */
	}
}