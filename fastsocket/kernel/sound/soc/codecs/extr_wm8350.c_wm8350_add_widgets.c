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
struct snd_soc_codec {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_map ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_new_widgets (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  wm8350_dapm_widgets ; 

__attribute__((used)) static int wm8350_add_widgets(struct snd_soc_codec *codec)
{
	int ret;

	ret = snd_soc_dapm_new_controls(codec,
					wm8350_dapm_widgets,
					ARRAY_SIZE(wm8350_dapm_widgets));
	if (ret != 0) {
		dev_err(codec->dev, "dapm control register failed\n");
		return ret;
	}

	/* set up audio paths */
	ret = snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));
	if (ret != 0) {
		dev_err(codec->dev, "DAPM route register failed\n");
		return ret;
	}

	return snd_soc_dapm_new_widgets(codec);
}