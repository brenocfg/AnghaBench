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
struct snd_pcm_substream {struct snd_soc_pcm_runtime* private_data; } ;
struct s6000_pcm_dma_params {int (* trigger ) (struct snd_pcm_substream*,int,int) ;} ;
struct TYPE_4__ {TYPE_1__* cpu_dai; } ;
struct TYPE_3__ {struct s6000_pcm_dma_params* dma_data; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int s6000_pcm_start (struct snd_pcm_substream*) ; 
 int s6000_pcm_stop (struct snd_pcm_substream*) ; 
 int stub1 (struct snd_pcm_substream*,int,int) ; 
 int stub2 (struct snd_pcm_substream*,int,int) ; 

__attribute__((used)) static int s6000_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct snd_soc_pcm_runtime *soc_runtime = substream->private_data;
	struct s6000_pcm_dma_params *par = soc_runtime->dai->cpu_dai->dma_data;
	int ret;

	ret = par->trigger(substream, cmd, 0);
	if (ret < 0)
		return ret;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ret = s6000_pcm_start(substream);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ret = s6000_pcm_stop(substream);
		break;
	default:
		ret = -EINVAL;
	}
	if (ret < 0)
		return ret;

	return par->trigger(substream, cmd, 1);
}