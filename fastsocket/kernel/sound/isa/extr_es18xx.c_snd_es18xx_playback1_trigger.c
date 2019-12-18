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
struct snd_pcm_substream {int dummy; } ;
struct snd_es18xx {int active; int dma2; int caps; int audio2_vol; } ;

/* Variables and functions */
 int DAC2 ; 
 int EINVAL ; 
 int ES18XX_PCM2 ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  snd_es18xx_dsp_command (struct snd_es18xx*,int) ; 
 int /*<<< orphan*/  snd_es18xx_mixer_write (struct snd_es18xx*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_es18xx_playback1_trigger(struct snd_es18xx *chip,
					struct snd_pcm_substream *substream,
					int cmd)
{
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		if (chip->active & DAC2)
			return 0;
		chip->active |= DAC2;
                /* Start DMA */
		if (chip->dma2 >= 4)
			snd_es18xx_mixer_write(chip, 0x78, 0xb3);
		else
			snd_es18xx_mixer_write(chip, 0x78, 0x93);
#ifdef AVOID_POPS
		/* Avoid pops */
                udelay(100000);
		if (chip->caps & ES18XX_PCM2)
			/* Restore Audio 2 volume */
			snd_es18xx_mixer_write(chip, 0x7C, chip->audio2_vol);
		else
			/* Enable PCM output */
			snd_es18xx_dsp_command(chip, 0xD1);
#endif
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		if (!(chip->active & DAC2))
			return 0;
		chip->active &= ~DAC2;
                /* Stop DMA */
                snd_es18xx_mixer_write(chip, 0x78, 0x00);
#ifdef AVOID_POPS
                udelay(25000);
		if (chip->caps & ES18XX_PCM2)
			/* Set Audio 2 volume to 0 */
			snd_es18xx_mixer_write(chip, 0x7C, 0);
		else
			/* Disable PCM output */
			snd_es18xx_dsp_command(chip, 0xD3);
#endif
		break;
	default:
		return -EINVAL;
	}

	return 0;
}