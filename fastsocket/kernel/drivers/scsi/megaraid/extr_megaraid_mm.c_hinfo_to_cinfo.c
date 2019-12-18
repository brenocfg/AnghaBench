#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  unique_id; int /*<<< orphan*/  pci_slot; int /*<<< orphan*/  pci_vendor_id; int /*<<< orphan*/  pci_device_id; int /*<<< orphan*/  pci_dev_fn; int /*<<< orphan*/  pci_bus; int /*<<< orphan*/  num_ldrv; int /*<<< orphan*/  irq; int /*<<< orphan*/  baseport; } ;
typedef  TYPE_1__ mraid_hba_info_t ;
struct TYPE_6__ {int /*<<< orphan*/  uid; int /*<<< orphan*/  pcislot; int /*<<< orphan*/  pcivendor; int /*<<< orphan*/  pciid; int /*<<< orphan*/  pcifun; int /*<<< orphan*/  pcidev; int /*<<< orphan*/  pcibus; int /*<<< orphan*/  numldrv; int /*<<< orphan*/  irq; int /*<<< orphan*/  base; } ;
typedef  TYPE_2__ mcontroller_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_FUNC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hinfo_to_cinfo(mraid_hba_info_t *hinfo, mcontroller_t *cinfo)
{
	if (!hinfo || !cinfo)
		return;

	cinfo->base		= hinfo->baseport;
	cinfo->irq		= hinfo->irq;
	cinfo->numldrv		= hinfo->num_ldrv;
	cinfo->pcibus		= hinfo->pci_bus;
	cinfo->pcidev		= hinfo->pci_slot;
	cinfo->pcifun		= PCI_FUNC(hinfo->pci_dev_fn);
	cinfo->pciid		= hinfo->pci_device_id;
	cinfo->pcivendor	= hinfo->pci_vendor_id;
	cinfo->pcislot		= hinfo->pci_slot;
	cinfo->uid		= hinfo->unique_id;
}