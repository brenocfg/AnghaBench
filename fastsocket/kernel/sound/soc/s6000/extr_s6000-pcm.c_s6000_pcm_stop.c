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
struct snd_soc_pcm_runtime {TYPE_2__* dai; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; TYPE_3__* runtime; } ;
struct s6000_runtime_data {int /*<<< orphan*/  lock; } ;
struct s6000_pcm_dma_params {int /*<<< orphan*/  dma_in; int /*<<< orphan*/  dma_out; } ;
struct TYPE_6__ {struct s6000_runtime_data* private_data; } ;
struct TYPE_5__ {TYPE_1__* cpu_dai; } ;
struct TYPE_4__ {struct s6000_pcm_dma_params* dma_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_INDEX_CHNL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_MASK_DMAC (int /*<<< orphan*/ ) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  s6dmac_disable_chan (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6dmac_set_terminal_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int s6000_pcm_stop(struct snd_pcm_substream *substream)
{
	struct s6000_runtime_data *prtd = substream->runtime->private_data;
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct s6000_pcm_dma_params *par = soc_runtime->dai->cpu_dai->dma_data;
	unsigned long flags;
	u32 channel;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		channel = par->dma_out;
	else
		channel = par->dma_in;

	s6dmac_set_terminal_count(DMA_MASK_DMAC(channel),
				  DMA_INDEX_CHNL(channel), 0);

	spin_lock_irqsave(&prtd->lock, flags);

	s6dmac_disable_chan(DMA_MASK_DMAC(channel), DMA_INDEX_CHNL(channel));

	spin_unlock_irqrestore(&prtd->lock, flags);

	return 0;
}