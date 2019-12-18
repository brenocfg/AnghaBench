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
 int /*<<< orphan*/  e750_dapm_widgets ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 

__attribute__((used)) static int e750_ac97_init(struct snd_soc_codec *codec)
{
	snd_soc_dapm_nc_pin(codec, "LOUT");
	snd_soc_dapm_nc_pin(codec, "ROUT");
	snd_soc_dapm_nc_pin(codec, "PHONE");
	snd_soc_dapm_nc_pin(codec, "LINEINL");
	snd_soc_dapm_nc_pin(codec, "LINEINR");
	snd_soc_dapm_nc_pin(codec, "CDINL");
	snd_soc_dapm_nc_pin(codec, "CDINR");
	snd_soc_dapm_nc_pin(codec, "PCBEEP");
	snd_soc_dapm_nc_pin(codec, "MIC2");

	snd_soc_dapm_new_controls(codec, e750_dapm_widgets,
					ARRAY_SIZE(e750_dapm_widgets));

	snd_soc_dapm_add_routes(codec, audio_map, ARRAY_SIZE(audio_map));

	snd_soc_dapm_sync(codec);

	return 0;
}