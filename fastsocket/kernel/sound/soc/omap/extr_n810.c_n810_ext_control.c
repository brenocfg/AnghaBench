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
#define  N810_JACK_HP 130 
#define  N810_JACK_HS 129 
#define  N810_JACK_MIC 128 
 scalar_t__ n810_dmic_func ; 
 int n810_jack_func ; 
 scalar_t__ n810_spk_func ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 

__attribute__((used)) static void n810_ext_control(struct snd_soc_codec *codec)
{
	int hp = 0, line1l = 0;

	switch (n810_jack_func) {
	case N810_JACK_HS:
		line1l = 1;
	case N810_JACK_HP:
		hp = 1;
		break;
	case N810_JACK_MIC:
		line1l = 1;
		break;
	}

	if (n810_spk_func)
		snd_soc_dapm_enable_pin(codec, "Ext Spk");
	else
		snd_soc_dapm_disable_pin(codec, "Ext Spk");

	if (hp)
		snd_soc_dapm_enable_pin(codec, "Headphone Jack");
	else
		snd_soc_dapm_disable_pin(codec, "Headphone Jack");
	if (line1l)
		snd_soc_dapm_enable_pin(codec, "LINE1L");
	else
		snd_soc_dapm_disable_pin(codec, "LINE1L");

	if (n810_dmic_func)
		snd_soc_dapm_enable_pin(codec, "DMic");
	else
		snd_soc_dapm_disable_pin(codec, "DMic");

	snd_soc_dapm_sync(codec);
}