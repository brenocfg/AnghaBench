#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {struct omap_runtime_data* private_data; } ;
struct omap_runtime_data {int period_index; int /*<<< orphan*/  lock; int /*<<< orphan*/  dma_ch; struct omap_pcm_dma_data* dma_data; } ;
struct omap_pcm_dma_data {int /*<<< orphan*/  (* set_threshold ) (struct snd_pcm_substream*) ;} ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  omap_start_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_stop_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct snd_pcm_substream*) ; 

__attribute__((used)) static int omap_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	struct omap_runtime_data *prtd = runtime->private_data;
	struct omap_pcm_dma_data *dma_data = prtd->dma_data;
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&prtd->lock, flags);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		prtd->period_index = 0;
		/* Configure McBSP internal buffer usage */
		if (dma_data->set_threshold)
			dma_data->set_threshold(substream);

		omap_start_dma(prtd->dma_ch);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		prtd->period_index = -1;
		omap_stop_dma(prtd->dma_ch);
		break;
	default:
		ret = -EINVAL;
	}
	spin_unlock_irqrestore(&prtd->lock, flags);

	return ret;
}