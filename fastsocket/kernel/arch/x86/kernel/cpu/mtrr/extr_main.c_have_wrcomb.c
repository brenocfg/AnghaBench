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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; } ;
struct TYPE_2__ {int (* have_wrcomb ) () ;} ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_HOST ; 
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 scalar_t__ PCI_DEVICE_ID_INTEL_82451NX ; 
 scalar_t__ PCI_DEVICE_ID_SERVERWORKS_LE ; 
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 scalar_t__ PCI_VENDOR_ID_SERVERWORKS ; 
 TYPE_1__* mtrr_if ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_class (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int stub1 () ; 

__attribute__((used)) static int have_wrcomb(void)
{
	struct pci_dev *dev;
	u8 rev;

	dev = pci_get_class(PCI_CLASS_BRIDGE_HOST << 8, NULL);
	if (dev != NULL) {
		/*
		 * ServerWorks LE chipsets < rev 6 have problems with
		 * write-combining. Don't allow it and leave room for other
		 * chipsets to be tagged
		 */
		if (dev->vendor == PCI_VENDOR_ID_SERVERWORKS &&
		    dev->device == PCI_DEVICE_ID_SERVERWORKS_LE) {
			pci_read_config_byte(dev, PCI_CLASS_REVISION, &rev);
			if (rev <= 5) {
				pr_info("mtrr: Serverworks LE rev < 6 detected. Write-combining disabled.\n");
				pci_dev_put(dev);
				return 0;
			}
		}
		/*
		 * Intel 450NX errata # 23. Non ascending cacheline evictions to
		 * write combining memory may resulting in data corruption
		 */
		if (dev->vendor == PCI_VENDOR_ID_INTEL &&
		    dev->device == PCI_DEVICE_ID_INTEL_82451NX) {
			pr_info("mtrr: Intel 450NX MMC detected. Write-combining disabled.\n");
			pci_dev_put(dev);
			return 0;
		}
		pci_dev_put(dev);
	}
	return mtrr_if->have_wrcomb ? mtrr_if->have_wrcomb() : 0;
}