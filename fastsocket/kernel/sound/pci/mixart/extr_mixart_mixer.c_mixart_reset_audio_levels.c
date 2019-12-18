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
struct snd_mixart {int chip_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mixart_update_analog_audio_level (struct snd_mixart*,int) ; 

__attribute__((used)) static void mixart_reset_audio_levels(struct snd_mixart *chip)
{
	/* analog volumes can be set even if there is no pipe */
	mixart_update_analog_audio_level(chip, 0);
	/* analog levels for capture only on the first two chips */
	if(chip->chip_idx < 2) {
		mixart_update_analog_audio_level(chip, 1);
	}
	return;
}