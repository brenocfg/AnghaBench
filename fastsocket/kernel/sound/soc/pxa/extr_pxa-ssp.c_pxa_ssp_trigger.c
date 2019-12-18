#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct ssp_device* ssp; } ;
struct ssp_priv {TYPE_2__ dev; } ;
struct ssp_device {int dummy; } ;
struct snd_soc_pcm_runtime {TYPE_1__* dai; } ;
struct snd_soc_dai {struct ssp_priv* private_data; } ;
struct snd_pcm_substream {int /*<<< orphan*/  stream; struct snd_soc_pcm_runtime* private_data; } ;
struct TYPE_4__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SNDRV_PCM_STREAM_PLAYBACK ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  SSCR1 ; 
 int SSCR1_RSRE ; 
 int SSCR1_TSRE ; 
 int /*<<< orphan*/  SSSR ; 
 int /*<<< orphan*/  dump_registers (struct ssp_device*) ; 
 int /*<<< orphan*/  ssp_disable (TYPE_2__*) ; 
 int /*<<< orphan*/  ssp_enable (TYPE_2__*) ; 
 int ssp_read_reg (struct ssp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssp_write_reg (struct ssp_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int pxa_ssp_trigger(struct snd_pcm_substream *substream, int cmd,
			   struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;
	int ret = 0;
	struct ssp_priv *priv = cpu_dai->private_data;
	struct ssp_device *ssp = priv->dev.ssp;
	int val;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_RESUME:
		ssp_enable(&priv->dev);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		val = ssp_read_reg(ssp, SSCR1);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			val |= SSCR1_TSRE;
		else
			val |= SSCR1_RSRE;
		ssp_write_reg(ssp, SSCR1, val);
		val = ssp_read_reg(ssp, SSSR);
		ssp_write_reg(ssp, SSSR, val);
		break;
	case SNDRV_PCM_TRIGGER_START:
		val = ssp_read_reg(ssp, SSCR1);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			val |= SSCR1_TSRE;
		else
			val |= SSCR1_RSRE;
		ssp_write_reg(ssp, SSCR1, val);
		ssp_enable(&priv->dev);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		val = ssp_read_reg(ssp, SSCR1);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			val &= ~SSCR1_TSRE;
		else
			val &= ~SSCR1_RSRE;
		ssp_write_reg(ssp, SSCR1, val);
		break;
	case SNDRV_PCM_TRIGGER_SUSPEND:
		ssp_disable(&priv->dev);
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		val = ssp_read_reg(ssp, SSCR1);
		if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			val &= ~SSCR1_TSRE;
		else
			val &= ~SSCR1_RSRE;
		ssp_write_reg(ssp, SSCR1, val);
		break;

	default:
		ret = -EINVAL;
	}

	dump_registers(ssp);

	return ret;
}