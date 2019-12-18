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
struct TYPE_6__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {int reset_fn; TYPE_2__* vpd; TYPE_3__ dev; } ;
struct TYPE_4__ {char* name; int mode; } ;
struct bin_attribute {int /*<<< orphan*/  write; int /*<<< orphan*/  read; TYPE_1__ attr; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {struct bin_attribute* attr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int S_IRUSR ; 
 int S_IWUSR ; 
 int device_create_file (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bin_attribute*) ; 
 struct bin_attribute* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_probe_reset_function (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_aspm_create_sysfs_dev_files (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_aspm_remove_sysfs_dev_files (struct pci_dev*) ; 
 int /*<<< orphan*/  read_vpd_attr ; 
 int /*<<< orphan*/  reset_attr ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,struct bin_attribute*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,struct bin_attribute*) ; 
 int /*<<< orphan*/  write_vpd_attr ; 

__attribute__((used)) static int pci_create_capabilities_sysfs(struct pci_dev *dev)
{
	int retval;
	struct bin_attribute *attr;

	/* If the device has VPD, try to expose it in sysfs. */
	if (dev->vpd) {
		attr = kzalloc(sizeof(*attr), GFP_ATOMIC);
		if (!attr)
			return -ENOMEM;

		attr->size = dev->vpd->len;
		attr->attr.name = "vpd";
		attr->attr.mode = S_IRUSR | S_IWUSR;
		attr->read = read_vpd_attr;
		attr->write = write_vpd_attr;
		retval = sysfs_create_bin_file(&dev->dev.kobj, attr);
		if (retval) {
			kfree(dev->vpd->attr);
			return retval;
		}
		dev->vpd->attr = attr;
	}

	/* Active State Power Management */
	pcie_aspm_create_sysfs_dev_files(dev);

	if (!pci_probe_reset_function(dev)) {
		retval = device_create_file(&dev->dev, &reset_attr);
		if (retval)
			goto error;
		dev->reset_fn = 1;
	}
	return 0;

error:
	pcie_aspm_remove_sysfs_dev_files(dev);
	if (dev->vpd && dev->vpd->attr) {
		sysfs_remove_bin_file(&dev->dev.kobj, dev->vpd->attr);
		kfree(dev->vpd->attr);
	}

	return retval;
}