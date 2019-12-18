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
struct es1938 {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO2MODE ; 
 int /*<<< orphan*/  DAC2 ; 
 int EINVAL ; 
 int /*<<< orphan*/  ESSSB_IREG_AUDIO2CONTROL1 ; 
 int /*<<< orphan*/  SLIO_REG (struct es1938*,int /*<<< orphan*/ ) ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_es1938_mixer_write (struct es1938*,int /*<<< orphan*/ ,int) ; 
 struct es1938* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_es1938_playback1_trigger(struct snd_pcm_substream *substream,
					int cmd)
{
	struct es1938 *chip = snd_pcm_substream_chip(substream);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		/* According to the documentation this should be:
		   0x13 but that value may randomly swap stereo channels */
                snd_es1938_mixer_write(chip, ESSSB_IREG_AUDIO2CONTROL1, 0x92);
                udelay(10);
		snd_es1938_mixer_write(chip, ESSSB_IREG_AUDIO2CONTROL1, 0x93);
                /* This two stage init gives the FIFO -> DAC connection time to
                 * settle before first data from DMA flows in.  This should ensure
                 * no swapping of stereo channels.  Report a bug if otherwise :-) */
		outb(0x0a, SLIO_REG(chip, AUDIO2MODE));
		chip->active |= DAC2;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		outb(0, SLIO_REG(chip, AUDIO2MODE));
		snd_es1938_mixer_write(chip, ESSSB_IREG_AUDIO2CONTROL1, 0);
		chip->active &= ~DAC2;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}