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
 int /*<<< orphan*/  twl4030_codec_enable (struct snd_soc_codec*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl4030_power_down(struct snd_soc_codec *codec)
{
	/* power down */
	twl4030_codec_enable(codec, 0);
}