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
 int /*<<< orphan*/  WM8940_DAC ; 
 int snd_soc_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int snd_soc_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8940_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_codec *codec = dai->codec;
	u16 mute_reg = snd_soc_read(codec, WM8940_DAC) & 0xffbf;

	if (mute)
		mute_reg |= 0x40;

	return snd_soc_write(codec, WM8940_DAC, mute_reg);
}