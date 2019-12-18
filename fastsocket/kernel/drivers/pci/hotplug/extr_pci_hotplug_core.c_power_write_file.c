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
struct pci_slot {struct hotplug_slot* hotplug; } ;
struct hotplug_slot {TYPE_1__* ops; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* disable_slot ) (struct hotplug_slot*) ;int (* enable_slot ) (struct hotplug_slot*) ;int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  dbg (char*,int) ; 
 int /*<<< orphan*/  err (char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 unsigned long simple_strtoul (char const*,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct hotplug_slot*) ; 
 int stub2 (struct hotplug_slot*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t power_write_file(struct pci_slot *pci_slot, const char *buf,
		size_t count)
{
	struct hotplug_slot *slot = pci_slot->hotplug;
	unsigned long lpower;
	u8 power;
	int retval = 0;

	lpower = simple_strtoul (buf, NULL, 10);
	power = (u8)(lpower & 0xff);
	dbg ("power = %d\n", power);

	if (!try_module_get(slot->ops->owner)) {
		retval = -ENODEV;
		goto exit;
	}
	switch (power) {
		case 0:
			if (slot->ops->disable_slot)
				retval = slot->ops->disable_slot(slot);
			break;

		case 1:
			if (slot->ops->enable_slot)
				retval = slot->ops->enable_slot(slot);
			break;

		default:
			err ("Illegal value specified for power\n");
			retval = -EINVAL;
	}
	module_put(slot->ops->owner);

exit:	
	if (retval)
		return retval;
	return count;
}