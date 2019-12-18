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
struct snd_pcm_substream {scalar_t__ stream; struct snd_pcm_runtime* runtime; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_runtime {unsigned int buffer_size; scalar_t__ dma_addr; struct s6000_runtime_data* private_data; } ;
struct s6000_runtime_data {int /*<<< orphan*/  lock; } ;
struct s6000_pcm_dma_params {int /*<<< orphan*/  dma_in; int /*<<< orphan*/  dma_out; } ;
typedef  unsigned int snd_pcm_uframes_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {TYPE_1__* cpu_dai; } ;
struct TYPE_3__ {struct s6000_pcm_dma_params* dma_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_INDEX_CHNL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_MASK_DMAC (int /*<<< orphan*/ ) ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 unsigned int bytes_to_frames (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6dmac_cur_dst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s6dmac_cur_src (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static snd_pcm_uframes_t s6000_pcm_pointer(struct snd_pcm_substream *substream)
{
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct s6000_pcm_dma_params *par = soc_runtime->dai->cpu_dai->dma_data;
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct s6000_runtime_data *prtd = runtime->private_data;
	unsigned long flags;
	unsigned int offset;
	dma_addr_t count;

	spin_lock_irqsave(&prtd->lock, flags);

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		count = s6dmac_cur_src(DMA_MASK_DMAC(par->dma_out),
				       DMA_INDEX_CHNL(par->dma_out));
	else
		count = s6dmac_cur_dst(DMA_MASK_DMAC(par->dma_in),
				       DMA_INDEX_CHNL(par->dma_in));

	count -= runtime->dma_addr;

	spin_unlock_irqrestore(&prtd->lock, flags);

	offset = bytes_to_frames(runtime, count);
	if (unlikely(offset >= runtime->buffer_size))
		offset = 0;

	return offset;
}