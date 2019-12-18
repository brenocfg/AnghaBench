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
 int /*<<< orphan*/  omap3pandora_out_dapm_widgets ; 
 int /*<<< orphan*/  omap3pandora_out_map ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_codec*,char*) ; 
 int snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_dapm_sync (struct snd_soc_codec*) ; 

__attribute__((used)) static int omap3pandora_out_init(struct snd_soc_codec *codec)
{
	int ret;

	/* All TWL4030 output pins are floating */
	snd_soc_dapm_nc_pin(codec, "OUTL");
	snd_soc_dapm_nc_pin(codec, "OUTR");
	snd_soc_dapm_nc_pin(codec, "EARPIECE");
	snd_soc_dapm_nc_pin(codec, "PREDRIVEL");
	snd_soc_dapm_nc_pin(codec, "PREDRIVER");
	snd_soc_dapm_nc_pin(codec, "HSOL");
	snd_soc_dapm_nc_pin(codec, "HSOR");
	snd_soc_dapm_nc_pin(codec, "CARKITL");
	snd_soc_dapm_nc_pin(codec, "CARKITR");
	snd_soc_dapm_nc_pin(codec, "HFL");
	snd_soc_dapm_nc_pin(codec, "HFR");
	snd_soc_dapm_nc_pin(codec, "VIBRA");

	ret = snd_soc_dapm_new_controls(codec, omap3pandora_out_dapm_widgets,
				ARRAY_SIZE(omap3pandora_out_dapm_widgets));
	if (ret < 0)
		return ret;

	snd_soc_dapm_add_routes(codec, omap3pandora_out_map,
		ARRAY_SIZE(omap3pandora_out_map));

	return snd_soc_dapm_sync(codec);
}