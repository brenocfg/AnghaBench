#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int reg; } ;
struct snd_ad1889 {TYPE_1__ ramc; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD_CHAN_ADC ; 
 int /*<<< orphan*/  AD_DMA_ADC ; 
 int /*<<< orphan*/  AD_DMA_CHSS ; 
 int /*<<< orphan*/  AD_DMA_CHSS_ADCS ; 
 int AD_DMA_IM_CNT ; 
 int AD_DMA_LOOP ; 
 int /*<<< orphan*/  AD_DS_RAMC ; 
 int AD_DS_RAMC_ADEN ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_START 129 
#define  SNDRV_PCM_TRIGGER_STOP 128 
 int /*<<< orphan*/  ad1889_channel_reset (struct snd_ad1889*,int /*<<< orphan*/ ) ; 
 int ad1889_readw (struct snd_ad1889*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1889_writel (struct snd_ad1889*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad1889_writew (struct snd_ad1889*,int /*<<< orphan*/ ,int) ; 
 struct snd_ad1889* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
snd_ad1889_capture_trigger(struct snd_pcm_substream *ss, int cmd)
{
	u16 ramc;
	struct snd_ad1889 *chip = snd_pcm_substream_chip(ss);

	ramc = ad1889_readw(chip, AD_DS_RAMC);
	
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
		/* enable DMA loop & interrupts */
		ad1889_writew(chip, AD_DMA_ADC, AD_DMA_LOOP | AD_DMA_IM_CNT);
		ramc |= AD_DS_RAMC_ADEN;
		/* 1 to clear CHSS bit */
		ad1889_writel(chip, AD_DMA_CHSS, AD_DMA_CHSS_ADCS);
		break;
	case SNDRV_PCM_TRIGGER_STOP:
		ramc &= ~AD_DS_RAMC_ADEN;
		break;
	default:
		return -EINVAL;
	}
	
	chip->ramc.reg = ramc;
	ad1889_writew(chip, AD_DS_RAMC, ramc);	
	ad1889_readw(chip, AD_DS_RAMC);	/* flush */
	
	/* reset the chip when STOP - will disable IRQs */
	if (cmd == SNDRV_PCM_TRIGGER_STOP)
		ad1889_channel_reset(chip, AD_CHAN_ADC);
		
	return 0;
}