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
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPITZ_GPIO_MUTE_L ; 
 int /*<<< orphan*/  SPITZ_GPIO_MUTE_R ; 
#define  SPITZ_HEADSET 132 
#define  SPITZ_HP 131 
#define  SPITZ_HP_OFF 130 
#define  SPITZ_LINE 129 
#define  SPITZ_MIC 128 
 scalar_t__ SPITZ_SPK_ON ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int spitz_jack_func ; 
 scalar_t__ spitz_spk_func ; 

__attribute__((used)) static void spitz_ext_control(struct snd_soc_codec *codec)
{
	if (spitz_spk_func == SPITZ_SPK_ON)
		snd_soc_dapm_enable_pin(codec, "Ext Spk");
	else
		snd_soc_dapm_disable_pin(codec, "Ext Spk");

	/* set up jack connection */
	switch (spitz_jack_func) {
	case SPITZ_HP:
		/* enable and unmute hp jack, disable mic bias */
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		snd_soc_dapm_disable_pin(codec, "Mic Jack");
		snd_soc_dapm_disable_pin(codec, "Line Jack");
		snd_soc_dapm_enable_pin(codec, "Headphone Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 1);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 1);
		break;
	case SPITZ_MIC:
		/* enable mic jack and bias, mute hp */
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		snd_soc_dapm_disable_pin(codec, "Line Jack");
		snd_soc_dapm_enable_pin(codec, "Mic Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 0);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 0);
		break;
	case SPITZ_LINE:
		/* enable line jack, disable mic bias and mute hp */
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		snd_soc_dapm_disable_pin(codec, "Mic Jack");
		snd_soc_dapm_enable_pin(codec, "Line Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 0);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 0);
		break;
	case SPITZ_HEADSET:
		/* enable and unmute headset jack enable mic bias, mute L hp */
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_enable_pin(codec, "Mic Jack");
		snd_soc_dapm_disable_pin(codec, "Line Jack");
		snd_soc_dapm_enable_pin(codec, "Headset Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 0);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 1);
		break;
	case SPITZ_HP_OFF:

		/* jack removed, everything off */
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		snd_soc_dapm_disable_pin(codec, "Mic Jack");
		snd_soc_dapm_disable_pin(codec, "Line Jack");
		gpio_set_value(SPITZ_GPIO_MUTE_L, 0);
		gpio_set_value(SPITZ_GPIO_MUTE_R, 0);
		break;
	}
	snd_soc_dapm_sync(codec);
}