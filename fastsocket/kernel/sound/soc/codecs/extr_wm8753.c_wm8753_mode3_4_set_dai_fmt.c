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
 int /*<<< orphan*/  WM8753_CLOCK ; 
 scalar_t__ wm8753_hdac_set_dai_fmt (struct snd_soc_dai*,unsigned int) ; 
 int wm8753_i2s_set_dai_fmt (struct snd_soc_dai*,unsigned int) ; 
 int wm8753_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 scalar_t__ wm8753_vdac_adc_set_dai_fmt (struct snd_soc_dai*,unsigned int) ; 
 int /*<<< orphan*/  wm8753_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8753_mode3_4_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 clock;

	/* set clk source as mclk */
	clock = wm8753_read_reg_cache(codec, WM8753_CLOCK) & 0xfffb;
	wm8753_write(codec, WM8753_CLOCK, clock | 0x4);

	if (wm8753_hdac_set_dai_fmt(codec_dai, fmt) < 0)
		return -EINVAL;
	if (wm8753_vdac_adc_set_dai_fmt(codec_dai, fmt) < 0)
		return -EINVAL;
	return wm8753_i2s_set_dai_fmt(codec_dai, fmt);
}