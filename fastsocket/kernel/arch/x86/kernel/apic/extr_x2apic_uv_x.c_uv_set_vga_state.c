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
typedef  int u32 ;
struct pci_dev {int devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int number; } ;

/* Variables and functions */
 unsigned int PCI_COMMAND_IO ; 
 int PCI_VGA_STATE_CHANGE_BRIDGE ; 
 int /*<<< orphan*/  PR_DEVEL (char*,int,int,int,int) ; 
 int pci_domain_nr (TYPE_1__*) ; 
 int uv_bios_set_legacy_vga_target (int,int,int) ; 

int uv_set_vga_state(struct pci_dev *pdev, bool decode,
		      unsigned int command_bits, u32 flags)
{
	int domain, bus, rc;

	PR_DEVEL("devfn %x decode %d cmd %x flags %d\n",
			pdev->devfn, decode, command_bits, flags);

	if (!(flags & PCI_VGA_STATE_CHANGE_BRIDGE))
		return 0;

	if ((command_bits & PCI_COMMAND_IO) == 0)
		return 0;

	domain = pci_domain_nr(pdev->bus);
	bus = pdev->bus->number;

	rc = uv_bios_set_legacy_vga_target(decode, domain, bus);
	PR_DEVEL("vga decode %d %x:%x, rc: %d\n", decode, domain, bus, rc);

	return rc;
}