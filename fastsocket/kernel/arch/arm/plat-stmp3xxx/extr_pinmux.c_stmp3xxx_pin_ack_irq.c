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
typedef  int u32 ;
struct stmp3xxx_pinmux_bank {int /*<<< orphan*/  irqstat; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmp3xxx_clearl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmp3xxx_irq_to_gpio (unsigned int,struct stmp3xxx_pinmux_bank**,unsigned int*) ; 

__attribute__((used)) static void stmp3xxx_pin_ack_irq(unsigned irq)
{
	u32 stat;
	struct stmp3xxx_pinmux_bank *pm;
	unsigned gpio;

	stmp3xxx_irq_to_gpio(irq, &pm, &gpio);
	stat = __raw_readl(pm->irqstat) & (1 << gpio);
	stmp3xxx_clearl(stat, pm->irqstat);
}