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
struct stmp3xxx_pinmux_bank {int virq; } ;

/* Variables and functions */
 int ENOENT ; 
 int NR_BANKS ; 
 struct stmp3xxx_pinmux_bank* pinmux_banks ; 

__attribute__((used)) static int stmp3xxx_irq_to_gpio(int irq,
	struct stmp3xxx_pinmux_bank **bank, unsigned *gpio)
{
	struct stmp3xxx_pinmux_bank *pm;

	for (pm = pinmux_banks; pm < pinmux_banks + NR_BANKS; pm++)
		if (pm->virq <= irq && irq < pm->virq + 32) {
			*bank = pm;
			*gpio = irq - pm->virq;
			return 0;
		}
	return -ENOENT;
}