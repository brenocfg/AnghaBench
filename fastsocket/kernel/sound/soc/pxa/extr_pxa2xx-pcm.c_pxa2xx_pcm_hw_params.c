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
struct snd_soc_pcm_runtime {TYPE_2__* dai; } ;
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct pxa2xx_runtime_data* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct pxa2xx_runtime_data {int dma_ch; struct pxa2xx_pcm_dma_params* params; } ;
struct pxa2xx_pcm_dma_params {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__* cpu_dai; } ;
struct TYPE_3__ {struct pxa2xx_pcm_dma_params* dma_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_PRIO_LOW ; 
 int __pxa2xx_pcm_hw_params (struct snd_pcm_substream*,struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  pxa2xx_pcm_dma_irq ; 
 int /*<<< orphan*/  pxa_free_dma (int) ; 
 int pxa_request_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_substream*) ; 

__attribute__((used)) static int pxa2xx_pcm_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct pxa2xx_runtime_data *prtd = runtime->private_data;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct pxa2xx_pcm_dma_params *dma = rtd->dai->cpu_dai->dma_data;
	int ret;

	/* return if this is a bufferless transfer e.g.
	 * codec <--> BT codec or GSM modem -- lg FIXME */
	if (!dma)
		return 0;

	/* this may get called several times by oss emulation
	 * with different params */
	if (prtd->params == NULL) {
		prtd->params = dma;
		ret = pxa_request_dma(prtd->params->name, DMA_PRIO_LOW,
			      pxa2xx_pcm_dma_irq, substream);
		if (ret < 0)
			return ret;
		prtd->dma_ch = ret;
	} else if (prtd->params != dma) {
		pxa_free_dma(prtd->dma_ch);
		prtd->params = dma;
		ret = pxa_request_dma(prtd->params->name, DMA_PRIO_LOW,
			      pxa2xx_pcm_dma_irq, substream);
		if (ret < 0)
			return ret;
		prtd->dma_ch = ret;
	}

	return __pxa2xx_pcm_hw_params(substream, params);
}