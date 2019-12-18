#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_4__* dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct atmel_ssc_info {TYPE_2__* ssc; struct atmel_pcm_dma_params** dma_params; } ;
struct atmel_pcm_dma_params {TYPE_1__* mask; } ;
struct TYPE_8__ {TYPE_3__* cpu_dai; } ;
struct TYPE_7__ {size_t id; } ;
struct TYPE_6__ {int /*<<< orphan*/  regs; } ;
struct TYPE_5__ {int /*<<< orphan*/  ssc_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CR ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ) ; 
 struct snd_soc_pcm_runtime* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 struct atmel_ssc_info* ssc_info ; 
 int /*<<< orphan*/  ssc_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atmel_ssc_prepare(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = snd_pcm_substream_chip(substream);
	struct atmel_ssc_info *ssc_p = &ssc_info[rtd->dai->cpu_dai->id];
	struct atmel_pcm_dma_params *dma_params;
	int dir;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		dir = 0;
	else
		dir = 1;

	dma_params = ssc_p->dma_params[dir];

	ssc_writel(ssc_p->ssc->regs, CR, dma_params->mask->ssc_enable);

	pr_debug("%s enabled SSC_SR=0x%08x\n",
			dir ? "receive" : "transmit",
			ssc_readl(ssc_p->ssc->regs, SR));
	return 0;
}