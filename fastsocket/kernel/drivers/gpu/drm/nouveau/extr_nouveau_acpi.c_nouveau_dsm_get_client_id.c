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
struct pci_dev {scalar_t__ vendor; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ number; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int VGA_SWITCHEROO_DIS ; 
 int VGA_SWITCHEROO_IGD ; 

__attribute__((used)) static int nouveau_dsm_get_client_id(struct pci_dev *pdev)
{
	/* easy option one - intel vendor ID means Integrated */
	if (pdev->vendor == PCI_VENDOR_ID_INTEL)
		return VGA_SWITCHEROO_IGD;

	/* is this device on Bus 0? - this may need improving */
	if (pdev->bus->number == 0)
		return VGA_SWITCHEROO_IGD;

	return VGA_SWITCHEROO_DIS;
}