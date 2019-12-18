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
struct TYPE_4__ {struct list_head entry; } ;
struct device {TYPE_2__ power; int /*<<< orphan*/  kobj; TYPE_1__* bus; } ;
struct dev_pm_info_entry {struct list_head entry; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (struct device*,char*) ; 
 int /*<<< orphan*/  dpm_list ; 
 struct dev_pm_info_entry* get_dev_pm_info_entry (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (struct list_head*,struct list_head*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void device_pm_move_after(struct device *deva, struct device *devb)
{
	struct list_head *entrya, *entryb;
#ifdef CONFIG_PPC_PSERIES
	struct dev_pm_info_entry *pm_entrya, *pm_entryb;
#endif /* CONFIG_PPC_PSERIES */

	pr_debug("PM: Moving %s:%s after %s:%s\n",
		 deva->bus ? deva->bus->name : "No Bus",
		 kobject_name(&deva->kobj),
		 devb->bus ? devb->bus->name : "No Bus",
		 kobject_name(&devb->kobj));

#ifdef CONFIG_PPC_PSERIES
	pm_entrya = get_dev_pm_info_entry(deva, &dpm_list);
	if (!pm_entrya) {
		dev_WARN(deva, "Not found on PM device list");
		return;
	}

	pm_entryb = get_dev_pm_info_entry(devb, &dpm_list);
	if (!pm_entryb) {
		dev_WARN(devb, "Not found on PM device list");
		return;
	}

	entrya = &pm_entrya->entry;
	entryb = &pm_entryb->entry;
#else /* !CONFIG_PPC_PSERIES */
	entrya = &deva->power.entry;
	entryb = &devb->power.entry;
#endif /* !CONFIG_PPC_PSERIES */

	/* Delete deva from dpm_list and reinsert before devb. */
	list_move_tail(entrya, entryb);
}