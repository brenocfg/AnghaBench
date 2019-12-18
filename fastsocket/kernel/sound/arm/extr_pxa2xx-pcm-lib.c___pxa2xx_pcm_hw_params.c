#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_pcm_substream {scalar_t__ stream; int /*<<< orphan*/  dma_buffer; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {size_t dma_bytes; int dma_addr; struct pxa2xx_runtime_data* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct pxa2xx_runtime_data {int dma_desc_array_phys; TYPE_1__* params; TYPE_2__* dma_desc_array; } ;
struct TYPE_4__ {int ddadr; int dsadr; int dtadr; size_t dcmd; } ;
typedef  TYPE_2__ pxa_dma_desc ;
typedef  int dma_addr_t ;
struct TYPE_3__ {int dev_addr; size_t dcmd; } ;

/* Variables and functions */
 size_t DCMD_ENDIRQEN ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 size_t params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 size_t params_period_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

int __pxa2xx_pcm_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct pxa2xx_runtime_data *rtd = runtime->private_data;
	size_t totsize = params_buffer_bytes(params);
	size_t period = params_period_bytes(params);
	pxa_dma_desc *dma_desc;
	dma_addr_t dma_buff_phys, next_desc_phys;

	snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);
	runtime->dma_bytes = totsize;

	dma_desc = rtd->dma_desc_array;
	next_desc_phys = rtd->dma_desc_array_phys;
	dma_buff_phys = runtime->dma_addr;
	do {
		next_desc_phys += sizeof(pxa_dma_desc);
		dma_desc->ddadr = next_desc_phys;
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
			dma_desc->dsadr = dma_buff_phys;
			dma_desc->dtadr = rtd->params->dev_addr;
		} else {
			dma_desc->dsadr = rtd->params->dev_addr;
			dma_desc->dtadr = dma_buff_phys;
		}
		if (period > totsize)
			period = totsize;
		dma_desc->dcmd = rtd->params->dcmd | period | DCMD_ENDIRQEN;
		dma_desc++;
		dma_buff_phys += period;
	} while (totsize -= period);
	dma_desc[-1].ddadr = rtd->dma_desc_array_phys;

	return 0;
}