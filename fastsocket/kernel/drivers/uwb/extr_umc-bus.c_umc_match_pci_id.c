#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct umc_driver {struct pci_device_id* match_data; } ;
struct TYPE_3__ {TYPE_2__* parent; } ;
struct umc_dev {TYPE_1__ dev; } ;
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_bus_type ; 
 int /*<<< orphan*/ * pci_match_id (struct pci_device_id const*,struct pci_dev*) ; 
 struct pci_dev* to_pci_dev (TYPE_2__*) ; 

int umc_match_pci_id(struct umc_driver *umc_drv, struct umc_dev *umc)
{
	const struct pci_device_id *id_table = umc_drv->match_data;
	struct pci_dev *pci;

	if (umc->dev.parent->bus != &pci_bus_type)
		return 0;

	pci = to_pci_dev(umc->dev.parent);
	return pci_match_id(id_table, pci) != NULL;
}