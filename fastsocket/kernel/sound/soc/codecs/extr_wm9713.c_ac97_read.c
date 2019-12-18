#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct snd_soc_codec {unsigned int* reg_cache; int /*<<< orphan*/  ac97; } ;
struct TYPE_2__ {unsigned int (* read ) (int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 unsigned int AC97_CD ; 
 unsigned int AC97_GPIO_STATUS ; 
 unsigned int AC97_RESET ; 
 unsigned int AC97_VENDOR_ID1 ; 
 unsigned int AC97_VENDOR_ID2 ; 
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int EIO ; 
 TYPE_1__ soc_ac97_ops ; 
 unsigned int stub1 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  wm9713_reg ; 

__attribute__((used)) static unsigned int ac97_read(struct snd_soc_codec *codec,
	unsigned int reg)
{
	u16 *cache = codec->reg_cache;

	if (reg == AC97_RESET || reg == AC97_GPIO_STATUS ||
		reg == AC97_VENDOR_ID1 || reg == AC97_VENDOR_ID2 ||
		reg == AC97_CD)
		return soc_ac97_ops.read(codec->ac97, reg);
	else {
		reg = reg >> 1;

		if (reg >= (ARRAY_SIZE(wm9713_reg)))
			return -EIO;

		return cache[reg];
	}
}