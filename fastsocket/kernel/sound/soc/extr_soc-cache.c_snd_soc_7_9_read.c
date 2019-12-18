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
struct snd_soc_codec {unsigned int* reg_cache; unsigned int reg_cache_size; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int snd_soc_7_9_read(struct snd_soc_codec *codec,
				     unsigned int reg)
{
	u16 *cache = codec->reg_cache;
	if (reg >= codec->reg_cache_size)
		return -1;
	return cache[reg];
}