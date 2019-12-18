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
struct sport_device {int once; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  period_size; struct sport_device* private_data; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  bf5xx_mmap_copy (struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_period_elapsed (struct snd_pcm_substream*) ; 

__attribute__((used)) static void bf5xx_dma_irq(void *data)
{
	struct snd_pcm_substream *pcm = data;
#if defined(CONFIG_SND_BF5XX_MMAP_SUPPORT)
	struct snd_pcm_runtime *runtime = pcm->runtime;
	struct sport_device *sport = runtime->private_data;
	bf5xx_mmap_copy(pcm, runtime->period_size);
	if (pcm->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		if (sport->once == 0) {
			snd_pcm_period_elapsed(pcm);
			bf5xx_mmap_copy(pcm, runtime->period_size);
			sport->once = 1;
		}
	}
#endif
	snd_pcm_period_elapsed(pcm);
}