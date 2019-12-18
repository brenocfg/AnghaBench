#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_sb {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/  mode; } ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_off; int /*<<< orphan*/  dma_on; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SB_RATE_LOCK_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 TYPE_1__ playback_cmd (struct snd_sb*) ; 
 struct snd_sb* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  snd_sbdsp_command (struct snd_sb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_als4000_playback_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_sb *chip = snd_pcm_substream_chip(substream);
	int result = 0;

	spin_lock(&chip->reg_lock);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
		chip->mode |= SB_RATE_LOCK_PLAYBACK;
		snd_sbdsp_command(chip, playback_cmd(chip).dma_on);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
		snd_sbdsp_command(chip, playback_cmd(chip).dma_off);
		chip->mode &= ~SB_RATE_LOCK_PLAYBACK;
		break;
	default:
		result = -EINVAL;
		break;
	}
	spin_unlock(&chip->reg_lock);
	return result;
}