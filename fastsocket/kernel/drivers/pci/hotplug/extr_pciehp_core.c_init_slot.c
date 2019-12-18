#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct slot {struct hotplug_slot_info* hotplug_slot; } ;
struct hotplug_slot_info {int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  latch_status; int /*<<< orphan*/  attention_status; int /*<<< orphan*/  power_status; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * release; struct slot* private; struct hotplug_slot_info* info; } ;
struct hotplug_slot {int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  latch_status; int /*<<< orphan*/  attention_status; int /*<<< orphan*/  power_status; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * release; struct slot* private; struct hotplug_slot* info; } ;
struct controller {TYPE_2__* pcie; struct slot* slot; } ;
struct TYPE_7__ {int /*<<< orphan*/  number; } ;
struct TYPE_6__ {TYPE_1__* port; } ;
struct TYPE_5__ {TYPE_3__* subordinate; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PSN (struct controller*) ; 
 int SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int) ; 
 int /*<<< orphan*/  get_adapter_status (struct hotplug_slot_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_attention_status (struct hotplug_slot_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_latch_status (struct hotplug_slot_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_power_status (struct hotplug_slot_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct hotplug_slot_info*) ; 
 struct hotplug_slot_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_3__*) ; 
 int pci_hp_register (struct hotplug_slot_info*,TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pciehp_hotplug_slot_ops ; 
 int /*<<< orphan*/  release_slot ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int init_slot(struct controller *ctrl)
{
	struct slot *slot = ctrl->slot;
	struct hotplug_slot *hotplug = NULL;
	struct hotplug_slot_info *info = NULL;
	char name[SLOT_NAME_SIZE];
	int retval = -ENOMEM;

	hotplug = kzalloc(sizeof(*hotplug), GFP_KERNEL);
	if (!hotplug)
		goto out;

	info = kzalloc(sizeof(*info), GFP_KERNEL);
	if (!info)
		goto out;

	/* register this slot with the hotplug pci core */
	hotplug->info = info;
	hotplug->private = slot;
	hotplug->release = &release_slot;
	hotplug->ops = &pciehp_hotplug_slot_ops;
	slot->hotplug_slot = hotplug;
	snprintf(name, SLOT_NAME_SIZE, "%u", PSN(ctrl));

	ctrl_dbg(ctrl, "Registering domain:bus:dev=%04x:%02x:00 sun=%x\n",
		 pci_domain_nr(ctrl->pcie->port->subordinate),
		 ctrl->pcie->port->subordinate->number, PSN(ctrl));
	retval = pci_hp_register(hotplug,
				 ctrl->pcie->port->subordinate, 0, name);
	if (retval) {
		ctrl_err(ctrl,
			 "pci_hp_register failed with error %d\n", retval);
		goto out;
	}
	get_power_status(hotplug, &info->power_status);
	get_attention_status(hotplug, &info->attention_status);
	get_latch_status(hotplug, &info->latch_status);
	get_adapter_status(hotplug, &info->adapter_status);
out:
	if (retval) {
		kfree(info);
		kfree(hotplug);
	}
	return retval;
}