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
#define  TOSA_HEADSET 130 
#define  TOSA_HP 129 
#define  TOSA_MIC_INT 128 
 scalar_t__ TOSA_SPK_ON ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int tosa_jack_func ; 
 scalar_t__ tosa_spk_func ; 

__attribute__((used)) static void tosa_ext_control(struct snd_soc_codec *codec)
{
	/* set up jack connection */
	switch (tosa_jack_func) {
	case TOSA_HP:
		snd_soc_dapm_disable_pin(codec, "Mic (Internal)");
		snd_soc_dapm_enable_pin(codec, "Headphone Jack");
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		break;
	case TOSA_MIC_INT:
		snd_soc_dapm_enable_pin(codec, "Mic (Internal)");
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_disable_pin(codec, "Headset Jack");
		break;
	case TOSA_HEADSET:
		snd_soc_dapm_disable_pin(codec, "Mic (Internal)");
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
		snd_soc_dapm_enable_pin(codec, "Headset Jack");
		break;
	}

	if (tosa_spk_func == TOSA_SPK_ON)
		snd_soc_dapm_enable_pin(codec, "Speaker");
	else
		snd_soc_dapm_disable_pin(codec, "Speaker");

	snd_soc_dapm_sync(codec);
}