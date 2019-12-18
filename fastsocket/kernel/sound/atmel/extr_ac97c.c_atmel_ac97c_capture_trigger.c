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
struct snd_pcm_substream {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_chan; } ;
struct atmel_ac97c {int opened; TYPE_1__ dma; } ;

/* Variables and functions */
 unsigned long AC97C_CMR_CENA ; 
 int /*<<< orphan*/  CAMR ; 
 int EINVAL ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 unsigned long ac97c_readl (struct atmel_ac97c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97c_writel (struct atmel_ac97c*,int /*<<< orphan*/ ,unsigned long) ; 
 int dw_dma_cyclic_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_dma_cyclic_stop (int /*<<< orphan*/ ) ; 
 struct atmel_ac97c* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int
atmel_ac97c_capture_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct atmel_ac97c *chip = snd_pcm_substream_chip(substream);
	unsigned long camr;
	int retval = 0;

	camr = ac97c_readl(chip, CAMR);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE: /* fall through */
	case SNDRV_PCM_TRIGGER_RESUME: /* fall through */
	case SNDRV_PCM_TRIGGER_START:
		retval = dw_dma_cyclic_start(chip->dma.rx_chan);
		if (retval)
			goto out;
		camr |= AC97C_CMR_CENA;
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH: /* fall through */
	case SNDRV_PCM_TRIGGER_SUSPEND: /* fall through */
	case SNDRV_PCM_TRIGGER_STOP:
		dw_dma_cyclic_stop(chip->dma.rx_chan);
		if (chip->opened <= 1)
			camr &= ~AC97C_CMR_CENA;
		break;
	default:
		retval = -EINVAL;
		break;
	}

	ac97c_writel(chip, CAMR, camr);
out:
	return retval;
}