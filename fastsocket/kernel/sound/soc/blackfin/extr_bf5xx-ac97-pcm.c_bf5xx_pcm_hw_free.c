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
struct sport_device {scalar_t__ rx_dma_buf; scalar_t__ tx_dma_buf; scalar_t__ once; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int buffer_size; scalar_t__ dma_area; struct sport_device* private_data; } ;
struct ac97_frame {int dummy; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_pcm_lib_free_pages (struct snd_pcm_substream*) ; 

__attribute__((used)) static int bf5xx_pcm_hw_free(struct snd_pcm_substream *substream)
{
#if defined(CONFIG_SND_BF5XX_MMAP_SUPPORT)
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct sport_device *sport = runtime->private_data;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		sport->once = 0;
		if (runtime->dma_area)
			memset(runtime->dma_area, 0, runtime->buffer_size);
		memset(sport->tx_dma_buf, 0, runtime->buffer_size *
			sizeof(struct ac97_frame));
	} else
		memset(sport->rx_dma_buf, 0, runtime->buffer_size *
			sizeof(struct ac97_frame));
#endif
	snd_pcm_lib_free_pages(substream);
	return 0;
}