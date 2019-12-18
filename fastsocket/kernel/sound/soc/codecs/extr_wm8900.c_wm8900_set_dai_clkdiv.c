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
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  WM8900_ADC_CLKDIV 134 
#define  WM8900_ADC_LRCLK 133 
#define  WM8900_BCLK_DIV 132 
#define  WM8900_DAC_CLKDIV 131 
#define  WM8900_DAC_LRCLK 130 
#define  WM8900_LRCLK_MODE 129 
 unsigned int WM8900_LRC_MASK ; 
#define  WM8900_OPCLK_DIV 128 
 int /*<<< orphan*/  WM8900_REG_AUDIO3 ; 
 int /*<<< orphan*/  WM8900_REG_AUDIO4 ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING1 ; 
 unsigned int WM8900_REG_CLOCKING1_BCLK_MASK ; 
 unsigned int WM8900_REG_CLOCKING1_OPCLK_MASK ; 
 int /*<<< orphan*/  WM8900_REG_CLOCKING2 ; 
 unsigned int WM8900_REG_CLOCKING2_ADC_CLKDIV ; 
 unsigned int WM8900_REG_CLOCKING2_DAC_CLKDIV ; 
 int /*<<< orphan*/  WM8900_REG_DACCTRL ; 
 unsigned int WM8900_REG_DACCTRL_AIF_LRCLKRATE ; 
 unsigned int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8900_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
				 int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	unsigned int reg;

	switch (div_id) {
	case WM8900_BCLK_DIV:
		reg = snd_soc_read(codec, WM8900_REG_CLOCKING1);
		snd_soc_write(codec, WM8900_REG_CLOCKING1,
			     div | (reg & WM8900_REG_CLOCKING1_BCLK_MASK));
		break;
	case WM8900_OPCLK_DIV:
		reg = snd_soc_read(codec, WM8900_REG_CLOCKING1);
		snd_soc_write(codec, WM8900_REG_CLOCKING1,
			     div | (reg & WM8900_REG_CLOCKING1_OPCLK_MASK));
		break;
	case WM8900_DAC_LRCLK:
		reg = snd_soc_read(codec, WM8900_REG_AUDIO4);
		snd_soc_write(codec, WM8900_REG_AUDIO4,
			     div | (reg & WM8900_LRC_MASK));
		break;
	case WM8900_ADC_LRCLK:
		reg = snd_soc_read(codec, WM8900_REG_AUDIO3);
		snd_soc_write(codec, WM8900_REG_AUDIO3,
			     div | (reg & WM8900_LRC_MASK));
		break;
	case WM8900_DAC_CLKDIV:
		reg = snd_soc_read(codec, WM8900_REG_CLOCKING2);
		snd_soc_write(codec, WM8900_REG_CLOCKING2,
			     div | (reg & WM8900_REG_CLOCKING2_DAC_CLKDIV));
		break;
	case WM8900_ADC_CLKDIV:
		reg = snd_soc_read(codec, WM8900_REG_CLOCKING2);
		snd_soc_write(codec, WM8900_REG_CLOCKING2,
			     div | (reg & WM8900_REG_CLOCKING2_ADC_CLKDIV));
		break;
	case WM8900_LRCLK_MODE:
		reg = snd_soc_read(codec, WM8900_REG_DACCTRL);
		snd_soc_write(codec, WM8900_REG_DACCTRL,
			     div | (reg & WM8900_REG_DACCTRL_AIF_LRCLKRATE));
		break;
	default:
		return -EINVAL;
	}

	return 0;
}