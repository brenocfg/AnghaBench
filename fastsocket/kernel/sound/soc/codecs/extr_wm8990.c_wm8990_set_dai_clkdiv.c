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
#define  WM8990_ADCCLK_DIV 131 
 int WM8990_ADC_CLKDIV_MASK ; 
#define  WM8990_BCLK_DIV 130 
 int WM8990_BCLK_DIV_MASK ; 
 int /*<<< orphan*/  WM8990_CLOCKING_1 ; 
 int /*<<< orphan*/  WM8990_CLOCKING_2 ; 
#define  WM8990_DACCLK_DIV 129 
 int WM8990_DAC_CLKDIV_MASK ; 
#define  WM8990_MCLK_DIV 128 
 int WM8990_MCLK_DIV_MASK ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8990_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg;

	switch (div_id) {
	case WM8990_MCLK_DIV:
		reg = snd_soc_read(codec, WM8990_CLOCKING_2) &
			~WM8990_MCLK_DIV_MASK;
		snd_soc_write(codec, WM8990_CLOCKING_2, reg | div);
		break;
	case WM8990_DACCLK_DIV:
		reg = snd_soc_read(codec, WM8990_CLOCKING_2) &
			~WM8990_DAC_CLKDIV_MASK;
		snd_soc_write(codec, WM8990_CLOCKING_2, reg | div);
		break;
	case WM8990_ADCCLK_DIV:
		reg = snd_soc_read(codec, WM8990_CLOCKING_2) &
			~WM8990_ADC_CLKDIV_MASK;
		snd_soc_write(codec, WM8990_CLOCKING_2, reg | div);
		break;
	case WM8990_BCLK_DIV:
		reg = snd_soc_read(codec, WM8990_CLOCKING_1) &
			~WM8990_BCLK_DIV_MASK;
		snd_soc_write(codec, WM8990_CLOCKING_1, reg | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}