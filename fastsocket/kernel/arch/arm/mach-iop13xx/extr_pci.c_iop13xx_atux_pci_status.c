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
 int /*<<< orphan*/  IOP13XX_ATUX_ATUISR ; 
 unsigned int IOP13XX_ATUX_ATUISR_ERROR ; 
 int /*<<< orphan*/  IOP13XX_ATUX_ATUSR ; 
 unsigned int IOP_PCI_STATUS_ERROR ; 
 int /*<<< orphan*/  PRINTK (char*,unsigned int) ; 
 unsigned int __raw_readl (int /*<<< orphan*/ ) ; 
 unsigned int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iop13xx_atux_pci_status(int clear)
{
	unsigned int status;
	int err = 0;

	/*
	 * Check the status registers.
	 */
	status = __raw_readw(IOP13XX_ATUX_ATUSR);
	if (status & IOP_PCI_STATUS_ERROR)
	{
		PRINTK("\t\t\tPCI error: ATUSR %#08x", status);
		if(clear)
			__raw_writew(status & IOP_PCI_STATUS_ERROR,
				IOP13XX_ATUX_ATUSR);
		err = 1;
	}
	status = __raw_readl(IOP13XX_ATUX_ATUISR);
	if (status & IOP13XX_ATUX_ATUISR_ERROR)
	{
		PRINTK("\t\t\tPCI error interrupt:  ATUISR %#08x", status);
		if(clear)
			__raw_writel(status & IOP13XX_ATUX_ATUISR_ERROR,
				IOP13XX_ATUX_ATUISR);
		err = 1;
	}
	return err;
}