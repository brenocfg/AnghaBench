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
struct snd_pcm_substream {scalar_t__ number; } ;
struct snd_es18xx {int caps; int active; int dma2_shift; int dma1_shift; int /*<<< orphan*/  dma1_size; int /*<<< orphan*/  dma1; int /*<<< orphan*/  dma2_size; int /*<<< orphan*/  dma2; } ;
typedef  int snd_pcm_uframes_t ;

/* Variables and functions */
 int DAC1 ; 
 int DAC2 ; 
 int ES18XX_PCM2 ; 
 int snd_dma_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_es18xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static snd_pcm_uframes_t snd_es18xx_playback_pointer(struct snd_pcm_substream *substream)
{
        struct snd_es18xx *chip = snd_pcm_substream_chip(substream);
	int pos;

	if (substream->number == 0 && (chip->caps & ES18XX_PCM2)) {
		if (!(chip->active & DAC2))
			return 0;
		pos = snd_dma_pointer(chip->dma2, chip->dma2_size);
		return pos >> chip->dma2_shift;
	} else {
		if (!(chip->active & DAC1))
			return 0;
		pos = snd_dma_pointer(chip->dma1, chip->dma1_size);
		return pos >> chip->dma1_shift;
	}
}