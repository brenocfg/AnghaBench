#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct amd64_pvt {TYPE_1__* F3; TYPE_1__* F2; TYPE_1__* F1; } ;
struct TYPE_4__ {int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_AMD ; 
 int /*<<< orphan*/  amd64_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugf1 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_1__*) ; 
 void* pci_get_related_function (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  pci_name (TYPE_1__*) ; 

__attribute__((used)) static int reserve_mc_sibling_devs(struct amd64_pvt *pvt, u16 f1_id, u16 f3_id)
{
	/* Reserve the ADDRESS MAP Device */
	pvt->F1 = pci_get_related_function(pvt->F2->vendor, f1_id, pvt->F2);
	if (!pvt->F1) {
		amd64_err("error address map device not found: "
			  "vendor %x device 0x%x (broken BIOS?)\n",
			  PCI_VENDOR_ID_AMD, f1_id);
		return -ENODEV;
	}

	/* Reserve the MISC Device */
	pvt->F3 = pci_get_related_function(pvt->F2->vendor, f3_id, pvt->F2);
	if (!pvt->F3) {
		pci_dev_put(pvt->F1);
		pvt->F1 = NULL;

		amd64_err("error F3 device not found: "
			  "vendor %x device 0x%x (broken BIOS?)\n",
			  PCI_VENDOR_ID_AMD, f3_id);

		return -ENODEV;
	}
	debugf1("F1: %s\n", pci_name(pvt->F1));
	debugf1("F2: %s\n", pci_name(pvt->F2));
	debugf1("F3: %s\n", pci_name(pvt->F3));

	return 0;
}