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
 int EINVAL ; 
 int /*<<< orphan*/  WM8974_ADC ; 
#define  WM8974_ADCCLK 132 
#define  WM8974_BCLKDIV 131 
 int /*<<< orphan*/  WM8974_CLOCK ; 
 int /*<<< orphan*/  WM8974_DAC ; 
#define  WM8974_DACCLK 130 
 int /*<<< orphan*/  WM8974_GPIO ; 
#define  WM8974_MCLKDIV 129 
#define  WM8974_OPCLKDIV 128 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8974_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg;

	switch (div_id) {
	case WM8974_OPCLKDIV:
		reg = snd_soc_read(codec, WM8974_GPIO) & 0x1cf;
		snd_soc_write(codec, WM8974_GPIO, reg | div);
		break;
	case WM8974_MCLKDIV:
		reg = snd_soc_read(codec, WM8974_CLOCK) & 0x11f;
		snd_soc_write(codec, WM8974_CLOCK, reg | div);
		break;
	case WM8974_ADCCLK:
		reg = snd_soc_read(codec, WM8974_ADC) & 0x1f7;
		snd_soc_write(codec, WM8974_ADC, reg | div);
		break;
	case WM8974_DACCLK:
		reg = snd_soc_read(codec, WM8974_DAC) & 0x1f7;
		snd_soc_write(codec, WM8974_DAC, reg | div);
		break;
	case WM8974_BCLKDIV:
		reg = snd_soc_read(codec, WM8974_CLOCK) & 0x1e3;
		snd_soc_write(codec, WM8974_CLOCK, reg | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}