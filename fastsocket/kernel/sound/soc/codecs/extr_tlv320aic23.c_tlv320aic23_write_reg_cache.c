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
typedef  int /*<<< orphan*/  u16 ;
struct snd_soc_codec {int /*<<< orphan*/ * reg_cache; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tlv320aic23_reg ; 

__attribute__((used)) static inline void tlv320aic23_write_reg_cache(struct snd_soc_codec *codec,
					       u8 reg, u16 value)
{
	u16 *cache = codec->reg_cache;
	if (reg >= ARRAY_SIZE(tlv320aic23_reg))
		return;
	cache[reg] = value;
}