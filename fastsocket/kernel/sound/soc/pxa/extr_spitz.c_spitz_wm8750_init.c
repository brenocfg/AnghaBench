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
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  wm8750_dapm_widgets ; 
 int /*<<< orphan*/  wm8750_spitz_controls ; 

__attribute__((used)) static int spitz_wm8750_init(struct snd_soc_codec *codec)
{
	int err;

	/* NC codec pins */
	snd_soc_dapm_nc_pin(codec, "RINPUT1");
	snd_soc_dapm_nc_pin(codec, "LINPUT2");
	snd_soc_dapm_nc_pin(codec, "RINPUT2");
	snd_soc_dapm_nc_pin(codec, "LINPUT3");
	snd_soc_dapm_nc_pin(codec, "RINPUT3");
	snd_soc_dapm_nc_pin(codec, "OUT3");
	snd_soc_dapm_nc_pin(codec, "MONO1");

	/* Add spitz specific controls */
	err = snd_soc_add_controls(codec, wm8750_spitz_controls,
				ARRAY_SIZE(wm8750_spitz_controls));
	if (err < 0)
		return err;

	/* Add spitz specific widgets */
	snd_soc_dapm_new_controls(codec, wm8750_dapm_widgets,
				  ARRAY_SIZE(wm8750_dapm_widgets));

	/* Set up spitz specific audio paths */
	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	snd_soc_dapm_sync(codec);
	return 0;
}