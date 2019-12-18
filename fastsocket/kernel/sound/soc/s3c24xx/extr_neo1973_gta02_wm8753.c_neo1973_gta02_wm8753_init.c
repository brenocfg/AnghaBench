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
 int /*<<< orphan*/  audio_map ; 
 int snd_soc_add_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  wm8753_dapm_widgets ; 
 int /*<<< orphan*/  wm8753_neo1973_gta02_controls ; 

__attribute__((used)) static int neo1973_gta02_wm8753_init(struct snd_soc_codec *codec)
{
	int err;

	/* set up NC codec pins */
	snd_soc_dapm_nc_pin(codec, "OUT3");
	snd_soc_dapm_nc_pin(codec, "OUT4");
	snd_soc_dapm_nc_pin(codec, "LINE1");
	snd_soc_dapm_nc_pin(codec, "LINE2");

	/* Add neo1973 gta02 specific widgets */
	snd_soc_dapm_new_controls(codec, wm8753_dapm_widgets,
				  ARRAY_SIZE(wm8753_dapm_widgets));

	/* add neo1973 gta02 specific controls */
	err = snd_soc_add_controls(codec, wm8753_neo1973_gta02_controls,
		ARRAY_SIZE(wm8753_neo1973_gta02_controls));

	if (err < 0)
		return err;

	/* set up neo1973 gta02 specific audio path audio_map */
	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	/* set endpoints to default off mode */
	snd_soc_dapm_disable_pin(codec, "Stereo Out");
	snd_soc_dapm_disable_pin(codec, "GSM Line Out");
	snd_soc_dapm_disable_pin(codec, "GSM Line In");
	snd_soc_dapm_disable_pin(codec, "Headset Mic");
	snd_soc_dapm_disable_pin(codec, "Handset Mic");
	snd_soc_dapm_disable_pin(codec, "Handset Spk");

	snd_soc_dapm_sync(codec);

	return 0;
}