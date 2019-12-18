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
struct snd_pcm_substream {scalar_t__ stream; TYPE_1__* runtime; } ;
typedef  int snd_pcm_uframes_t ;
struct TYPE_2__ {int channels; scalar_t__ dma_area; } ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 

__attribute__((used)) static int bf5xx_pcm_copy(struct snd_pcm_substream *substream, int channel,
	snd_pcm_uframes_t pos, void *buf, snd_pcm_uframes_t count)
{
	unsigned int *src;
	unsigned int *dst;
	int i;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		src = buf;
		dst = (unsigned int *)substream->runtime->dma_area;

		dst += pos * 8;
		while (count--) {
			for (i = 0; i < substream->runtime->channels; i++)
				*(dst + i) = *src++;
			dst += 8;
		}
	} else {
		src = (unsigned int *)substream->runtime->dma_area;
		dst = buf;

		src += pos * 8;
		while (count--) {
			for (i = 0; i < substream->runtime->channels; i++)
				*dst++ = *(src+i);
			src += 8;
		}
	}

	return 0;
}