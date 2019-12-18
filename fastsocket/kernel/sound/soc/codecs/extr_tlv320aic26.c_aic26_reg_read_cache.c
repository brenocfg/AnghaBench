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
struct snd_soc_codec {unsigned int* reg_cache; } ;

/* Variables and functions */
 unsigned int AIC26_NUM_REGS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

__attribute__((used)) static unsigned int aic26_reg_read_cache(struct snd_soc_codec *codec,
					 unsigned int reg)
{
	u16 *cache = codec->reg_cache;

	if (reg >= AIC26_NUM_REGS) {
		WARN_ON_ONCE(1);
		return 0;
	}

	return cache[reg];
}