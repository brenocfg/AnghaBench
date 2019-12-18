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
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int fifo_size; } ;
struct snd_pcm_runtime {TYPE_2__ hw; struct aaci_runtime* private_data; } ;
struct aaci_runtime {struct snd_pcm_substream* substream; } ;
struct aaci {int fifosize; TYPE_1__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int IRQF_DISABLED ; 
 int IRQF_SHARED ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_CHANNELS ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_RATE ; 
 TYPE_2__ aaci_hw_info ; 
 int /*<<< orphan*/  aaci_irq ; 
 int /*<<< orphan*/  aaci_rule_rate_by_channels ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct aaci*) ; 
 int snd_pcm_hw_rule_add (struct snd_pcm_runtime*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct aaci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int __aaci_pcm_open(struct aaci *aaci,
			   struct snd_pcm_substream *substream,
			   struct aaci_runtime *aacirun)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int ret;

	aacirun->substream = substream;
	runtime->private_data = aacirun;
	runtime->hw = aaci_hw_info;

	/*
	 * FIXME: ALSA specifies fifo_size in bytes.  If we're in normal
	 * mode, each 32-bit word contains one sample.  If we're in
	 * compact mode, each 32-bit word contains two samples, effectively
	 * halving the FIFO size.  However, we don't know for sure which
	 * we'll be using at this point.  We set this to the lower limit.
	 */
	runtime->hw.fifo_size = aaci->fifosize * 2;

	/*
	 * Add rule describing hardware rate dependency
	 * on the number of channels.
	 */
	ret = snd_pcm_hw_rule_add(runtime, 0, SNDRV_PCM_HW_PARAM_RATE,
				  aaci_rule_rate_by_channels, aaci,
				  SNDRV_PCM_HW_PARAM_CHANNELS,
				  SNDRV_PCM_HW_PARAM_RATE, -1);
	if (ret)
		goto out;

	ret = request_irq(aaci->dev->irq[0], aaci_irq, IRQF_SHARED|IRQF_DISABLED,
			  DRIVER_NAME, aaci);
	if (ret)
		goto out;

	return 0;

 out:
	return ret;
}