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
typedef  int* vulp ;
typedef  int u8 ;
struct pci_bus {int number; } ;

/* Variables and functions */
 scalar_t__ LCA_IOC_CONF ; 

__attribute__((used)) static int
mk_conf_addr(struct pci_bus *pbus, unsigned int device_fn, int where,
	     unsigned long *pci_addr)
{
	unsigned long addr;
	u8 bus = pbus->number;

	if (bus == 0) {
		int device = device_fn >> 3;
		int func = device_fn & 0x7;

		/* Type 0 configuration cycle.  */

		if (device > 12) {
			return -1;
		}

		*(vulp)LCA_IOC_CONF = 0;
		addr = (1 << (11 + device)) | (func << 8) | where;
	} else {
		/* Type 1 configuration cycle.  */
		*(vulp)LCA_IOC_CONF = 1;
		addr = (bus << 16) | (device_fn << 8) | where;
	}
	*pci_addr = addr;
	return 0;
}