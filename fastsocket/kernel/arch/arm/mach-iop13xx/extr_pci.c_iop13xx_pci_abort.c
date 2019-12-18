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
struct pt_regs {int ARM_pc; int /*<<< orphan*/  ARM_lr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOP13XX_XBG_BECSR ; 
 int /*<<< orphan*/  IOP13XX_XBG_BERAR ; 
 int /*<<< orphan*/  IOP13XX_XBG_BERUAR ; 
 int /*<<< orphan*/  PRINTK (char*,unsigned long,...) ; 
 int /*<<< orphan*/  __raw_readl (int /*<<< orphan*/ ) ; 
 scalar_t__ is_atue_occdr_error () ; 
 scalar_t__ is_atux_occdr_error () ; 

int
iop13xx_pci_abort(unsigned long addr, unsigned int fsr, struct pt_regs *regs)
{
	PRINTK("Data abort: address = 0x%08lx "
		    "fsr = 0x%03x PC = 0x%08lx LR = 0x%08lx",
		addr, fsr, regs->ARM_pc, regs->ARM_lr);

	PRINTK("IOP13XX_XBG_BECSR: %#10x", __raw_readl(IOP13XX_XBG_BECSR));
	PRINTK("IOP13XX_XBG_BERAR: %#10x", __raw_readl(IOP13XX_XBG_BERAR));
	PRINTK("IOP13XX_XBG_BERUAR: %#10x", __raw_readl(IOP13XX_XBG_BERUAR));

	/*  If it was an imprecise abort, then we need to correct the
	 *  return address to be _after_ the instruction.
	 */
	if (fsr & (1 << 10))
		regs->ARM_pc += 4;

	if (is_atue_occdr_error() || is_atux_occdr_error())
		return 0;
	else
		return 1;
}