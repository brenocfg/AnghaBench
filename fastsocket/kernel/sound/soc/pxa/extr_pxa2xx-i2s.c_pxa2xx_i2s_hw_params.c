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
struct snd_soc_pcm_runtime {TYPE_1__* dai; } ;
struct snd_soc_dai {int /*<<< orphan*/ * dma_data; struct snd_soc_dai* private_data; } ;
struct snd_pcm_substream {scalar_t__ stream; struct snd_soc_pcm_runtime* private_data; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fmt; scalar_t__ master; } ;
struct TYPE_3__ {struct snd_soc_dai* cpu_dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int SACR0 ; 
 int SACR0_BCKD ; 
 int SACR0_ENB ; 
 int SACR0_RFTH (int) ; 
 int SACR0_TFTH (int) ; 
 int /*<<< orphan*/  SACR1 ; 
 int SADIV ; 
 int /*<<< orphan*/  SAIMR ; 
 int /*<<< orphan*/  SAIMR_RFS ; 
 int /*<<< orphan*/  SAIMR_TFS ; 
 scalar_t__ SNDRV_PCM_STREAM_PLAYBACK ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_i2s ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  pxa2xx_i2s_pcm_stereo_in ; 
 int /*<<< orphan*/  pxa2xx_i2s_pcm_stereo_out ; 
 TYPE_2__ pxa_i2s ; 
 int /*<<< orphan*/  pxa_i2s_wait () ; 

__attribute__((used)) static int pxa2xx_i2s_hw_params(struct snd_pcm_substream *substream,
				struct snd_pcm_hw_params *params,
				struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->dai->cpu_dai;

	BUG_ON(IS_ERR(clk_i2s));
	clk_enable(clk_i2s);
	dai->private_data = dai;
	pxa_i2s_wait();

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		cpu_dai->dma_data = &pxa2xx_i2s_pcm_stereo_out;
	else
		cpu_dai->dma_data = &pxa2xx_i2s_pcm_stereo_in;

	/* is port used by another stream */
	if (!(SACR0 & SACR0_ENB)) {
		SACR0 = 0;
		if (pxa_i2s.master)
			SACR0 |= SACR0_BCKD;

		SACR0 |= SACR0_RFTH(14) | SACR0_TFTH(1);
		SACR1 |= pxa_i2s.fmt;
	}
	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		SAIMR |= SAIMR_TFS;
	else
		SAIMR |= SAIMR_RFS;

	switch (params_rate(params)) {
	case 8000:
		SADIV = 0x48;
		break;
	case 11025:
		SADIV = 0x34;
		break;
	case 16000:
		SADIV = 0x24;
		break;
	case 22050:
		SADIV = 0x1a;
		break;
	case 44100:
		SADIV = 0xd;
		break;
	case 48000:
		SADIV = 0xc;
		break;
	case 96000: /* not in manual and possibly slightly inaccurate */
		SADIV = 0x6;
		break;
	}

	return 0;
}