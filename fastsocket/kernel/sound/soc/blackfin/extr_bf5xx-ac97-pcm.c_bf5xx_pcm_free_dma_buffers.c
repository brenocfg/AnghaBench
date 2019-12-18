#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_dma_buffer {size_t bytes; int /*<<< orphan*/ * area; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_dma_buffer dma_buffer; } ;
struct snd_pcm {TYPE_1__* streams; } ;
struct ac97_frame {int dummy; } ;
struct TYPE_7__ {int buffer_bytes_max; } ;
struct TYPE_6__ {int /*<<< orphan*/ * rx_dma_buf; int /*<<< orphan*/ * tx_dma_buf; } ;
struct TYPE_5__ {struct snd_pcm_substream* substream; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 TYPE_4__ bf5xx_pcm_hardware ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sport_done (TYPE_2__*) ; 
 TYPE_2__* sport_handle ; 

__attribute__((used)) static void bf5xx_pcm_free_dma_buffers(struct snd_pcm *pcm)
{
	struct snd_pcm_substream *substream;
	struct snd_dma_buffer *buf;
	int stream;
#if defined(CONFIG_SND_BF5XX_MMAP_SUPPORT)
	size_t size = bf5xx_pcm_hardware.buffer_bytes_max *
		sizeof(struct ac97_frame) / 4;
#endif
	for (stream = 0; stream < 2; stream++) {
		substream = pcm->streams[stream].substream;
		if (!substream)
			continue;

		buf = &substream->dma_buffer;
		if (!buf->area)
			continue;
		dma_free_coherent(NULL, buf->bytes, buf->area, 0);
		buf->area = NULL;
#if defined(CONFIG_SND_BF5XX_MMAP_SUPPORT)
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		if (sport_handle->tx_dma_buf)
			dma_free_coherent(NULL, size, \
				sport_handle->tx_dma_buf, 0);
		sport_handle->tx_dma_buf = NULL;
	} else {

		if (sport_handle->rx_dma_buf)
			dma_free_coherent(NULL, size, \
				sport_handle->rx_dma_buf, 0);
		sport_handle->rx_dma_buf = NULL;
	}
#endif
	}
	if (sport_handle)
		sport_done(sport_handle);
}