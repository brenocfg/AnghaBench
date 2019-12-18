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
 int /*<<< orphan*/  AC97_HANDSET_RATE ; 
 int /*<<< orphan*/  AC97_LINE1_LEVEL ; 
 int EINVAL ; 
#define  WM9713_CLKA_MULT 134 
#define  WM9713_CLKB_MULT 133 
#define  WM9713_HIFI_DIV 132 
#define  WM9713_HIFI_PLL_DIV 131 
#define  WM9713_PCMBCLK_DIV 130 
#define  WM9713_PCMCLK_DIV 129 
#define  WM9713_PCMCLK_PLL_DIV 128 
 int ac97_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ac97_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm9713_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg;

	switch (div_id) {
	case WM9713_PCMCLK_DIV:
		reg = ac97_read(codec, AC97_HANDSET_RATE) & 0xf0ff;
		ac97_write(codec, AC97_HANDSET_RATE, reg | div);
		break;
	case WM9713_CLKA_MULT:
		reg = ac97_read(codec, AC97_HANDSET_RATE) & 0xfffd;
		ac97_write(codec, AC97_HANDSET_RATE, reg | div);
		break;
	case WM9713_CLKB_MULT:
		reg = ac97_read(codec, AC97_HANDSET_RATE) & 0xfffb;
		ac97_write(codec, AC97_HANDSET_RATE, reg | div);
		break;
	case WM9713_HIFI_DIV:
		reg = ac97_read(codec, AC97_HANDSET_RATE) & 0x8fff;
		ac97_write(codec, AC97_HANDSET_RATE, reg | div);
		break;
	case WM9713_PCMBCLK_DIV:
		reg = ac97_read(codec, AC97_CENTER_LFE_MASTER) & 0xf1ff;
		ac97_write(codec, AC97_CENTER_LFE_MASTER, reg | div);
		break;
	case WM9713_PCMCLK_PLL_DIV:
		reg = ac97_read(codec, AC97_LINE1_LEVEL) & 0xff80;
		ac97_write(codec, AC97_LINE1_LEVEL, reg | 0x60 | div);
		break;
	case WM9713_HIFI_PLL_DIV:
		reg = ac97_read(codec, AC97_LINE1_LEVEL) & 0xff80;
		ac97_write(codec, AC97_LINE1_LEVEL, reg | 0x70 | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}