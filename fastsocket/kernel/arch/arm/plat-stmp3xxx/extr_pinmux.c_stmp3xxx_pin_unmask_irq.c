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
struct stmp3xxx_pinmux_bank {int /*<<< orphan*/  pin2irq; int /*<<< orphan*/  irqen; } ;

/* Variables and functions */
 int /*<<< orphan*/  stmp3xxx_irq_to_gpio (unsigned int,struct stmp3xxx_pinmux_bank**,unsigned int*) ; 
 int /*<<< orphan*/  stmp3xxx_setl (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stmp3xxx_pin_unmask_irq(unsigned irq)
{
	struct stmp3xxx_pinmux_bank *pm;
	unsigned gpio;

	stmp3xxx_irq_to_gpio(irq, &pm, &gpio);
	stmp3xxx_setl(1 << gpio, pm->irqen);
	stmp3xxx_setl(1 << gpio, pm->pin2irq);
}