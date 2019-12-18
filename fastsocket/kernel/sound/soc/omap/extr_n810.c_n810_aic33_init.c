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
 int /*<<< orphan*/  aic33_dapm_widgets ; 
 int /*<<< orphan*/  aic33_n810_controls ; 
 int /*<<< orphan*/  audio_map ; 
 int snd_soc_add_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 

__attribute__((used)) static int n810_aic33_init(struct snd_soc_codec *codec)
{
	int err;

	/* Not connected */
	snd_soc_dapm_nc_pin(codec, "MONO_LOUT");
	snd_soc_dapm_nc_pin(codec, "HPLCOM");
	snd_soc_dapm_nc_pin(codec, "HPRCOM");
	snd_soc_dapm_nc_pin(codec, "MIC3L");
	snd_soc_dapm_nc_pin(codec, "MIC3R");
	snd_soc_dapm_nc_pin(codec, "LINE1R");
	snd_soc_dapm_nc_pin(codec, "LINE2L");
	snd_soc_dapm_nc_pin(codec, "LINE2R");

	/* Add N810 specific controls */
	err = snd_soc_add_controls(codec, aic33_n810_controls,
				ARRAY_SIZE(aic33_n810_controls));
	if (err < 0)
		return err;

	/* Add N810 specific widgets */
	snd_soc_dapm_new_controls(codec, aic33_dapm_widgets,
				  ARRAY_SIZE(aic33_dapm_widgets));

	/* Set up N810 specific audio path audio_map */
	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	snd_soc_dapm_sync(codec);

	return 0;
}