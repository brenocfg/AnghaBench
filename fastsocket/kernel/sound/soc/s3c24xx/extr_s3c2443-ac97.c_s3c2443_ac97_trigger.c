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
struct snd_soc_pcm_runtime {TYPE_1__* dai; } ;
struct snd_soc_dai {int dummy; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_soc_pcm_runtime* private_data; } ;
struct s3c24xx_pcm_dma_params {int channel; } ;
struct TYPE_6__ {scalar_t__ regs; } ;
struct TYPE_5__ {scalar_t__ dma_data; } ;
struct TYPE_4__ {TYPE_2__* cpu_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2410_DMAOP_STARTED ; 
 scalar_t__ S3C_AC97_GLBCTRL ; 
 int /*<<< orphan*/  S3C_AC97_GLBCTRL_PCMINTM_DMA ; 
 int /*<<< orphan*/  S3C_AC97_GLBCTRL_PCMINTM_MASK ; 
 int /*<<< orphan*/  S3C_AC97_GLBCTRL_PCMOUTTM_DMA ; 
 int /*<<< orphan*/  S3C_AC97_GLBCTRL_PCMOUTTM_MASK ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_CAPTURE ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  s3c2410_dma_ctrl (int,int /*<<< orphan*/ ) ; 
 TYPE_3__ s3c24xx_ac97 ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int s3c2443_ac97_trigger(struct snd_pcm_substream *substream, int cmd,
				struct snd_soc_dai *dai)
{
	u32 ac_glbctrl;
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int channel = ((struct s3c24xx_pcm_dma_params *)
		  rtd->dai->cpu_dai->dma_data)->channel;

	ac_glbctrl = readl(s3c24xx_ac97.regs + S3C_AC97_GLBCTRL);
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			ac_glbctrl |= S3C_AC97_GLBCTRL_PCMINTM_DMA;
		else
			ac_glbctrl |= S3C_AC97_GLBCTRL_PCMOUTTM_DMA;
		break;
	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
			ac_glbctrl &= ~S3C_AC97_GLBCTRL_PCMINTM_MASK;
		else
			ac_glbctrl &= ~S3C_AC97_GLBCTRL_PCMOUTTM_MASK;
		break;
	}
	writel(ac_glbctrl, s3c24xx_ac97.regs + S3C_AC97_GLBCTRL);

	s3c2410_dma_ctrl(channel, S3C2410_DMAOP_STARTED);

	return 0;
}