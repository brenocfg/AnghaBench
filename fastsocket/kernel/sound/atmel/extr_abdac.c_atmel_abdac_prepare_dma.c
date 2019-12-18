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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int dma_addr; int buffer_size; int period_size; } ;
struct dw_cyclic_desc {struct atmel_abdac* period_callback_param; int /*<<< orphan*/  period_callback; } ;
struct dma_chan {int dummy; } ;
struct TYPE_4__ {struct dw_cyclic_desc* cdesc; struct dma_chan* chan; } ;
struct atmel_abdac {int /*<<< orphan*/  flags; TYPE_2__ dma; TYPE_1__* pdev; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_READY ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dw_cyclic_desc*) ; 
 int PTR_ERR (struct dw_cyclic_desc*) ; 
 int /*<<< orphan*/  atmel_abdac_dma_period_done ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct dw_cyclic_desc* dw_dma_cyclic_prep (struct dma_chan*,int,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long frames_to_bytes (struct snd_pcm_runtime*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_abdac_prepare_dma(struct atmel_abdac *dac,
		struct snd_pcm_substream *substream,
		enum dma_data_direction direction)
{
	struct dma_chan			*chan = dac->dma.chan;
	struct dw_cyclic_desc		*cdesc;
	struct snd_pcm_runtime		*runtime = substream->runtime;
	unsigned long			buffer_len, period_len;

	/*
	 * We don't do DMA on "complex" transfers, i.e. with
	 * non-halfword-aligned buffers or lengths.
	 */
	if (runtime->dma_addr & 1 || runtime->buffer_size & 1) {
		dev_dbg(&dac->pdev->dev, "too complex transfer\n");
		return -EINVAL;
	}

	buffer_len = frames_to_bytes(runtime, runtime->buffer_size);
	period_len = frames_to_bytes(runtime, runtime->period_size);

	cdesc = dw_dma_cyclic_prep(chan, runtime->dma_addr, buffer_len,
			period_len, DMA_TO_DEVICE);
	if (IS_ERR(cdesc)) {
		dev_dbg(&dac->pdev->dev, "could not prepare cyclic DMA\n");
		return PTR_ERR(cdesc);
	}

	cdesc->period_callback = atmel_abdac_dma_period_done;
	cdesc->period_callback_param = dac;

	dac->dma.cdesc = cdesc;

	set_bit(DMA_READY, &dac->flags);

	return 0;
}