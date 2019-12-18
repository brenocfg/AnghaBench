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
 int /*<<< orphan*/  wm8731_corgi_controls ; 
 int /*<<< orphan*/  wm8731_dapm_widgets ; 

__attribute__((used)) static int corgi_wm8731_init(struct snd_soc_codec *codec)
{
	int err;

	snd_soc_dapm_nc_pin(codec, "LLINEIN");
	snd_soc_dapm_nc_pin(codec, "RLINEIN");

	/* Add corgi specific controls */
	err = snd_soc_add_controls(codec, wm8731_corgi_controls,
				ARRAY_SIZE(wm8731_corgi_controls));
	if (err < 0)
		return err;

	/* Add corgi specific widgets */
	snd_soc_dapm_new_controls(codec, wm8731_dapm_widgets,
				  ARRAY_SIZE(wm8731_dapm_widgets));

	/* Set up corgi specific audio path audio_map */
	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	snd_soc_dapm_sync(codec);
	return 0;
}