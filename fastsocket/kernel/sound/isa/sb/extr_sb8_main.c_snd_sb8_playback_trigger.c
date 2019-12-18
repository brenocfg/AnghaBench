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
struct snd_sb {unsigned int playback_format; int force_mode16; int /*<<< orphan*/  mode; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  mixer_lock; int /*<<< orphan*/  p_period_size; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; } ;

/* Variables and functions */
 unsigned int SB_DSP_DMA8_OFF ; 
 unsigned int SB_DSP_HI_OUTPUT_AUTO ; 
 unsigned int SB_DSP_OUTPUT ; 
 unsigned int SB_DSP_SPEAKER_OFF ; 
 int /*<<< orphan*/  SB_DSP_STEREO_SW ; 
 int /*<<< orphan*/  SB_MODE_HALT ; 
 int /*<<< orphan*/  SB_MODE_PLAYBACK_8 ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,unsigned int) ; 
 int /*<<< orphan*/  snd_sbdsp_reset (struct snd_sb*) ; 
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb8_playback_trigger(struct snd_pcm_substream *substream,
				    int cmd)
{
	unsigned long flags;
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	unsigned int count;

	spin_lock_irqsave(&chip->reg_lock, flags);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_sbdsp_command(chip, chip->playback_format);
		if (chip->playback_format == SB_DSP_OUTPUT) {
			count = chip->p_period_size - 1;
			snd_sbdsp_command(chip, count & 0xff);
			snd_sbdsp_command(chip, count >> 8);
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (chip->playback_format == SB_DSP_HI_OUTPUT_AUTO) {
			struct snd_pcm_runtime *runtime = substream->runtime;
			snd_sbdsp_reset(chip);
			if (runtime->channels > 1) {
				spin_lock(&chip->mixer_lock);
				/* restore output filter and set hardware to mono mode */ 
				snd_sbmixer_write(chip, SB_DSP_STEREO_SW, chip->force_mode16 & ~0x02);
				spin_unlock(&chip->mixer_lock);
			}
		} else {
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		}
		snd_sbdsp_command(chip, SB_DSP_SPEAKER_OFF);
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	chip->mode = (cmd == SNDRV_PCM_TRIGGER_START) ? SB_MODE_PLAYBACK_8 : SB_MODE_HALT;
	return 0;
}