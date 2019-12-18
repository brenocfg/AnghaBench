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
 int /*<<< orphan*/  PA_CPLD_IMSK ; 
 unsigned int SE7343_FPGA_IRQ_BASE ; 
 int ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outw (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_se7343_irq(unsigned int irq)
{
	unsigned int bit = irq - SE7343_FPGA_IRQ_BASE;
	ctrl_outw(ctrl_inw(PA_CPLD_IMSK) | 1 << bit, PA_CPLD_IMSK);
}