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
struct snd_soc_codec {int (* volatile_register ) (int) ;} ;

/* Variables and functions */
 int stub1 (int) ; 

int snd_soc_codec_volatile_register(struct snd_soc_codec *codec, int reg)
{
	if (codec->volatile_register)
		return codec->volatile_register(reg);
	else
		return 0;
}