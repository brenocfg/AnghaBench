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
typedef  size_t u8 ;
struct snd_soc_codec {size_t* reg_cache; } ;

/* Variables and functions */
 size_t UDA134X_REGS_NUM ; 

__attribute__((used)) static inline void uda134x_write_reg_cache(struct snd_soc_codec *codec,
	u8 reg, unsigned int value)
{
	u8 *cache = codec->reg_cache;

	if (reg >= UDA134X_REGS_NUM)
		return;
	cache[reg] = value;
}