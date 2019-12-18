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
struct ssb_bus {scalar_t__ bustype; int /*<<< orphan*/  sprom_mutex; struct pci_dev* host_pci; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_PCI ; 
 int /*<<< orphan*/  dev_attr_ssb_sprom ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int ssb_pci_init(struct ssb_bus *bus)
{
	struct pci_dev *pdev;
	int err;

	if (bus->bustype != SSB_BUSTYPE_PCI)
		return 0;

	pdev = bus->host_pci;
	mutex_init(&bus->sprom_mutex);
	err = device_create_file(&pdev->dev, &dev_attr_ssb_sprom);
	if (err)
		goto out;

out:
	return err;
}