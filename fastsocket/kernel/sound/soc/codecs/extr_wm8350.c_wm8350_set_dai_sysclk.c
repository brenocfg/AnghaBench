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
struct wm8350 {int dummy; } ;
struct snd_soc_dai {struct snd_soc_codec* codec; } ;
struct snd_soc_codec {struct wm8350* control_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8350_CLOCK_CONTROL_1 ; 
 int /*<<< orphan*/  WM8350_CLOCK_CONTROL_2 ; 
 int WM8350_FLL_CLK_SRC_MASK ; 
 int /*<<< orphan*/  WM8350_FLL_CONTROL_4 ; 
 int /*<<< orphan*/  WM8350_MCLK_DIR ; 
 int WM8350_MCLK_DIR_OUT ; 
 int /*<<< orphan*/  WM8350_MCLK_SEL ; 
#define  WM8350_MCLK_SEL_MCLK 132 
#define  WM8350_MCLK_SEL_PLL_32K 131 
#define  WM8350_MCLK_SEL_PLL_ADC 130 
#define  WM8350_MCLK_SEL_PLL_DAC 129 
#define  WM8350_MCLK_SEL_PLL_MCLK 128 
 int /*<<< orphan*/  wm8350_clear_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wm8350_codec_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_codec_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8350_set_bits (struct wm8350*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8350_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	struct wm8350 *wm8350 = codec->control_data;
	u16 fll_4;

	switch (clk_id) {
	case WM8350_MCLK_SEL_MCLK:
		wm8350_clear_bits(wm8350, WM8350_CLOCK_CONTROL_1,
				  WM8350_MCLK_SEL);
		break;
	case WM8350_MCLK_SEL_PLL_MCLK:
	case WM8350_MCLK_SEL_PLL_DAC:
	case WM8350_MCLK_SEL_PLL_ADC:
	case WM8350_MCLK_SEL_PLL_32K:
		wm8350_set_bits(wm8350, WM8350_CLOCK_CONTROL_1,
				WM8350_MCLK_SEL);
		fll_4 = wm8350_codec_read(codec, WM8350_FLL_CONTROL_4) &
		    ~WM8350_FLL_CLK_SRC_MASK;
		wm8350_codec_write(codec, WM8350_FLL_CONTROL_4, fll_4 | clk_id);
		break;
	}

	/* MCLK direction */
	if (dir == WM8350_MCLK_DIR_OUT)
		wm8350_set_bits(wm8350, WM8350_CLOCK_CONTROL_2,
				WM8350_MCLK_DIR);
	else
		wm8350_clear_bits(wm8350, WM8350_CLOCK_CONTROL_2,
				  WM8350_MCLK_DIR);

	return 0;
}