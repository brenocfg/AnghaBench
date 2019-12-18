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
struct viadev {size_t direction; int reg_offset; struct snd_pcm_substream* substream; } ;
struct via_rate_lock {int rate; int /*<<< orphan*/  lock; int /*<<< orphan*/  used; } ;
struct via82xx {TYPE_1__* ac97; scalar_t__ dxs_src; scalar_t__ dxs_fixed; scalar_t__ spdif_on; struct via_rate_lock* rates; } ;
struct snd_pcm_substream {struct snd_pcm_runtime* runtime; } ;
struct TYPE_4__ {int rates; int rate_min; int rate_max; } ;
struct snd_pcm_runtime {struct viadev* private_data; TYPE_2__ hw; } ;
struct TYPE_3__ {int* rates; } ;

/* Variables and functions */
 int AC97_RATES_ADC ; 
 int AC97_RATES_FRONT_DAC ; 
 size_t AC97_RATES_SPDIF ; 
 int /*<<< orphan*/  SNDRV_PCM_HW_PARAM_PERIODS ; 
 int SNDRV_PCM_RATE_48000 ; 
 int SNDRV_PCM_RATE_8000_48000 ; 
 int SNDRV_PCM_RATE_CONTINUOUS ; 
 int SNDRV_PCM_RATE_KNOT ; 
 int snd_pcm_hw_constraint_integer (struct snd_pcm_runtime*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_pcm_limit_hw_rates (struct snd_pcm_runtime*) ; 
 TYPE_2__ snd_via82xx_hw ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_via82xx_pcm_open(struct via82xx *chip, struct viadev *viadev,
				struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime = substream->runtime;
	int err;
	struct via_rate_lock *ratep;

	runtime->hw = snd_via82xx_hw;
	
	/* set the hw rate condition */
	ratep = &chip->rates[viadev->direction];
	spin_lock_irq(&ratep->lock);
	ratep->used++;
	if (chip->spdif_on && viadev->reg_offset == 0x30) {
		/* DXS#3 and spdif is on */
		runtime->hw.rates = chip->ac97->rates[AC97_RATES_SPDIF];
		snd_pcm_limit_hw_rates(runtime);
	} else if (chip->dxs_fixed && viadev->reg_offset < 0x40) {
		/* fixed DXS playback rate */
		runtime->hw.rates = SNDRV_PCM_RATE_48000;
		runtime->hw.rate_min = runtime->hw.rate_max = 48000;
	} else if (chip->dxs_src && viadev->reg_offset < 0x40) {
		/* use full SRC capabilities of DXS */
		runtime->hw.rates = (SNDRV_PCM_RATE_CONTINUOUS |
				     SNDRV_PCM_RATE_8000_48000);
		runtime->hw.rate_min = 8000;
		runtime->hw.rate_max = 48000;
	} else if (! ratep->rate) {
		int idx = viadev->direction ? AC97_RATES_ADC : AC97_RATES_FRONT_DAC;
		runtime->hw.rates = chip->ac97->rates[idx];
		snd_pcm_limit_hw_rates(runtime);
	} else {
		/* a fixed rate */
		runtime->hw.rates = SNDRV_PCM_RATE_KNOT;
		runtime->hw.rate_max = runtime->hw.rate_min = ratep->rate;
	}
	spin_unlock_irq(&ratep->lock);

	/* we may remove following constaint when we modify table entries
	   in interrupt */
	if ((err = snd_pcm_hw_constraint_integer(runtime, SNDRV_PCM_HW_PARAM_PERIODS)) < 0)
		return err;

	runtime->private_data = viadev;
	viadev->substream = substream;

	return 0;
}