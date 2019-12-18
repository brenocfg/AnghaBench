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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_cs46xx_pcm* private_data; } ;
struct snd_cs46xx_pcm {int /*<<< orphan*/  hw_buf; int /*<<< orphan*/ * substream; int /*<<< orphan*/ * pcm_channel; } ;
struct snd_cs46xx {int /*<<< orphan*/  (* active_ctrl ) (struct snd_cs46xx*,int) ;int /*<<< orphan*/ * playback_pcm; int /*<<< orphan*/  spos_mutex; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  cs46xx_dsp_destroy_pcm_channel (struct snd_cs46xx*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 
 struct snd_cs46xx* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  stub1 (struct snd_cs46xx*,int) ; 

__attribute__((used)) static int snd_cs46xx_playback_close(struct snd_pcm_substream *substream)
{
	struct snd_cs46xx *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_cs46xx_pcm * cpcm;

	cpcm = runtime->private_data;

	/* when playback_open fails, then cpcm can be NULL */
	if (!cpcm) return -ENXIO;

#ifdef CONFIG_SND_CS46XX_NEW_DSP
	mutex_lock(&chip->spos_mutex);
	if (cpcm->pcm_channel) {
		cs46xx_dsp_destroy_pcm_channel(chip,cpcm->pcm_channel);
		cpcm->pcm_channel = NULL;
	}
	mutex_unlock(&chip->spos_mutex);
#else
	chip->playback_pcm = NULL;
#endif

	cpcm->substream = NULL;
	snd_dma_free_pages(&cpcm->hw_buf);
	chip->active_ctrl(chip, -1);

	return 0;
}