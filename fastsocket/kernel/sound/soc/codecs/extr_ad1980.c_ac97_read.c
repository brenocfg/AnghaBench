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
#define  AC97_EXTENDED_STATUS 133 
#define  AC97_INT_PAGING 132 
#define  AC97_POWERDOWN 131 
#define  AC97_RESET 130 
#define  AC97_VENDOR_ID1 129 
#define  AC97_VENDOR_ID2 128 
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int EINVAL ; 
 int /*<<< orphan*/  ad1980_reg ; 
 TYPE_1__ soc_ac97_ops ; 
 unsigned int stub1 (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int ac97_read(struct snd_soc_codec *codec,
	unsigned int reg)
{
	u16 *cache = codec->reg_cache;

	switch (reg) {
	case AC97_RESET:
	case AC97_INT_PAGING:
	case AC97_POWERDOWN:
	case AC97_EXTENDED_STATUS:
	case AC97_VENDOR_ID1:
	case AC97_VENDOR_ID2:
		return soc_ac97_ops.read(codec->ac97, reg);
	default:
		reg = reg >> 1;

		if (reg >= ARRAY_SIZE(ad1980_reg))
			return -EINVAL;

		return cache[reg];
	}
}