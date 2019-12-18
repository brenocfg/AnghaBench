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
struct snd_es18xx {int dummy; } ;

/* Variables and functions */
 int snd_es18xx_bits (struct snd_es18xx*,unsigned char,unsigned char,unsigned char) ; 
 int snd_es18xx_mixer_bits (struct snd_es18xx*,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static int snd_es18xx_reg_bits(struct snd_es18xx *chip, unsigned char reg,
			       unsigned char mask, unsigned char val)
{
	if (reg < 0xa0)
		return snd_es18xx_mixer_bits(chip, reg, mask, val);
	else
		return snd_es18xx_bits(chip, reg, mask, val);
}