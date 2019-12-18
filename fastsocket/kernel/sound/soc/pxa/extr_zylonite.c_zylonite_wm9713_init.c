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
struct snd_soc_codec {int /*<<< orphan*/ * dai; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_map ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ clk_pout ; 
 int /*<<< orphan*/  pout ; 
 int /*<<< orphan*/  snd_soc_dai_set_pll (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 int /*<<< orphan*/  zylonite_dapm_widgets ; 

__attribute__((used)) static int zylonite_wm9713_init(struct snd_soc_codec *codec)
{
	if (clk_pout)
		snd_soc_dai_set_pll(&codec->dai[0], 0, clk_get_rate(pout), 0);

	snd_soc_dapm_new_controls(codec, zylonite_dapm_widgets,
				  ARRAY_SIZE(zylonite_dapm_widgets));

	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	/* Static setup for now */
	snd_soc_dapm_enable_pin(codec, "Headphone");
	snd_soc_dapm_enable_pin(codec, "Headset Earpiece");

	snd_soc_dapm_sync(codec);
	return 0;
}