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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int period_size; int buffer_size; scalar_t__ dma_addr; struct omap_runtime_data* private_data; } ;
struct omap_runtime_data {int period_index; int /*<<< orphan*/  dma_ch; } ;
typedef  int snd_pcm_uframes_t ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int bytes_to_frames (struct snd_pcm_runtime*,scalar_t__) ; 
 int /*<<< orphan*/  cpu_is_omap1510 () ; 
 scalar_t__ omap_get_dma_dst_pos (int /*<<< orphan*/ ) ; 
 scalar_t__ omap_get_dma_src_pos (int /*<<< orphan*/ ) ; 

__attribute__((used)) static snd_pcm_uframes_t omap_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct omap_runtime_data *prtd = runtime->private_data;
	dma_addr_t ptr;
	snd_pcm_uframes_t offset;

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE) {
		ptr = omap_get_dma_dst_pos(prtd->dma_ch);
		offset = bytes_to_frames(runtime, ptr - runtime->dma_addr);
	} else if (!(cpu_is_omap1510())) {
		ptr = omap_get_dma_src_pos(prtd->dma_ch);
		offset = bytes_to_frames(runtime, ptr - runtime->dma_addr);
	} else
		offset = prtd->period_index * runtime->period_size;

	if (offset >= runtime->buffer_size)
		offset = 0;

	return offset;
}