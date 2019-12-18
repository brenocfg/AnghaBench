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
typedef  unsigned int u16 ;
struct snd_soc_codec {unsigned int* reg_cache; unsigned int reg_cache_size; unsigned int (* hw_read ) (struct snd_soc_codec*,unsigned int) ;} ;

/* Variables and functions */
 scalar_t__ snd_soc_codec_volatile_register (struct snd_soc_codec*,unsigned int) ; 
 unsigned int stub1 (struct snd_soc_codec*,unsigned int) ; 

__attribute__((used)) static unsigned int snd_soc_8_16_read(struct snd_soc_codec *codec,
				      unsigned int reg)
{
	u16 *cache = codec->reg_cache;

	if (reg >= codec->reg_cache_size ||
	    snd_soc_codec_volatile_register(codec, reg))
		return codec->hw_read(codec, reg);
	else
		return cache[reg];
}