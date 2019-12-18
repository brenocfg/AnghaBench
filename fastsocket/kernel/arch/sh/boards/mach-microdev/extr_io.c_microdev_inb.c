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
 unsigned char microdev_pci_inb (unsigned long) ; 

unsigned char microdev_inb(unsigned long port)
{
#ifdef CONFIG_PCI
	if (port >= PCIBIOS_MIN_IO)
		return microdev_pci_inb(port);
#endif
	return *(volatile unsigned char*)PORT2ADDR(port);
}