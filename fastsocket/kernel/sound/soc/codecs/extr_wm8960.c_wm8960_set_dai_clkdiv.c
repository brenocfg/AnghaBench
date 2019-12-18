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
 int /*<<< orphan*/  WM8960_ADDCTL1 ; 
 int /*<<< orphan*/  WM8960_CLOCK1 ; 
 int /*<<< orphan*/  WM8960_CLOCK2 ; 
#define  WM8960_DACDIV 133 
#define  WM8960_DCLKDIV 132 
#define  WM8960_OPCLKDIV 131 
 int /*<<< orphan*/  WM8960_PLL1 ; 
#define  WM8960_SYSCLKDIV 130 
#define  WM8960_SYSCLKSEL 129 
#define  WM8960_TOCLKSEL 128 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8960_set_dai_clkdiv(struct snd_soc_dai *codec_dai,
		int div_id, int div)
{
	struct snd_soc_codec *codec = codec_dai->codec;
	u16 reg;

	switch (div_id) {
	case WM8960_SYSCLKSEL:
		reg = snd_soc_read(codec, WM8960_CLOCK1) & 0x1fe;
		snd_soc_write(codec, WM8960_CLOCK1, reg | div);
		break;
	case WM8960_SYSCLKDIV:
		reg = snd_soc_read(codec, WM8960_CLOCK1) & 0x1f9;
		snd_soc_write(codec, WM8960_CLOCK1, reg | div);
		break;
	case WM8960_DACDIV:
		reg = snd_soc_read(codec, WM8960_CLOCK1) & 0x1c7;
		snd_soc_write(codec, WM8960_CLOCK1, reg | div);
		break;
	case WM8960_OPCLKDIV:
		reg = snd_soc_read(codec, WM8960_PLL1) & 0x03f;
		snd_soc_write(codec, WM8960_PLL1, reg | div);
		break;
	case WM8960_DCLKDIV:
		reg = snd_soc_read(codec, WM8960_CLOCK2) & 0x03f;
		snd_soc_write(codec, WM8960_CLOCK2, reg | div);
		break;
	case WM8960_TOCLKSEL:
		reg = snd_soc_read(codec, WM8960_ADDCTL1) & 0x1fd;
		snd_soc_write(codec, WM8960_ADDCTL1, reg | div);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}