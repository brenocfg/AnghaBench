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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8900_REG_DACCTRL ; 
 int /*<<< orphan*/  WM8900_REG_DACCTRL_MUTE ; 
 int /*<<< orphan*/  snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8900_digital_mute(struct snd_soc_dai *codec_dai, int mute)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg;

	reg = snd_soc_read(codec, WM8900_REG_DACCTRL);

	if (mute)
		reg |= WM8900_REG_DACCTRL_MUTE;
	else
		reg &= ~WM8900_REG_DACCTRL_MUTE;

	snd_soc_write(codec, WM8900_REG_DACCTRL, reg);

	return 0;
}