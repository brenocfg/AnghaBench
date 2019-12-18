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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PCI_SAL_ADDRESS (unsigned int,unsigned int,unsigned int,int) ; 
 scalar_t__ PCI_SAL_EXT_ADDRESS (unsigned int,unsigned int,unsigned int,int) ; 
 scalar_t__ SAL_VERSION_CODE (int,int) ; 
 int ia64_sal_pci_config_read (scalar_t__,int,int,scalar_t__*) ; 
 scalar_t__ sal_revision ; 

int raw_pci_read(unsigned int seg, unsigned int bus, unsigned int devfn,
	      int reg, int len, u32 *value)
{
	u64 addr, data = 0;
	int mode, result;

	if (!value || (seg > 65535) || (bus > 255) || (devfn > 255) || (reg > 4095))
		return -EINVAL;

	if ((seg | reg) <= 255) {
		addr = PCI_SAL_ADDRESS(seg, bus, devfn, reg);
		mode = 0;
	} else if (sal_revision >= SAL_VERSION_CODE(3,2)) {
		addr = PCI_SAL_EXT_ADDRESS(seg, bus, devfn, reg);
		mode = 1;
	} else {
		return -EINVAL;
	}

	result = ia64_sal_pci_config_read(addr, mode, len, &data);
	if (result != 0)
		return -EINVAL;

	*value = (u32) data;
	return 0;
}