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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct snd_pcm_runtime {int channels; int format; int rate; } ;
struct atmel_ac97c {int /*<<< orphan*/  flags; TYPE_1__* pdev; int /*<<< orphan*/  ac97; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  A ; 
 unsigned long AC97C_CH_ASSIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long AC97C_CH_MASK (int /*<<< orphan*/ ) ; 
 unsigned long AC97C_CMR_CEM_LITTLE ; 
 unsigned long AC97C_CMR_DMAEN ; 
 unsigned long AC97C_CMR_SIZE_16 ; 
 unsigned long AC97C_CSR_OVRUN ; 
 unsigned long AC97C_MR_VRA ; 
 unsigned long AC97C_SR_CAEVT ; 
 int /*<<< orphan*/  AC97_PCM_LR_ADC_RATE ; 
 int /*<<< orphan*/  CAMR ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_RX_READY ; 
 int EINVAL ; 
 int /*<<< orphan*/  ICA ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IMR ; 
 int /*<<< orphan*/  MR ; 
 int /*<<< orphan*/  PCM_LEFT ; 
 int /*<<< orphan*/  PCM_RIGHT ; 
#define  SNDRV_PCM_FORMAT_S16_BE 129 
#define  SNDRV_PCM_FORMAT_S16_LE 128 
 unsigned long ac97c_readl (struct atmel_ac97c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97c_writel (struct atmel_ac97c*,int /*<<< orphan*/ ,unsigned long) ; 
 int atmel_ac97c_prepare_dma (struct atmel_ac97c*,struct snd_pcm_substream*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int snd_ac97_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct atmel_ac97c* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int atmel_ac97c_capture_prepare(struct snd_pcm_substream *substream)
{
	struct atmel_ac97c *chip = snd_pcm_substream_chip(substream);
	struct snd_pcm_runtime *runtime = substream->runtime;
	unsigned long word = ac97c_readl(chip, ICA);
	int retval;

	word &= ~(AC97C_CH_MASK(PCM_LEFT) | AC97C_CH_MASK(PCM_RIGHT));

	/* assign channels to AC97C channel A */
	switch (runtime->channels) {
	case 1:
		word |= AC97C_CH_ASSIGN(PCM_LEFT, A);
		break;
	case 2:
		word |= AC97C_CH_ASSIGN(PCM_LEFT, A)
			| AC97C_CH_ASSIGN(PCM_RIGHT, A);
		break;
	default:
		/* TODO: support more than two channels */
		return -EINVAL;
	}
	ac97c_writel(chip, ICA, word);

	/* configure sample format and size */
	word = AC97C_CMR_DMAEN | AC97C_CMR_SIZE_16;

	switch (runtime->format) {
	case SNDRV_PCM_FORMAT_S16_LE:
		word |= AC97C_CMR_CEM_LITTLE;
		break;
	case SNDRV_PCM_FORMAT_S16_BE: /* fall through */
		word &= ~(AC97C_CMR_CEM_LITTLE);
		break;
	default:
		word = ac97c_readl(chip, ICA);
		word &= ~(AC97C_CH_MASK(PCM_LEFT) | AC97C_CH_MASK(PCM_RIGHT));
		ac97c_writel(chip, ICA, word);
		return -EINVAL;
	}

	/* Enable overrun interrupt on channel A */
	word |= AC97C_CSR_OVRUN;

	ac97c_writel(chip, CAMR, word);

	/* Enable channel A event interrupt */
	word = ac97c_readl(chip, IMR);
	word |= AC97C_SR_CAEVT;
	ac97c_writel(chip, IER, word);

	/* set variable rate if needed */
	if (runtime->rate != 48000) {
		word = ac97c_readl(chip, MR);
		word |= AC97C_MR_VRA;
		ac97c_writel(chip, MR, word);
	} else {
		word = ac97c_readl(chip, MR);
		word &= ~(AC97C_MR_VRA);
		ac97c_writel(chip, MR, word);
	}

	retval = snd_ac97_set_rate(chip->ac97, AC97_PCM_LR_ADC_RATE,
			runtime->rate);
	if (retval)
		dev_dbg(&chip->pdev->dev, "could not set rate %d Hz\n",
				runtime->rate);

	if (!test_bit(DMA_RX_READY, &chip->flags))
		retval = atmel_ac97c_prepare_dma(chip, substream,
				DMA_FROM_DEVICE);

	return retval;
}