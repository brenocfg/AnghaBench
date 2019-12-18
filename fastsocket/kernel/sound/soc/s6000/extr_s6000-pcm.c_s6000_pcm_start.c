#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_pcm_runtime {TYPE_3__* dai; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; TYPE_1__* runtime; } ;
struct s6000_runtime_data {int /*<<< orphan*/  lock; } ;
struct s6000_pcm_dma_params {int /*<<< orphan*/  dma_in; int /*<<< orphan*/  dma_out; } ;
struct TYPE_6__ {TYPE_2__* cpu_dai; } ;
struct TYPE_5__ {struct s6000_pcm_dma_params* dma_data; } ;
struct TYPE_4__ {struct s6000_runtime_data* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_INDEX_CHNL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_MASK_DMAC (int /*<<< orphan*/ ) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  s6000_pcm_enqueue_dma (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  s6dmac_enable_chan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s6000_pcm_start(struct snd_pcm_substream *substream)
{
	struct s6000_runtime_data *prtd = substream->runtime->private_data;
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct s6000_pcm_dma_params *par = soc_runtime->dai->cpu_dai->dma_data;
	unsigned long flags;
	int srcinc;
	u32 dma;

	spin_lock_irqsave(&prtd->lock, flags);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) {
		srcinc = 1;
		dma = par->dma_out;
	} else {
		srcinc = 0;
		dma = par->dma_in;
	}
	s6dmac_enable_chan(DMA_MASK_DMAC(dma), DMA_INDEX_CHNL(dma),
			   1 /* priority 1 (0 is max) */,
			   0 /* peripheral requests w/o xfer length mode */,
			   srcinc /* source address increment */,
			   srcinc^1 /* destination address increment */,
			   0 /* chunksize 0 (skip impossible on this dma) */,
			   0 /* source skip after chunk (impossible) */,
			   0 /* destination skip after chunk (impossible) */,
			   4 /* 16 byte burst size */,
			   -1 /* don't conserve bandwidth */,
			   0 /* low watermark irq descriptor theshold */,
			   0 /* disable hardware timestamps */,
			   1 /* enable channel */);

	s6000_pcm_enqueue_dma(substream);
	s6000_pcm_enqueue_dma(substream);

	spin_unlock_irqrestore(&prtd->lock, flags);

	return 0;
}