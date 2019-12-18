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
struct snd_soc_codec {int /*<<< orphan*/  dai; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WM8510_OPCLKDIV ; 
 int WM8510_OPCLKDIV_1 ; 
 int /*<<< orphan*/ * intercon ; 
 int /*<<< orphan*/ * playpaq_dapm_widgets ; 
 int /*<<< orphan*/  snd_soc_dai_set_clkdiv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_control (struct snd_soc_codec*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 

__attribute__((used)) static int playpaq_wm8510_init(struct snd_soc_codec *codec)
{
	int i;

	/*
	 * Add DAPM widgets
	 */
	for (i = 0; i < ARRAY_SIZE(playpaq_dapm_widgets); i++)
		snd_soc_dapm_new_control(codec, &playpaq_dapm_widgets[i]);



	/*
	 * Setup audio path interconnects
	 */
	snd_soc_dapm_add_routes(codec, intercon, ARRAY_SIZE(intercon));



	/* always connected pins */
	snd_soc_dapm_enable_pin(codec, "Int Mic");
	snd_soc_dapm_enable_pin(codec, "Ext Spk");
	snd_soc_dapm_sync(codec);



	/* Make CSB show PLL rate */
	snd_soc_dai_set_clkdiv(codec->dai, WM8510_OPCLKDIV,
				       WM8510_OPCLKDIV_1 | 4);

	return 0;
}