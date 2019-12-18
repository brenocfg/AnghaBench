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
typedef  int /*<<< orphan*/  u8 ;
struct sbridge_dev {struct pci_dev** pdev; } ;
struct pci_id_table {struct pci_id_descr* descr; } ;
struct pci_id_descr {scalar_t__ dev; scalar_t__ func; int /*<<< orphan*/  dev_id; scalar_t__ optional; } ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_INTEL ; 
 struct sbridge_dev* alloc_sbridge_dev (int /*<<< orphan*/ ,struct pci_id_table const*) ; 
 int /*<<< orphan*/  debugf0 (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sbridge_dev* get_sbridge_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_dev*) ; 
 int /*<<< orphan*/  sbridge_printk (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,...) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int sbridge_get_onedevice(struct pci_dev **prev,
				 u8 *num_mc,
				 const struct pci_id_table *table,
				 const unsigned devno)
{
	struct sbridge_dev *sbridge_dev;
	const struct pci_id_descr *dev_descr = &table->descr[devno];

	struct pci_dev *pdev = NULL;
	u8 bus = 0;

	sbridge_printk(KERN_INFO,
		"Seeking for: dev %02x.%d PCI ID %04x:%04x\n",
		dev_descr->dev, dev_descr->func,
		PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

	pdev = pci_get_device(PCI_VENDOR_ID_INTEL,
			      dev_descr->dev_id, *prev);

	if (!pdev) {
		if (*prev) {
			*prev = pdev;
			return 0;
		}

		if (dev_descr->optional)
			return 0;

		if (devno == 0)
			return -ENODEV;

		sbridge_printk(KERN_INFO,
			"Device not found: dev %02x.%d PCI ID %04x:%04x\n",
			dev_descr->dev, dev_descr->func,
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

		/* End of list, leave */
		return -ENODEV;
	}
	bus = pdev->bus->number;

	sbridge_dev = get_sbridge_dev(bus);
	if (!sbridge_dev) {
		sbridge_dev = alloc_sbridge_dev(bus, table);
		if (!sbridge_dev) {
			pci_dev_put(pdev);
			return -ENOMEM;
		}
		(*num_mc)++;
	}

	if (sbridge_dev->pdev[devno]) {
		sbridge_printk(KERN_ERR,
			"Duplicated device for "
			"dev %02x:%d.%d PCI ID %04x:%04x\n",
			bus, dev_descr->dev, dev_descr->func,
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
		pci_dev_put(pdev);
		return -ENODEV;
	}

	sbridge_dev->pdev[devno] = pdev;

	/* Sanity check */
	if (unlikely(PCI_SLOT(pdev->devfn) != dev_descr->dev ||
			PCI_FUNC(pdev->devfn) != dev_descr->func)) {
		sbridge_printk(KERN_ERR,
			"Device PCI ID %04x:%04x "
			"has dev %02x:%d.%d instead of dev %02x:%02x.%d\n",
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id,
			bus, PCI_SLOT(pdev->devfn), PCI_FUNC(pdev->devfn),
			bus, dev_descr->dev, dev_descr->func);
		return -ENODEV;
	}

	/* Be sure that the device is enabled */
	if (unlikely(pci_enable_device(pdev) < 0)) {
		sbridge_printk(KERN_ERR,
			"Couldn't enable "
			"dev %02x:%d.%d PCI ID %04x:%04x\n",
			bus, dev_descr->dev, dev_descr->func,
			PCI_VENDOR_ID_INTEL, dev_descr->dev_id);
		return -ENODEV;
	}

	debugf0("Detected dev %02x:%d.%d PCI ID %04x:%04x\n",
		bus, dev_descr->dev,
		dev_descr->func,
		PCI_VENDOR_ID_INTEL, dev_descr->dev_id);

	/*
	 * As stated on drivers/pci/search.c, the reference count for
	 * @from is always decremented if it is not %NULL. So, as we need
	 * to get all devices up to null, we need to do a get for the device
	 */
	pci_dev_get(pdev);

	*prev = pdev;

	return 0;
}