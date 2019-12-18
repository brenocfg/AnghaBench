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
struct pci_dev {int subsystem_device; } ;
struct be_adapter {struct pci_dev* pdev; } ;

/* Variables and functions */
#define  OC_SUBSYS_DEVICE_ID1 131 
#define  OC_SUBSYS_DEVICE_ID2 130 
#define  OC_SUBSYS_DEVICE_ID3 129 
#define  OC_SUBSYS_DEVICE_ID4 128 
 int /*<<< orphan*/  be_physfn (struct be_adapter*) ; 

__attribute__((used)) static inline bool be_is_wol_excluded(struct be_adapter *adapter)
{
	struct pci_dev *pdev = adapter->pdev;

	if (!be_physfn(adapter))
		return true;

	switch (pdev->subsystem_device) {
	case OC_SUBSYS_DEVICE_ID1:
	case OC_SUBSYS_DEVICE_ID2:
	case OC_SUBSYS_DEVICE_ID3:
	case OC_SUBSYS_DEVICE_ID4:
		return true;
	default:
		return false;
	}
}