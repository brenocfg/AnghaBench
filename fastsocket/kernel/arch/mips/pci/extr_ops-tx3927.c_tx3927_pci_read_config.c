#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct pci_bus {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  icd; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int check_abort () ; 
 int le16_to_cpu (int /*<<< orphan*/  volatile) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mkaddr (struct pci_bus*,unsigned int,int) ; 
 TYPE_1__* tx3927_pcicptr ; 

__attribute__((used)) static int tx3927_pci_read_config(struct pci_bus *bus, unsigned int devfn,
	int where, int size, u32 * val)
{
	if (mkaddr(bus, devfn, where)) {
		*val = 0xffffffff;
		return PCIBIOS_DEVICE_NOT_FOUND;
	}

	switch (size) {
	case 1:
		*val = *(volatile u8 *) ((unsigned long) & tx3927_pcicptr->icd | (where & 3));
		break;

	case 2:
		*val = le16_to_cpu(*(volatile u16 *) ((unsigned long) & tx3927_pcicptr->icd | (where & 3)));
		break;

	case 4:
		*val = le32_to_cpu(tx3927_pcicptr->icd);
		break;
	}

	return check_abort();
}