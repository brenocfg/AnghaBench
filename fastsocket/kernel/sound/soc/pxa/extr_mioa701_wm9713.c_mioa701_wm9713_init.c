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
struct snd_soc_codec {unsigned short (* read ) (struct snd_soc_codec*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned short) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_3D_CONTROL ; 
 int /*<<< orphan*/  AC97_GPIO_CFG ; 
 int /*<<< orphan*/  ARRAY_AND_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  audio_map ; 
 int /*<<< orphan*/  mioa701_dapm_widgets ; 
 int /*<<< orphan*/  snd_soc_dapm_add_routes (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_enable_pin (struct snd_soc_codec*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_new_controls (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (struct snd_soc_codec*) ; 
 unsigned short stub1 (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned short) ; 
 unsigned short stub3 (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct snd_soc_codec*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static int mioa701_wm9713_init(struct snd_soc_codec *codec)
{
	unsigned short reg;

	/* Add mioa701 specific widgets */
	snd_soc_dapm_new_controls(codec, ARRAY_AND_SIZE(mioa701_dapm_widgets));

	/* Set up mioa701 specific audio path audio_mapnects */
	snd_soc_dapm_add_routes(codec, ARRAY_AND_SIZE(audio_map));

	/* Prepare GPIO8 for rear speaker amplifier */
	reg = codec->read(codec, AC97_GPIO_CFG);
	codec->write(codec, AC97_GPIO_CFG, reg | 0x0100);

	/* Prepare MIC input */
	reg = codec->read(codec, AC97_3D_CONTROL);
	codec->write(codec, AC97_3D_CONTROL, reg | 0xc000);

	snd_soc_dapm_enable_pin(codec, "Front Speaker");
	snd_soc_dapm_enable_pin(codec, "Rear Speaker");
	snd_soc_dapm_enable_pin(codec, "Front Mic");
	snd_soc_dapm_enable_pin(codec, "GSM Line In");
	snd_soc_dapm_enable_pin(codec, "GSM Line Out");
	snd_soc_dapm_sync(codec);

	return 0;
}