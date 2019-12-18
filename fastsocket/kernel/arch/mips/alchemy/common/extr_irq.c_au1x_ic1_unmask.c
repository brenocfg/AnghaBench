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

/* Variables and functions */
 unsigned int AU1000_GPIO_15 ; 
 unsigned int AU1000_INTC1_INT_BASE ; 
 int /*<<< orphan*/  IC1_MASKSET ; 
 int /*<<< orphan*/  IC1_WAKESET ; 
 int /*<<< orphan*/  PB1000_MDR ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  au_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void au1x_ic1_unmask(unsigned int irq_nr)
{
	unsigned int bit = irq_nr - AU1000_INTC1_INT_BASE;
	au_writel(1 << bit, IC1_MASKSET);
	au_writel(1 << bit, IC1_WAKESET);

/* very hacky. does the pb1000 cpld auto-disable this int?
 * nowhere in the current kernel sources is it disabled.	--mlau
 */
#if defined(CONFIG_MIPS_PB1000)
	if (irq_nr == AU1000_GPIO_15)
		au_writel(0x4000, PB1000_MDR); /* enable int */
#endif
	au_sync();
}