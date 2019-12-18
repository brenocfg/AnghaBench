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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct snd_dma_buffer {int /*<<< orphan*/  addr; int /*<<< orphan*/  area; int /*<<< orphan*/  bytes; TYPE_1__ dev; } ;
struct snd_pcm_substream {struct snd_dma_buffer dma_buffer; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct snd_dma_buffer* dma_buffer_p; int /*<<< orphan*/ * dma_area; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct snd_dma_buffer*) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

void devdma_hw_free(struct device *dev, struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_dma_buffer *buf = runtime->dma_buffer_p;

	if (runtime->dma_area == NULL)
		return;

	if (buf != &substream->dma_buffer) {
		dma_free_coherent(buf->dev.dev, buf->bytes, buf->area, buf->addr);
		kfree(runtime->dma_buffer_p);
	}

	snd_pcm_set_runtime_buffer(substream, NULL);
}