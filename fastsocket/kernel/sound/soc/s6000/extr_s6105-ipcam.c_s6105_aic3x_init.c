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
struct snd_soc_codec {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aic3x_dapm_widgets ; 
 int /*<<< orphan*/  audio_map ; 
 int /*<<< orphan*/  audio_out_mux ; 
 int /*<<< orphan*/  snd_ctl_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (int /*<<< orphan*/ *,struct snd_soc_codec*) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 

__attribute__((used)) static int s6105_aic3x_init(struct snd_soc_codec *codec)
{
	/* Add s6105 specific widgets */
	snd_soc_dapm_new_controls(codec, aic3x_dapm_widgets,
				  ARRAY_SIZE(aic3x_dapm_widgets));

	/* Set up s6105 specific audio path audio_map */
	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	/* not present */
	snd_soc_dapm_nc_pin(codec, "MONO_LOUT");
	snd_soc_dapm_nc_pin(codec, "LINE2L");
	snd_soc_dapm_nc_pin(codec, "LINE2R");

	/* not connected */
	snd_soc_dapm_nc_pin(codec, "MIC3L"); /* LINE2L on this chip */
	snd_soc_dapm_nc_pin(codec, "MIC3R"); /* LINE2R on this chip */
	snd_soc_dapm_nc_pin(codec, "LLOUT");
	snd_soc_dapm_nc_pin(codec, "RLOUT");
	snd_soc_dapm_nc_pin(codec, "HPRCOM");

	/* always connected */
	snd_soc_dapm_enable_pin(codec, "Audio In");

	/* must correspond to audio_out_mux.private_value initializer */
	snd_soc_dapm_disable_pin(codec, "Audio Out Differential");
	snd_soc_dapm_sync(codec);
	snd_soc_dapm_enable_pin(codec, "Audio Out Stereo");

	snd_soc_dapm_sync(codec);

	snd_ctl_add(codec->card, snd_ctl_new1(&audio_out_mux, codec));

	return 0;
}