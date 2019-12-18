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
 int WM8350_ADCLRC_RATE_MASK ; 
#define  WM8350_ADCLR_CLKDIV 134 
#define  WM8350_ADC_CLKDIV 133 
 int WM8350_ADC_CLKDIV_MASK ; 
 int /*<<< orphan*/  WM8350_ADC_DIVIDER ; 
 int /*<<< orphan*/  WM8350_ADC_LR_RATE ; 
#define  WM8350_BCLK_CLKDIV 132 
 int WM8350_BCLK_DIV_MASK ; 
 int /*<<< orphan*/  WM8350_CLOCK_CONTROL_1 ; 
 int WM8350_DACLRC_RATE_MASK ; 
#define  WM8350_DACLR_CLKDIV 131 
#define  WM8350_DAC_CLKDIV 130 
 int WM8350_DAC_CLKDIV_MASK ; 
 int /*<<< orphan*/  WM8350_DAC_CLOCK_CONTROL ; 
 int /*<<< orphan*/  WM8350_DAC_LR_RATE ; 
 int WM8350_MCLK_DIV_MASK ; 
#define  WM8350_OPCLK_CLKDIV 129 
 int WM8350_OPCLK_DIV_MASK ; 
#define  WM8350_SYS_CLKDIV 128 
 int wm8350_codec_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8350_codec_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8350_set_clkdiv(struct snd_soc_dai *codec_dai, int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 val;

	switch (div_id) {
	case WM8350_ADC_CLKDIV:
		val = wm8350_codec_read(codec, WM8350_ADC_DIVIDER) &
		    ~WM8350_ADC_CLKDIV_MASK;
		wm8350_codec_write(codec, WM8350_ADC_DIVIDER, val | div);
		break;
	case WM8350_DAC_CLKDIV:
		val = wm8350_codec_read(codec, WM8350_DAC_CLOCK_CONTROL) &
		    ~WM8350_DAC_CLKDIV_MASK;
		wm8350_codec_write(codec, WM8350_DAC_CLOCK_CONTROL, val | div);
		break;
	case WM8350_BCLK_CLKDIV:
		val = wm8350_codec_read(codec, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_BCLK_DIV_MASK;
		wm8350_codec_write(codec, WM8350_CLOCK_CONTROL_1, val | div);
		break;
	case WM8350_OPCLK_CLKDIV:
		val = wm8350_codec_read(codec, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_OPCLK_DIV_MASK;
		wm8350_codec_write(codec, WM8350_CLOCK_CONTROL_1, val | div);
		break;
	case WM8350_SYS_CLKDIV:
		val = wm8350_codec_read(codec, WM8350_CLOCK_CONTROL_1) &
		    ~WM8350_MCLK_DIV_MASK;
		wm8350_codec_write(codec, WM8350_CLOCK_CONTROL_1, val | div);
		break;
	case WM8350_DACLR_CLKDIV:
		val = wm8350_codec_read(codec, WM8350_DAC_LR_RATE) &
		    ~WM8350_DACLRC_RATE_MASK;
		wm8350_codec_write(codec, WM8350_DAC_LR_RATE, val | div);
		break;
	case WM8350_ADCLR_CLKDIV:
		val = wm8350_codec_read(codec, WM8350_ADC_LR_RATE) &
		    ~WM8350_ADCLRC_RATE_MASK;
		wm8350_codec_write(codec, WM8350_ADC_LR_RATE, val | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}