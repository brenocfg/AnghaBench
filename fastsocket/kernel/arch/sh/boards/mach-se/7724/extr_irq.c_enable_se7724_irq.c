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
struct fpga_irq {unsigned int base; int /*<<< orphan*/  mraddr; } ;

/* Variables and functions */
 int ctrl_inw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga2irq (unsigned int) ; 
 struct fpga_irq get_fpga_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void enable_se7724_irq(unsigned int irq)
{
	struct fpga_irq set = get_fpga_irq(fpga2irq(irq));
	unsigned int bit = irq - set.base;
	ctrl_outw(ctrl_inw(set.mraddr) & ~(0x0001 << bit), set.mraddr);
}