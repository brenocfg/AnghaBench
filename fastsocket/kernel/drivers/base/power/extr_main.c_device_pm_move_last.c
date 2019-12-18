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
struct list_head {int dummy; } ;
struct TYPE_3__ {struct list_head entry; } ;
struct device {TYPE_1__ power; int /*<<< orphan*/  kobj; TYPE_2__* bus; } ;
struct dev_pm_info_entry {struct list_head entry; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (struct device*,char*) ; 
 int /*<<< orphan*/  dpm_list ; 
 struct dev_pm_info_entry* get_dev_pm_info_entry (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ) ; 

void device_pm_move_last(struct device *dev)
{
	struct list_head *entry;
#ifdef CONFIG_PPC_PSERIES
	struct dev_pm_info_entry *pm_entry;
#endif /* CONFIG_PPC_PSERIES */

	pr_debug("PM: Moving %s:%s to end of list\n",
		 dev->bus ? dev->bus->name : "No Bus",
		 kobject_name(&dev->kobj));

#ifdef CONFIG_PPC_PSERIES
	pm_entry = get_dev_pm_info_entry(dev, &dpm_list);
	if (!pm_entry) {
		dev_WARN(dev, "Not found on PM device list");
		return;
	}
	entry = &pm_entry->entry;
#else /* !CONFIG_PPC_PSERIES */
	entry = &dev->power.entry;
#endif /* !CONFIG_PPC_PSERIES */

	list_move_tail(entry, &dpm_list);
}