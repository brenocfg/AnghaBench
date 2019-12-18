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
 int /*<<< orphan*/  CORGI_GPIO_MUTE_L ; 
 int /*<<< orphan*/  CORGI_GPIO_MUTE_R ; 
#define  CORGI_HEADSET 131 
#define  CORGI_HP 130 
#define  CORGI_LINE 129 
#define  CORGI_MIC 128 
 scalar_t__ CORGI_SPK_ON ; 
 int corgi_jack_func ; 
 scalar_t__ corgi_spk_func ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 

__attribute__((used)) static void corgi_ext_control(struct snd_soc_codec *codec)
{
	/* set up jack connection */
	switch (corgi_jack_func) {
	case CORGI_HP:
		/* set = unmute headphone */
		gpio_set_value(CORGI_GPIO_MUTE_L, 1);
		gpio_set_value(CORGI_GPIO_MUTE_R, 1);
		snd_soc_dapm_disable_pin(codec, "Mic Jack");
		snd_soc_dapm_disable_pin(codec, "Line Jack");
		snd_soc_dapm_enable_pin(codec, "Headphone Jack");
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		break;
	case CORGI_MIC:
		/* reset = mute headphone */
		gpio_set_value(CORGI_GPIO_MUTE_L, 0);
		gpio_set_value(CORGI_GPIO_MUTE_R, 0);
		snd_soc_dapm_enable_pin(codec, "Mic Jack");
		snd_soc_dapm_disable_pin(codec, "Line Jack");
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		break;
	case CORGI_LINE:
		gpio_set_value(CORGI_GPIO_MUTE_L, 0);
		gpio_set_value(CORGI_GPIO_MUTE_R, 0);
		snd_soc_dapm_disable_pin(codec, "Mic Jack");
		snd_soc_dapm_enable_pin(codec, "Line Jack");
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		break;
	case CORGI_HEADSET:
		gpio_set_value(CORGI_GPIO_MUTE_L, 0);
		gpio_set_value(CORGI_GPIO_MUTE_R, 1);
		snd_soc_dapm_enable_pin(codec, "Mic Jack");
		snd_soc_dapm_disable_pin(codec, "Line Jack");
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_enable_pin(codec, "Headset Jack");
		break;
	}

	if (corgi_spk_func == CORGI_SPK_ON)
		snd_soc_dapm_enable_pin(codec, "Ext Spk");
	else
		snd_soc_dapm_disable_pin(codec, "Ext Spk");

	/* signal a DAPM event */
	snd_soc_dapm_sync(codec);
}