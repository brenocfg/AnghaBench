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
struct ak4117 {unsigned char* regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_write (struct ak4117*,unsigned char,unsigned char) ; 

void snd_ak4117_reg_write(struct ak4117 *chip, unsigned char reg, unsigned char mask, unsigned char val)
{
	if (reg >= 5)
		return;
	reg_write(chip, reg, (chip->regmap[reg] & ~mask) | val);
}