#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_soc_dapm_widget {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP3_PANDORA_AMP_POWER_GPIO ; 
 int /*<<< orphan*/  OMAP3_PANDORA_DAC_POWER_GPIO ; 
 scalar_t__ SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int omap3pandora_hp_event(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *k, int event)
{
	if (SND_SOC_DAPM_EVENT_ON(event)) {
		gpio_set_value(OMAP3_PANDORA_DAC_POWER_GPIO, 1);
		gpio_set_value(OMAP3_PANDORA_AMP_POWER_GPIO, 1);
	} else {
		gpio_set_value(OMAP3_PANDORA_AMP_POWER_GPIO, 0);
		mdelay(1);
		gpio_set_value(OMAP3_PANDORA_DAC_POWER_GPIO, 0);
	}

	return 0;
}