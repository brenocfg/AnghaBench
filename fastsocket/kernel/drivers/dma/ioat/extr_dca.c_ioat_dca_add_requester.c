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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct ioat_dca_priv {int requester_count; int max_requesters; scalar_t__ dca_base; TYPE_1__* req_slots; } ;
struct device {int /*<<< orphan*/ * bus; } ;
struct dca_provider {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rid; struct pci_dev* pdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENODEV ; 
 struct ioat_dca_priv* dca_priv (struct dca_provider*) ; 
 int /*<<< orphan*/  dcaid_from_pcidev (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_bus_type ; 
 struct pci_dev* to_pci_dev (struct device*) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ioat_dca_add_requester(struct dca_provider *dca, struct device *dev)
{
	struct ioat_dca_priv *ioatdca = dca_priv(dca);
	struct pci_dev *pdev;
	int i;
	u16 id;

	/* This implementation only supports PCI-Express */
	if (dev->bus != &pci_bus_type)
		return -ENODEV;
	pdev = to_pci_dev(dev);
	id = dcaid_from_pcidev(pdev);

	if (ioatdca->requester_count == ioatdca->max_requesters)
		return -ENODEV;

	for (i = 0; i < ioatdca->max_requesters; i++) {
		if (ioatdca->req_slots[i].pdev == NULL) {
			/* found an empty slot */
			ioatdca->requester_count++;
			ioatdca->req_slots[i].pdev = pdev;
			ioatdca->req_slots[i].rid = id;
			writew(id, ioatdca->dca_base + (i * 4));
			/* make sure the ignore function bit is off */
			writeb(0, ioatdca->dca_base + (i * 4) + 2);
			return i;
		}
	}
	/* Error, ioatdma->requester_count is out of whack */
	return -EFAULT;
}