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
#define  WM8753_BCLKDIV 130 
 int /*<<< orphan*/  WM8753_CLOCK ; 
#define  WM8753_PCMDIV 129 
 int /*<<< orphan*/  WM8753_SRATE2 ; 
#define  WM8753_VXCLKDIV 128 
 int wm8753_read_reg_cache (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8753_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8753_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg;

	switch (div_id) {
	case WM8753_PCMDIV:
		reg = wm8753_read_reg_cache(codec, WM8753_CLOCK) & 0x003f;
		wm8753_write(codec, WM8753_CLOCK, reg | div);
		break;
	case WM8753_BCLKDIV:
		reg = wm8753_read_reg_cache(codec, WM8753_SRATE2) & 0x01c7;
		wm8753_write(codec, WM8753_SRATE2, reg | div);
		break;
	case WM8753_VXCLKDIV:
		reg = wm8753_read_reg_cache(codec, WM8753_SRATE2) & 0x003f;
		wm8753_write(codec, WM8753_SRATE2, reg | div);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}