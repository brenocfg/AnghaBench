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
 int /*<<< orphan*/  WM8400_DAC_CTRL ; 
 int WM8400_DAC_MUTE ; 
 int wm8400_read (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wm8400_write (struct snd_soc_codec*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm8400_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_codec *codec = dai->codec;
	u16 val = wm8400_read(codec, WM8400_DAC_CTRL) & ~WM8400_DAC_MUTE;

	if (mute)
		wm8400_write(codec, WM8400_DAC_CTRL, val | WM8400_DAC_MUTE);
	else
		wm8400_write(codec, WM8400_DAC_CTRL, val);

	return 0;
}