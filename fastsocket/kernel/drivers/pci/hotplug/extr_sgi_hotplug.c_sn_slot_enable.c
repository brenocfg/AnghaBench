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
struct slot {TYPE_2__* pci_bus; } ;
struct pcibus_info {int pbi_enabled_devices; } ;
struct pcibr_slot_enable_resp {int resp_sub_errno; int resp_l1_msg; } ;
struct hotplug_slot {struct slot* private; } ;
struct TYPE_4__ {TYPE_1__* self; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 int PCI_L1_ERR ; 
 int PCI_SLOT_ALREADY_UP ; 
 struct pcibus_info* SN_PCIBUS_BUSSOFT_INFO (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int sal_pcibr_slot_enable (struct pcibus_info*,int,struct pcibr_slot_enable_resp*,char**) ; 

__attribute__((used)) static int sn_slot_enable(struct hotplug_slot *bss_hotplug_slot,
			  int device_num, char **ssdt)
{
	struct slot *slot = bss_hotplug_slot->private;
	struct pcibus_info *pcibus_info;
	struct pcibr_slot_enable_resp resp;
	int rc;

	pcibus_info = SN_PCIBUS_BUSSOFT_INFO(slot->pci_bus);

	/*
	 * Power-on and initialize the slot in the SN
	 * PCI infrastructure.
	 */
	rc = sal_pcibr_slot_enable(pcibus_info, device_num, &resp, ssdt);


	if (rc == PCI_SLOT_ALREADY_UP) {
		dev_dbg(&slot->pci_bus->self->dev, "is already active\n");
		return 1; /* return 1 to user */
	}

	if (rc == PCI_L1_ERR) {
		dev_dbg(&slot->pci_bus->self->dev,
			"L1 failure %d with message: %s",
			resp.resp_sub_errno, resp.resp_l1_msg);
		return -EPERM;
	}

	if (rc) {
		dev_dbg(&slot->pci_bus->self->dev,
			"insert failed with error %d sub-error %d\n",
			rc, resp.resp_sub_errno);
		return -EIO;
	}

	pcibus_info = SN_PCIBUS_BUSSOFT_INFO(slot->pci_bus);
	pcibus_info->pbi_enabled_devices |= (1 << device_num);

	return 0;
}