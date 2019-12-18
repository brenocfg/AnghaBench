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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PCI_SAL_ADDRESS (unsigned int,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  PCI_SAL_EXT_ADDRESS (unsigned int,unsigned int,unsigned int,int) ; 
 scalar_t__ SAL_VERSION_CODE (int,int) ; 
 int ia64_sal_pci_config_write (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sal_revision ; 

int raw_pci_write(unsigned int seg, unsigned int bus, unsigned int devfn,
	       int reg, int len, u32 value)
{
	u64 addr;
	int mode, result;

	if ((seg > 65535) || (bus > 255) || (devfn > 255) || (reg > 4095))
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
	result = ia64_sal_pci_config_write(addr, mode, len, value);
	if (result != 0)
		return -EINVAL;
	return 0;
}