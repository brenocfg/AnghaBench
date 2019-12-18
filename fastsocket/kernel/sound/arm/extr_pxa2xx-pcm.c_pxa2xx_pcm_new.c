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
struct snd_pcm {int /*<<< orphan*/  private_free; struct pxa2xx_pcm_client* private_data; } ;
struct snd_card {TYPE_1__* dev; } ;
struct pxa2xx_pcm_client {scalar_t__ capture_params; scalar_t__ playback_params; } ;
struct TYPE_2__ {int coherent_dma_mask; int /*<<< orphan*/ * dma_mask; } ;

/* Variables and functions */
 int SNDRV_PCM_STREAM_CAPTURE ; 
 int SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  pxa2xx_pcm_dmamask ; 
 int /*<<< orphan*/  pxa2xx_pcm_free_dma_buffers ; 
 int /*<<< orphan*/  pxa2xx_pcm_ops ; 
 int pxa2xx_pcm_preallocate_dma_buffer (struct snd_pcm*,int) ; 
 int snd_pcm_new (struct snd_card*,char*,int /*<<< orphan*/ ,int,int,struct snd_pcm**) ; 
 int /*<<< orphan*/  snd_pcm_set_ops (struct snd_pcm*,int,int /*<<< orphan*/ *) ; 

int pxa2xx_pcm_new(struct snd_card *card, struct pxa2xx_pcm_client *client,
		   struct snd_pcm **rpcm)
{
	struct snd_pcm *pcm;
	int play = client->playback_params ? 1 : 0;
	int capt = client->capture_params ? 1 : 0;
	int ret;

	ret = snd_pcm_new(card, "PXA2xx-PCM", 0, play, capt, &pcm);
	if (ret)
		goto out;

	pcm->private_data = client;
	pcm->private_free = pxa2xx_pcm_free_dma_buffers;

	if (!card->dev->dma_mask)
		card->dev->dma_mask = &pxa2xx_pcm_dmamask;
	if (!card->dev->coherent_dma_mask)
		card->dev->coherent_dma_mask = 0xffffffff;

	if (play) {
		int stream = SNDRV_PCM_STREAM_PLAYBACK;
		snd_pcm_set_ops(pcm, stream, &pxa2xx_pcm_ops);
		ret = pxa2xx_pcm_preallocate_dma_buffer(pcm, stream);
		if (ret)
			goto out;
	}
	if (capt) {
		int stream = SNDRV_PCM_STREAM_CAPTURE;
		snd_pcm_set_ops(pcm, stream, &pxa2xx_pcm_ops);
		ret = pxa2xx_pcm_preallocate_dma_buffer(pcm, stream);
		if (ret)
			goto out;
	}

	if (rpcm)
		*rpcm = pcm;
	ret = 0;

 out:
	return ret;
}