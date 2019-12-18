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
struct snd_soc_codec {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ POODLE_HP ; 
 int /*<<< orphan*/  POODLE_LOCOMO_GPIO_MUTE_L ; 
 int /*<<< orphan*/  POODLE_LOCOMO_GPIO_MUTE_R ; 
 scalar_t__ POODLE_SPK_ON ; 
 int /*<<< orphan*/  locomo_gpio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ poodle_jack_func ; 
 TYPE_1__ poodle_locomo_device ; 
 scalar_t__ poodle_spk_func ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 

__attribute__((used)) static void poodle_ext_control(struct snd_soc_codec *codec)
{
	/* set up jack connection */
	if (poodle_jack_func == POODLE_HP) {
		/* set = unmute headphone */
		locomo_gpio_write(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_MUTE_L, 1);
		locomo_gpio_write(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_MUTE_R, 1);
		snd_soc_dapm_enable_pin(codec, "Headphone Jack");
	} else {
		locomo_gpio_write(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_MUTE_L, 0);
		locomo_gpio_write(&poodle_locomo_device.dev,
			POODLE_LOCOMO_GPIO_MUTE_R, 0);
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
	}

	/* set the enpoints to their new connetion states */
	if (poodle_spk_func == POODLE_SPK_ON)
		snd_soc_dapm_enable_pin(codec, "Ext Spk");
	else
		snd_soc_dapm_disable_pin(codec, "Ext Spk");

	/* signal a DAPM event */
	snd_soc_dapm_sync(codec);
}