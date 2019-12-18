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
struct snd_soc_codec {int dummy; } ;

/* Variables and functions */
 int snd_soc_dapm_set_pin (struct snd_soc_codec*,char const*,int /*<<< orphan*/ ) ; 

int snd_soc_dapm_nc_pin(struct snd_soc_codec *codec, const char *pin)
{
	return snd_soc_dapm_set_pin(codec, pin, 0);
}