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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SND_JACK_HEADPHONE ; 
 int /*<<< orphan*/  audio_map ; 
 int /*<<< orphan*/  hs_jack ; 
 int /*<<< orphan*/  hs_jack_gpios ; 
 int /*<<< orphan*/  hs_jack_pins ; 
 scalar_t__ machine_is_palmld () ; 
 int /*<<< orphan*/  palm27x_asoc ; 
 int /*<<< orphan*/  palm27x_dapm_widgets ; 
 int snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_codec*,char*) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_add_pins (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int palm27x_ac97_init(struct snd_soc_codec *codec)
{
	int err;

	/* add palm27x specific widgets */
	err = snd_soc_dapm_new_controls(codec, palm27x_dapm_widgets,
				ARRAY_SIZE(palm27x_dapm_widgets));
	if (err)
		return err;

	/* set up palm27x specific audio path audio_map */
	err = snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));
	if (err)
		return err;

	/* connected pins */
	if (machine_is_palmld())
		snd_soc_dapm_enable_pin(codec, "MIC1");
	snd_soc_dapm_enable_pin(codec, "HPOUTL");
	snd_soc_dapm_enable_pin(codec, "HPOUTR");
	snd_soc_dapm_enable_pin(codec, "LOUT2");
	snd_soc_dapm_enable_pin(codec, "ROUT2");

	/* not connected pins */
	snd_soc_dapm_nc_pin(codec, "OUT3");
	snd_soc_dapm_nc_pin(codec, "MONOOUT");
	snd_soc_dapm_nc_pin(codec, "LINEINL");
	snd_soc_dapm_nc_pin(codec, "LINEINR");
	snd_soc_dapm_nc_pin(codec, "PCBEEP");
	snd_soc_dapm_nc_pin(codec, "PHONE");
	snd_soc_dapm_nc_pin(codec, "MIC2");

	err = snd_soc_dapm_sync(codec);
	if (err)
		return err;

	/* Jack detection API stuff */
	err = snd_soc_jack_new(&palm27x_asoc, "Headphone Jack",
				SND_JACK_HEADPHONE, &hs_jack);
	if (err)
		return err;

	err = snd_soc_jack_add_pins(&hs_jack, ARRAY_SIZE(hs_jack_pins),
				hs_jack_pins);
	if (err)
		return err;

	err = snd_soc_jack_add_gpios(&hs_jack, ARRAY_SIZE(hs_jack_gpios),
				hs_jack_gpios);

	return err;
}