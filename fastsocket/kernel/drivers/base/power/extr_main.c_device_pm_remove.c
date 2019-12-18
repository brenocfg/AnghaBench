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
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
struct device {TYPE_1__ power; int /*<<< orphan*/  kobj; TYPE_2__* bus; } ;
struct dev_pm_info_entry {int /*<<< orphan*/  entry; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (struct device*,char*) ; 
 int /*<<< orphan*/  dpm_list ; 
 int /*<<< orphan*/  dpm_list_mtx ; 
 struct dev_pm_info_entry* get_dev_pm_info_entry (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dev_pm_info_entry*) ; 
 int /*<<< orphan*/  kobject_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_remove (struct device*) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int /*<<< orphan*/ ) ; 

void device_pm_remove(struct device *dev)
{
#ifdef CONFIG_PPC_PSERIES
	struct dev_pm_info_entry* pm_entry;
#endif /* CONFIG_PPC_PSERIES */

	pr_debug("PM: Removing info for %s:%s\n",
		 dev->bus ? dev->bus->name : "No Bus",
		 kobject_name(&dev->kobj));
	mutex_lock(&dpm_list_mtx);

#ifdef CONFIG_PPC_PSERIES
	pm_entry = get_dev_pm_info_entry(dev, &dpm_list);
	if (!pm_entry) {
		dev_WARN(dev, "Not found on PM device list");
		goto out;
	}
	list_del_init(&pm_entry->entry);
	kfree(pm_entry);
out:
#else  /* !CONFIG_PPC_PSERIES */
	list_del_init(&dev->power.entry);
#endif /* !CONFIG_PPC_PSERIES */

	mutex_unlock(&dpm_list_mtx);
	pm_runtime_remove(dev);
}