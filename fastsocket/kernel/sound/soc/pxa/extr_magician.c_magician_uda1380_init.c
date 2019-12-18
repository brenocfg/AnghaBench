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
 int /*<<< orphan*/  uda1380_dapm_widgets ; 
 int /*<<< orphan*/  uda1380_magician_controls ; 

__attribute__((used)) static int magician_uda1380_init(struct snd_soc_codec *codec)
{
	int err;

	/* NC codec pins */
	snd_soc_dapm_nc_pin(codec, "VOUTLHP");
	snd_soc_dapm_nc_pin(codec, "VOUTRHP");

	/* FIXME: is anything connected here? */
	snd_soc_dapm_nc_pin(codec, "VINL");
	snd_soc_dapm_nc_pin(codec, "VINR");

	/* Add magician specific controls */
	err = snd_soc_add_controls(codec, uda1380_magician_controls,
				ARRAY_SIZE(uda1380_magician_controls));
	if (err < 0)
		return err;

	/* Add magician specific widgets */
	snd_soc_dapm_new_controls(codec, uda1380_dapm_widgets,
				  ARRAY_SIZE(uda1380_dapm_widgets));

	/* Set up magician specific audio path interconnects */
	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	snd_soc_dapm_sync(codec);
	return 0;
}