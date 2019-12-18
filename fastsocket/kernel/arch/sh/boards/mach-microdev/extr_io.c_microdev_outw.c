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
 unsigned long PCIBIOS_MIN_IO ; 
 scalar_t__ PORT2ADDR (unsigned long) ; 
 int /*<<< orphan*/  microdev_pci_outw (unsigned short,unsigned long) ; 

void microdev_outw(unsigned short b, unsigned long port)
{
#ifdef CONFIG_PCI
	if (port >= PCIBIOS_MIN_IO) {
		microdev_pci_outw(b, port);
		return;
	}
#endif
	*(volatile unsigned short*)PORT2ADDR(port) = b;
}