#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct slot {int hp_slot; int number; int /*<<< orphan*/  slot_list; int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  latch_status; int /*<<< orphan*/  attention_status; int /*<<< orphan*/  power_status; scalar_t__ device; struct slot* hotplug_slot; int /*<<< orphan*/  bus; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * release; struct slot* private; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  hpc_ops; struct controller* ctrl; struct slot* info; } ;
struct hotplug_slot_info {int hp_slot; int number; int /*<<< orphan*/  slot_list; int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  latch_status; int /*<<< orphan*/  attention_status; int /*<<< orphan*/  power_status; scalar_t__ device; struct hotplug_slot_info* hotplug_slot; int /*<<< orphan*/  bus; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * release; struct hotplug_slot_info* private; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  hpc_ops; struct controller* ctrl; struct hotplug_slot_info* info; } ;
struct hotplug_slot {int hp_slot; int number; int /*<<< orphan*/  slot_list; int /*<<< orphan*/  adapter_status; int /*<<< orphan*/  latch_status; int /*<<< orphan*/  attention_status; int /*<<< orphan*/  power_status; scalar_t__ device; struct hotplug_slot* hotplug_slot; int /*<<< orphan*/  bus; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * release; struct hotplug_slot* private; int /*<<< orphan*/  work; int /*<<< orphan*/  lock; int /*<<< orphan*/  hpc_ops; struct controller* ctrl; struct hotplug_slot* info; } ;
struct controller {int num_slots; int first_slot; int slot_num_inc; int /*<<< orphan*/  slot_list; TYPE_1__* pci_dev; int /*<<< orphan*/  slot_device_offset; int /*<<< orphan*/  hpc_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  number; } ;
struct TYPE_4__ {TYPE_2__* subordinate; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SLOT_NAME_SIZE ; 
 int /*<<< orphan*/  ctrl_dbg (struct controller*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctrl_err (struct controller*,char*,int) ; 
 int /*<<< orphan*/  get_adapter_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_attention_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_latch_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_power_status (struct slot*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct slot*) ; 
 struct slot* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_2__*) ; 
 int pci_hp_register (struct slot*,TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  release_slot ; 
 int /*<<< orphan*/  shpchp_hotplug_slot_ops ; 
 int /*<<< orphan*/  shpchp_queue_pushbutton_work ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int init_slots(struct controller *ctrl)
{
	struct slot *slot;
	struct hotplug_slot *hotplug_slot;
	struct hotplug_slot_info *info;
	char name[SLOT_NAME_SIZE];
	int retval = -ENOMEM;
	int i;

	for (i = 0; i < ctrl->num_slots; i++) {
		slot = kzalloc(sizeof(*slot), GFP_KERNEL);
		if (!slot)
			goto error;

		hotplug_slot = kzalloc(sizeof(*hotplug_slot), GFP_KERNEL);
		if (!hotplug_slot)
			goto error_slot;
		slot->hotplug_slot = hotplug_slot;

		info = kzalloc(sizeof(*info), GFP_KERNEL);
		if (!info)
			goto error_hpslot;
		hotplug_slot->info = info;

		slot->hp_slot = i;
		slot->ctrl = ctrl;
		slot->bus = ctrl->pci_dev->subordinate->number;
		slot->device = ctrl->slot_device_offset + i;
		slot->hpc_ops = ctrl->hpc_ops;
		slot->number = ctrl->first_slot + (ctrl->slot_num_inc * i);
		mutex_init(&slot->lock);
		INIT_DELAYED_WORK(&slot->work, shpchp_queue_pushbutton_work);

		/* register this slot with the hotplug pci core */
		hotplug_slot->private = slot;
		hotplug_slot->release = &release_slot;
		snprintf(name, SLOT_NAME_SIZE, "%d", slot->number);
		hotplug_slot->ops = &shpchp_hotplug_slot_ops;

 		ctrl_dbg(ctrl, "Registering domain:bus:dev=%04x:%02x:%02x "
 			 "hp_slot=%x sun=%x slot_device_offset=%x\n",
 			 pci_domain_nr(ctrl->pci_dev->subordinate),
 			 slot->bus, slot->device, slot->hp_slot, slot->number,
 			 ctrl->slot_device_offset);
		retval = pci_hp_register(slot->hotplug_slot,
				ctrl->pci_dev->subordinate, slot->device, name);
		if (retval) {
			ctrl_err(ctrl, "pci_hp_register failed with error %d\n",
				 retval);
			goto error_info;
		}

		get_power_status(hotplug_slot, &info->power_status);
		get_attention_status(hotplug_slot, &info->attention_status);
		get_latch_status(hotplug_slot, &info->latch_status);
		get_adapter_status(hotplug_slot, &info->adapter_status);

		list_add(&slot->slot_list, &ctrl->slot_list);
	}

	return 0;
error_info:
	kfree(info);
error_hpslot:
	kfree(hotplug_slot);
error_slot:
	kfree(slot);
error:
	return retval;
}