#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_sriov {TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {int /*<<< orphan*/  bus; TYPE_3__ dev; struct pci_sriov* sriov; } ;
struct pci_bus {int dummy; } ;
struct TYPE_5__ {TYPE_1__* sriov; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int VIRTFN_ID_LEN ; 
 int /*<<< orphan*/  __pci_reset_function (struct pci_dev*) ; 
 int /*<<< orphan*/  device_release_driver (TYPE_3__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (int /*<<< orphan*/ ) ; 
 struct pci_bus* pci_find_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_slot (struct pci_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_remove_bus_device (struct pci_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  sysfs_remove_link (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  virtfn_bus (struct pci_dev*,int) ; 
 int /*<<< orphan*/  virtfn_devfn (struct pci_dev*,int) ; 
 int /*<<< orphan*/  virtfn_remove_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtfn_remove(struct pci_dev *dev, int id, int reset)
{
	char buf[VIRTFN_ID_LEN];
	struct pci_bus *bus;
	struct pci_dev *virtfn;
	struct pci_sriov *iov = dev->sriov;

	bus = pci_find_bus(pci_domain_nr(dev->bus), virtfn_bus(dev, id));
	if (!bus)
		return;

	virtfn = pci_get_slot(bus, virtfn_devfn(dev, id));
	if (!virtfn)
		return;

	pci_dev_put(virtfn);

	if (reset) {
		device_release_driver(&virtfn->dev);
		__pci_reset_function(virtfn);
	}

	sprintf(buf, "virtfn%u", id);
	sysfs_remove_link(&dev->dev.kobj, buf);
	sysfs_remove_link(&virtfn->dev.kobj, "physfn");

	mutex_lock(&iov->dev->sriov->lock);
	pci_remove_bus_device(virtfn);
	virtfn_remove_bus(dev->bus, virtfn_bus(dev, id));
	mutex_unlock(&iov->dev->sriov->lock);

	pci_dev_put(dev);
}