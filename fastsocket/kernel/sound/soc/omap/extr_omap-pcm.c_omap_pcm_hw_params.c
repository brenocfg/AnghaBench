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
struct snd_pcm_substream {int /*<<< orphan*/  dma_buffer; struct snd_soc_pcm_runtime* private_data; struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int /*<<< orphan*/  dma_bytes; struct omap_runtime_data* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct omap_runtime_data {int /*<<< orphan*/  dma_ch; struct omap_pcm_dma_data* dma_data; } ;
struct omap_pcm_dma_data {int /*<<< orphan*/  name; int /*<<< orphan*/  dma_req; } ;
struct TYPE_4__ {TYPE_1__* cpu_dai; } ;
struct TYPE_3__ {struct omap_pcm_dma_data* dma_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_dma_link_lch (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_pcm_dma_irq ; 
 int omap_request_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_buffer_bytes (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_pcm_set_runtime_buffer (struct snd_pcm_substream*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_pcm_hw_params(struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct omap_runtime_data *prtd = runtime->private_data;
	struct omap_pcm_dma_data *dma_data = rtd->dai->cpu_dai->dma_data;
	int err = 0;

	/* return if this is a bufferless transfer e.g.
	 * codec <--> BT codec or GSM modem -- lg FIXME */
	if (!dma_data)
		return 0;

	snd_pcm_set_runtime_buffer(substream, &substream->dma_buffer);
	runtime->dma_bytes = params_buffer_bytes(params);

	if (prtd->dma_data)
		return 0;
	prtd->dma_data = dma_data;
	err = omap_request_dma(dma_data->dma_req, dma_data->name,
			       omap_pcm_dma_irq, substream, &prtd->dma_ch);
	if (!err) {
		/*
		 * Link channel with itself so DMA doesn't need any
		 * reprogramming while looping the buffer
		 */
		omap_dma_link_lch(prtd->dma_ch, prtd->dma_ch);
	}

	return err;
}