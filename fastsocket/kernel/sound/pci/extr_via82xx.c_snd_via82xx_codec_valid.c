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
struct via82xx {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned int VIA_REG_AC97_BUSY ; 
 unsigned int VIA_REG_AC97_PRIMARY_VALID ; 
 unsigned int VIA_REG_AC97_SECONDARY_VALID ; 
 unsigned int snd_via82xx_codec_xread (struct via82xx*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int snd_via82xx_codec_valid(struct via82xx *chip, int secondary)
{
	unsigned int timeout = 1000;	/* 1ms */
	unsigned int val, val1;
	unsigned int stat = !secondary ? VIA_REG_AC97_PRIMARY_VALID :
					 VIA_REG_AC97_SECONDARY_VALID;
	
	while (timeout-- > 0) {
		val = snd_via82xx_codec_xread(chip);
		val1 = val & (VIA_REG_AC97_BUSY | stat);
		if (val1 == stat)
			return val & 0xffff;
		udelay(1);
	}
	return -EIO;
}