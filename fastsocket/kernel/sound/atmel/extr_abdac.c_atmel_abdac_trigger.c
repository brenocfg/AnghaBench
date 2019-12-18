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
struct TYPE_2__ {int /*<<< orphan*/  chan; } ;
struct atmel_abdac {int /*<<< orphan*/  sample_clk; TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  DAC_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DATA ; 
 int EINVAL ; 
 int /*<<< orphan*/  EN ; 
#define  SNDRV_PCM_TRIGGER_PAUSE_PUSH 133 
#define  SNDRV_PCM_TRIGGER_PAUSE_RELEASE 132 
#define  SNDRV_PCM_TRIGGER_RESUME 131 
#define  SNDRV_PCM_TRIGGER_START 130 
#define  SNDRV_PCM_TRIGGER_STOP 129 
#define  SNDRV_PCM_TRIGGER_SUSPEND 128 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac_writel (struct atmel_abdac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dw_dma_cyclic_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dw_dma_cyclic_stop (int /*<<< orphan*/ ) ; 
 struct atmel_abdac* snd_pcm_substream_chip (struct snd_pcm_substream*) ; 

__attribute__((used)) static int atmel_abdac_trigger(struct snd_pcm_substream *substream, int cmd)
{
	struct atmel_abdac *dac = snd_pcm_substream_chip(substream);
	int retval = 0;

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE: /* fall through */
	case SNDRV_PCM_TRIGGER_RESUME: /* fall through */
	case SNDRV_PCM_TRIGGER_START:
		clk_enable(dac->sample_clk);
		retval = dw_dma_cyclic_start(dac->dma.chan);
		if (retval)
			goto out;
		dac_writel(dac, CTRL, DAC_BIT(EN));
		break;
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH: /* fall through */
	case SNDRV_PCM_TRIGGER_SUSPEND: /* fall through */
	case SNDRV_PCM_TRIGGER_STOP:
		dw_dma_cyclic_stop(dac->dma.chan);
		dac_writel(dac, DATA, 0);
		dac_writel(dac, CTRL, 0);
		clk_disable(dac->sample_clk);
		break;
	default:
		retval = -EINVAL;
		break;
	}
out:
	return retval;
}