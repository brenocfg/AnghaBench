#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_7__* socdev; TYPE_2__* dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm {TYPE_9__* streams; TYPE_3__* card; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_card {TYPE_11__* dev; } ;
struct psc_dma {int dummy; } ;
struct TYPE_22__ {TYPE_8__* substream; } ;
struct TYPE_21__ {int /*<<< orphan*/  dma_buffer; } ;
struct TYPE_20__ {TYPE_6__* card; int /*<<< orphan*/  dev; } ;
struct TYPE_19__ {TYPE_5__* codec; } ;
struct TYPE_18__ {TYPE_4__* ac97; } ;
struct TYPE_17__ {struct psc_dma* private_data; } ;
struct TYPE_16__ {int /*<<< orphan*/  dev; } ;
struct TYPE_15__ {TYPE_1__* cpu_dai; } ;
struct TYPE_14__ {struct psc_dma* private_data; } ;
struct TYPE_13__ {int coherent_dma_mask; int /*<<< orphan*/ * dma_mask; } ;
struct TYPE_12__ {size_t buffer_bytes_max; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SNDRV_DMA_TYPE_DEV ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct snd_card*,struct snd_soc_dai*,struct snd_pcm*) ; 
 int /*<<< orphan*/  dev_err (TYPE_11__*,char*) ; 
 int /*<<< orphan*/  psc_dma_dmamask ; 
 TYPE_10__ psc_dma_hardware ; 
 int snd_dma_alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_dma_free_pages (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int psc_dma_new(struct snd_card *card, struct snd_soc_dai *dai,
			   struct snd_pcm *pcm)
{
	struct snd_soc_pcm_runtime *rtd = pcm->private_data;
	struct psc_dma *psc_dma = rtd->dai->cpu_dai->private_data;
	size_t size = psc_dma_hardware.buffer_bytes_max;
	int rc = 0;

	dev_dbg(rtd->socdev->dev, "psc_dma_new(card=%p, dai=%p, pcm=%p)\n",
		card, dai, pcm);

	if (!card->dev->dma_mask)
		card->dev->dma_mask = &psc_dma_dmamask;
	if (!card->dev->coherent_dma_mask)
		card->dev->coherent_dma_mask = 0xffffffff;

	if (pcm->streams[0].substream) {
		rc = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, pcm->card->dev,
				size, &pcm->streams[0].substream->dma_buffer);
		if (rc)
			goto playback_alloc_err;
	}

	if (pcm->streams[1].substream) {
		rc = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV, pcm->card->dev,
				size, &pcm->streams[1].substream->dma_buffer);
		if (rc)
			goto capture_alloc_err;
	}

	if (rtd->socdev->card->codec->ac97)
		rtd->socdev->card->codec->ac97->private_data = psc_dma;

	return 0;

 capture_alloc_err:
	if (pcm->streams[0].substream)
		snd_dma_free_pages(&pcm->streams[0].substream->dma_buffer);

 playback_alloc_err:
	dev_err(card->dev, "Cannot allocate buffer(s)\n");

	return -ENOMEM;
}