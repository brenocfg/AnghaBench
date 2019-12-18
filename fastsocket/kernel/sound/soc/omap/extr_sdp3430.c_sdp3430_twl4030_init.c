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
 int /*<<< orphan*/  SND_JACK_HEADSET ; 
 int /*<<< orphan*/  audio_map ; 
 int /*<<< orphan*/  hs_jack ; 
 int /*<<< orphan*/  hs_jack_gpios ; 
 int /*<<< orphan*/  hs_jack_pins ; 
 int /*<<< orphan*/  sdp3430_twl4030_dapm_widgets ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_codec*,char*) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int snd_soc_jack_add_gpios (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_add_pins (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_jack_new (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_sdp3430 ; 

__attribute__((used)) static int sdp3430_twl4030_init(struct snd_soc_codec *codec)
{
	int ret;

	/* Add SDP3430 specific widgets */
	ret = snd_soc_dapm_new_controls(codec, sdp3430_twl4030_dapm_widgets,
				ARRAY_SIZE(sdp3430_twl4030_dapm_widgets));
	if (ret)
		return ret;

	/* Set up SDP3430 specific audio path audio_map */
	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	/* SDP3430 connected pins */
	snd_soc_dapm_enable_pin(codec, "Ext Mic");
	snd_soc_dapm_enable_pin(codec, "Ext Spk");
	snd_soc_dapm_disable_pin(codec, "Headset Mic");
	snd_soc_dapm_disable_pin(codec, "Headset Stereophone");

	/* TWL4030 not connected pins */
	snd_soc_dapm_nc_pin(codec, "AUXL");
	snd_soc_dapm_nc_pin(codec, "AUXR");
	snd_soc_dapm_nc_pin(codec, "CARKITMIC");
	snd_soc_dapm_nc_pin(codec, "DIGIMIC0");
	snd_soc_dapm_nc_pin(codec, "DIGIMIC1");

	snd_soc_dapm_nc_pin(codec, "OUTL");
	snd_soc_dapm_nc_pin(codec, "OUTR");
	snd_soc_dapm_nc_pin(codec, "EARPIECE");
	snd_soc_dapm_nc_pin(codec, "PREDRIVEL");
	snd_soc_dapm_nc_pin(codec, "PREDRIVER");
	snd_soc_dapm_nc_pin(codec, "CARKITL");
	snd_soc_dapm_nc_pin(codec, "CARKITR");

	ret = snd_soc_dapm_sync(codec);
	if (ret)
		return ret;

	/* Headset jack detection */
	ret = snd_soc_jack_new(&snd_soc_sdp3430, "Headset Jack",
				SND_JACK_HEADSET, &hs_jack);
	if (ret)
		return ret;

	ret = snd_soc_jack_add_pins(&hs_jack, ARRAY_SIZE(hs_jack_pins),
				hs_jack_pins);
	if (ret)
		return ret;

	ret = snd_soc_jack_add_gpios(&hs_jack, ARRAY_SIZE(hs_jack_gpios),
				hs_jack_gpios);

	return ret;
}