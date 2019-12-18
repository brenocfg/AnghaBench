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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_CENTER_LFE_MASTER ; 
 int ac97_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm9713_set_dai_tristate(struct snd_soc_dai *codec_dai,
	int tristate)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg = ac97_read(codec, AC97_CENTER_LFE_MASTER) & 0x9fff;

	if (tristate)
		ac97_write(codec, AC97_CENTER_LFE_MASTER, reg);

	return 0;
}