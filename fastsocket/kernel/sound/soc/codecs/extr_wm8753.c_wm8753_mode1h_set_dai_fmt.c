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
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ wm8753_hdac_set_dai_fmt (struct snd_soc_dai*,unsigned int) ; 
 int wm8753_i2s_set_dai_fmt (struct snd_soc_dai*,unsigned int) ; 

__attribute__((used)) static int wm8753_mode1h_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	if (wm8753_hdac_set_dai_fmt(codec_dai, fmt) < 0)
		return -EINVAL;
	return wm8753_i2s_set_dai_fmt(codec_dai, fmt);
}