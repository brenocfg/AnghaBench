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
struct snd_sb {unsigned int capture_format; int /*<<< orphan*/  mode; int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  mixer_lock; int /*<<< orphan*/  force_mode16; int /*<<< orphan*/  c_period_size; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_DSP_CAPTURE_FILT ; 
 unsigned int SB_DSP_DMA8_OFF ; 
 unsigned int SB_DSP_HI_INPUT_AUTO ; 
 unsigned int SB_DSP_INPUT ; 
 unsigned int SB_DSP_MONO_8BIT ; 
 unsigned int SB_DSP_SPEAKER_OFF ; 
 int /*<<< orphan*/  SB_MODE_CAPTURE_8 ; 
 int /*<<< orphan*/  SB_MODE_HALT ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,unsigned int) ; 
 int /*<<< orphan*/  snd_sbdsp_reset (struct snd_sb*) ; 
 int /*<<< orphan*/  snd_sbmixer_write (struct snd_sb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_sb8_capture_trigger(struct snd_pcm_substream *substream,
				   int cmd)
{
	unsigned long flags;
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	unsigned int count;

	spin_lock_irqsave(&chip->reg_lock, flags);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		snd_sbdsp_command(chip, chip->capture_format);
		if (chip->capture_format == SB_DSP_INPUT) {
			count = chip->c_period_size - 1;
			snd_sbdsp_command(chip, count & 0xff);
			snd_sbdsp_command(chip, count >> 8);
		}
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		if (chip->capture_format == SB_DSP_HI_INPUT_AUTO) {
			struct snd_pcm_runtime *runtime = substream->runtime;
			snd_sbdsp_reset(chip);
			if (runtime->channels > 1) {
				/* restore input filter status */
				spin_lock(&chip->mixer_lock);
				snd_sbmixer_write(chip, SB_DSP_CAPTURE_FILT, chip->force_mode16);
				spin_unlock(&chip->mixer_lock);
				/* set hardware to mono mode */
				snd_sbdsp_command(chip, SB_DSP_MONO_8BIT);
			}
		} else {
			snd_sbdsp_command(chip, SB_DSP_DMA8_OFF);
		}
		snd_sbdsp_command(chip, SB_DSP_SPEAKER_OFF);
	}
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	chip->mode = (cmd == SNDRV_PCM_TRIGGER_START) ? SB_MODE_CAPTURE_8 : SB_MODE_HALT;
	return 0;
}