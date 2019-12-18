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
struct snd_soc_codec {int* reg_cache; } ;

/* Variables and functions */
 int UDA1380_CACHEREGNUM ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uda1380_cache_dirty ; 

__attribute__((used)) static inline void uda1380_write_reg_cache(struct snd_soc_codec *codec,
	u16 reg, unsigned int value)
{
	u16 *cache = codec->reg_cache;

	if (reg >= UDA1380_CACHEREGNUM)
		return;
	if ((reg >= 0x10) && (cache[reg] != value))
		set_bit(reg - 0x10, &uda1380_cache_dirty);
	cache[reg] = value;
}