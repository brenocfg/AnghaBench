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
typedef  int uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCICONFAREG ; 
 int PCI_FUNC (unsigned int) ; 
 unsigned int PCI_SLOT (unsigned int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int set_pci_configuration_address(unsigned char number,
                                                unsigned int devfn, int where)
{
	if (number == 0) {
		/*
		 * Type 0 configuration
		 */
		if (PCI_SLOT(devfn) < 11 || where > 0xff)
			return -EINVAL;

		writel((1U << PCI_SLOT(devfn)) | (PCI_FUNC(devfn) << 8) |
		       (where & 0xfc), PCICONFAREG);
	} else {
		/*
		 * Type 1 configuration
		 */
		if (where > 0xff)
			return -EINVAL;

		writel(((uint32_t)number << 16) | ((devfn & 0xff) << 8) |
		       (where & 0xfc) | 1U, PCICONFAREG);
	}

	return 0;
}