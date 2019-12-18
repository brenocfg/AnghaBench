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
struct snd_ac97 {int id; } ;

/* Variables and functions */
#define  AC97_ID_AD1819 143 
#define  AC97_ID_AD1881 142 
#define  AC97_ID_AD1881A 141 
#define  AC97_ID_AD1885 140 
#define  AC97_ID_AD1886 139 
#define  AC97_ID_AD1886A 138 
#define  AC97_ID_AD1887 137 
#define  AC97_ID_AK4540 136 
#define  AC97_ID_AK4542 135 
#define  AC97_ID_STAC9700 134 
#define  AC97_ID_STAC9704 133 
#define  AC97_ID_STAC9705 132 
#define  AC97_ID_STAC9708 131 
#define  AC97_ID_STAC9721 130 
#define  AC97_ID_STAC9744 129 
#define  AC97_ID_STAC9756 128 

__attribute__((used)) static int snd_ac97_valid_reg(struct snd_ac97 *ac97, unsigned short reg)
{
	/* filter some registers for buggy codecs */
	switch (ac97->id) {
	case AC97_ID_AK4540:
	case AC97_ID_AK4542:
		if (reg <= 0x1c || reg == 0x20 || reg == 0x26 || reg >= 0x7c)
			return 1;
		return 0;
	case AC97_ID_AD1819:	/* AD1819 */
	case AC97_ID_AD1881:	/* AD1881 */
	case AC97_ID_AD1881A:	/* AD1881A */
		if (reg >= 0x3a && reg <= 0x6e)	/* 0x59 */
			return 0;
		return 1;
	case AC97_ID_AD1885:	/* AD1885 */
	case AC97_ID_AD1886:	/* AD1886 */
	case AC97_ID_AD1886A:	/* AD1886A - !!verify!! --jk */
	case AC97_ID_AD1887:	/* AD1887 - !!verify!! --jk */
		if (reg == 0x5a)
			return 1;
		if (reg >= 0x3c && reg <= 0x6e)	/* 0x59 */
			return 0;
		return 1;
	case AC97_ID_STAC9700:
	case AC97_ID_STAC9704:
	case AC97_ID_STAC9705:
	case AC97_ID_STAC9708:
	case AC97_ID_STAC9721:
	case AC97_ID_STAC9744:
	case AC97_ID_STAC9756:
		if (reg <= 0x3a || reg >= 0x5a)
			return 1;
		return 0;
	}
	return 1;
}