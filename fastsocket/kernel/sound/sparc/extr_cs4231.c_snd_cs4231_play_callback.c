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
struct snd_cs4231 {int* image; int /*<<< orphan*/  p_periods_sent; int /*<<< orphan*/  playback_substream; int /*<<< orphan*/  p_dma; } ;

/* Variables and functions */
 size_t CS4231_IFACE_CTRL ; 
 int CS4231_PLAYBACK_ENABLE ; 
 int /*<<< orphan*/  snd_cs4231_advance_dma (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void snd_cs4231_play_callback(struct snd_cs4231 *chip)
{
	if (chip->image[CS4231_IFACE_CTRL] & CS4231_PLAYBACK_ENABLE) {
		snd_pcm_period_elapsed(chip->playback_substream);
		snd_cs4231_advance_dma(&chip->p_dma, chip->playback_substream,
					    &chip->p_periods_sent);
	}
}