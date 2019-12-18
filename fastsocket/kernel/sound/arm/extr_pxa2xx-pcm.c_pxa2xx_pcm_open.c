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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; struct pxa2xx_pcm_client* private_data; } ;
struct snd_pcm_runtime {struct pxa2xx_runtime_data* private_data; } ;
struct pxa2xx_runtime_data {int dma_ch; TYPE_1__* params; } ;
struct pxa2xx_pcm_client {int (* startup ) (struct snd_pcm_substream*) ;TYPE_1__* capture_params; TYPE_1__* playback_params; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRIO_LOW ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  __pxa2xx_pcm_close (struct snd_pcm_substream*) ; 
 int __pxa2xx_pcm_open (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  pxa2xx_pcm_dma_irq ; 
 int /*<<< orphan*/  pxa_free_dma (int) ; 
 int pxa_request_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 
 int stub1 (struct snd_pcm_substream*) ; 

__attribute__((used)) static int pxa2xx_pcm_open(struct snd_pcm_substream *substream)
{
	struct pxa2xx_pcm_client *client = substream->private_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct pxa2xx_runtime_data *rtd;
	int ret;

	ret = __pxa2xx_pcm_open(substream);
	if (ret)
		goto out;

	rtd = runtime->private_data;

	rtd->params = (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) ?
		      client->playback_params : client->capture_params;
	ret = pxa_request_dma(rtd->params->name, DMA_PRIO_LOW,
			      pxa2xx_pcm_dma_irq, substream);
	if (ret < 0)
		goto err2;
	rtd->dma_ch = ret;

	ret = client->startup(substream);
	if (!ret)
		goto out;

	pxa_free_dma(rtd->dma_ch);
 err2:
	__pxa2xx_pcm_close(substream);
 out:
	return ret;
}