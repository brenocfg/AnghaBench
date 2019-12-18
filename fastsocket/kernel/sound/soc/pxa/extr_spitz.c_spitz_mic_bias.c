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
 int /*<<< orphan*/  AKITA_GPIO_MIC_BIAS ; 
 int /*<<< orphan*/  SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  SPITZ_GPIO_MIC_BIAS ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_akita () ; 
 scalar_t__ machine_is_borzoi () ; 
 scalar_t__ machine_is_spitz () ; 

__attribute__((used)) static int spitz_mic_bias(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *k, int event)
{
	if (machine_is_borzoi() || machine_is_spitz())
		gpio_set_value(SPITZ_GPIO_MIC_BIAS,
				SND_SOC_DAPM_EVENT_ON(event));

	if (machine_is_akita())
		gpio_set_value(AKITA_GPIO_MIC_BIAS,
				SND_SOC_DAPM_EVENT_ON(event));

	return 0;
}